#include "guitartuner.h"
#include "ui_guitartuner.h"

#include <QMainWindow>
#include <math.h>
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <qendian.h>

const int BufferSize = 4096;  //размер буфера

GuitarTuner::GuitarTuner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuitarTuner),
    m_maximumPrecision(0)
{
    ui->setupUi(this);

    m_outputActive = false;
    m_muted = false;
    m_outputVolumeLevel = getVolumeFromSoundSlider();
    m_inputVolumeLevel = 1.0 - m_outputVolumeLevel;

    m_currentToneIndex = 5;


    updateFrequencyByToneIndex(m_currentToneIndex);

    connect(ui->soundSlider, SIGNAL(valueChanged(int)),
           SLOT(changeVolume()));
    connect(ui->soundButton, SIGNAL(toggled(bool)),
           SLOT(toggleSound(bool)));
    connect(ui->modeButton, SIGNAL(clicked()),
           SLOT(toggleInputOrOutput()));
    connect(ui->buttonNext, SIGNAL(clicked()), SLOT(next()));
    connect(ui->buttonPrev, SIGNAL(clicked()), SLOT(prev()));

    initAudioInput();
    initAudioOutput();

    connect(this, SIGNAL(muteStateChanged(bool)),
                SLOT(muteStateChanged(bool)));
        connect(this, SIGNAL(volumeChanged(qreal)),
                m_voicegenerator, SLOT(setAmplitude(qreal)));
        connect(this, SIGNAL(volumeChanged(qreal)),
                SLOT(setMaxVolumeLevel(qreal)));

        connect(this, SIGNAL(modeChanged(bool)),
                SLOT(modeChanged(bool)));

        connect(this, SIGNAL(microphoneSensitivityChanged(qreal)),
                m_analyzer, SLOT(setCutOffPercentage(qreal)));

        connect(m_analyzer, SIGNAL(lowVoice()),
                this, SLOT(lowVoice()));
        connect(m_analyzer, SIGNAL(correctFrequency()),
                this, SLOT(correctFrequencyObtained()));
        connect(m_analyzer, SIGNAL(voiceDifference(QVariant)),
                this, SLOT(voiceDifferenceChanged(QVariant)));

        voiceDifference(m_analyzer->getMaximumVoiceDifference());

        connect(this, SIGNAL(targetFrequencyChanged(qreal)),
                SLOT(targetFrequencyChanged(qreal)));

        modeChanged(m_outputActive);

    toggleInputOrOutput();
}

GuitarTuner::~GuitarTuner()
{
    delete ui;
}

AudioInfo::AudioInfo(const QAudioFormat &format, QObject *parent):
    QIODevice(parent),
    m_format(format),
    m_maxAmplitude(0),
    m_level(0.0)

{
    switch (m_format.sampleSize()) {
    case 8:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 255;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 127;
            break;
        default:
            break;
        }
        break;
    case 16:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 65535;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 32767;
            break;
        default:
            break;
        }
        break;

    case 32:
        switch (m_format.sampleType()) {
        case QAudioFormat::UnSignedInt:
            m_maxAmplitude = 0xffffffff;
            break;
        case QAudioFormat::SignedInt:
            m_maxAmplitude = 0x7fffffff;
            break;
        case QAudioFormat::Float:
            m_maxAmplitude = 0x7fffffff; // Kind of
        default:
            break;
        }
        break;

    default:
        break;
    }
}

AudioInfo::~AudioInfo()
{
}

void AudioInfo::start()
{
    open(QIODevice::WriteOnly);
}

void AudioInfo::stop()
{
    close();
}

qint64 AudioInfo::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)

    return 0;
}

qint64 AudioInfo::writeData(const char *data, qint64 len)
{
    if (m_maxAmplitude) {
        Q_ASSERT(m_format.sampleSize() % 8 == 0);
        const int channelBytes = m_format.sampleSize() / 8;
        const int sampleBytes = m_format.channelCount() * channelBytes;
        Q_ASSERT(len % sampleBytes == 0);
        const int numSamples = len / sampleBytes;

        quint32 maxValue = 0;
        const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);

        for (int i = 0; i < numSamples; ++i) {
            for (int j = 0; j < m_format.channelCount(); ++j) {
                quint32 value = 0;

                if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    value = *reinterpret_cast<const quint8*>(ptr);
                } else if (m_format.sampleSize() == 8 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    value = qAbs(*reinterpret_cast<const qint8*>(ptr));
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint16>(ptr);
                    else
                        value = qFromBigEndian<quint16>(ptr);
                } else if (m_format.sampleSize() == 16 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint16>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint16>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::UnSignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qFromLittleEndian<quint32>(ptr);
                    else
                        value = qFromBigEndian<quint32>(ptr);
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::SignedInt) {
                    if (m_format.byteOrder() == QAudioFormat::LittleEndian)
                        value = qAbs(qFromLittleEndian<qint32>(ptr));
                    else
                        value = qAbs(qFromBigEndian<qint32>(ptr));
                } else if (m_format.sampleSize() == 32 && m_format.sampleType() == QAudioFormat::Float) {
                    value = qAbs(*reinterpret_cast<const float*>(ptr) * 0x7fffffff); // assumes 0-1.0
                }

                maxValue = qMax(value, maxValue);
                ptr += channelBytes;
            }
        }

        maxValue = qMin(maxValue, m_maxAmplitude);
        m_level = qreal(maxValue) / m_maxAmplitude;
    }

    emit update();
    return len;
}

void GuitarTuner::initAudioOutput()
 {
     m_format_output.setSampleRate(DataFrequencyHzOutput);
     m_format_output.setCodec("audio/pcm");
     m_format_output.setSampleSize(16);
     m_format_output.setChannelCount(1);
     m_format_output.setByteOrder(QAudioFormat::LittleEndian);
     m_format_output.setSampleType(QAudioFormat::SignedInt);

     QAudioDeviceInfo outputDeviceInfo(
                 QAudioDeviceInfo::defaultOutputDevice());
     if (!outputDeviceInfo.isFormatSupported(m_format_output)) {
         m_format_output = outputDeviceInfo.nearestFormat(m_format_output);
     }

     m_audioOutput = new QAudioOutput(outputDeviceInfo,
                                      m_format_output, this);
     m_voicegenerator = new VoiceGenerator(m_format_output,
                                           getFrequency(),
                                           getVolume(),
                                           this);

     connect(m_audioOutput, SIGNAL(stateChanged(QAudio::State)),
             SLOT(outputStateChanged(QAudio::State)));
 }

void GuitarTuner::initAudioInput()
{
    m_format_input.setSampleRate(DataFrequencyHzInput);
    m_format_input.setCodec("audio/pcm");
    m_format_input.setSampleSize(16);
    m_format_input.setChannelCount(1);
    m_format_input.setByteOrder(QAudioFormat::LittleEndian);
    m_format_input.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo inputDeviceInfo(
                QAudioDeviceInfo::defaultInputDevice());
    if (!inputDeviceInfo.isFormatSupported(m_format_input)) {
        m_format_input = inputDeviceInfo.nearestFormat(m_format_input);
    }
    m_audioInfo  = new AudioInfo( m_format_input, this);
    m_audioInfo->start();
    connect(m_audioInfo, SIGNAL(update()), SLOT(printLevelSound));
    m_audioInput = new QAudioInput(inputDeviceInfo, m_format_input, this);
    m_analyzer = new VoiceAnalyzer(m_format_input, this);
    m_analyzer->setCutOffPercentage(getMicrophoneSensitivity());
}

qreal GuitarTuner::getVolumeFromSoundSlider() const
 {
     qreal value = ui->soundSlider->value();
     return value/ui->soundSlider->maximum();
 }

void GuitarTuner::updateFrequencyByToneIndex(int index)
 {

     switch (index) {
     case 0: {
             m_currentToneFrequency = FrequencyE;
             m_currentToneString = "E";
             break;
         }
     case 1: {
             m_currentToneFrequency = FrequencyA;
             m_currentToneString = "A";
             break;
         }
     case 2: {
             m_currentToneFrequency = FrequencyD;
             m_currentToneString = "D";
             break;
         }
     case 3: {
             m_currentToneFrequency = FrequencyG;
             m_currentToneString = "G";
             break;
         }
     case 4: {
             m_currentToneFrequency = FrequencyB;
             m_currentToneString = "B";
             break;
         }
     case 5: {
             m_currentToneFrequency = FrequencyE2;
             m_currentToneString = "e";
             break;
         }
     default: {
             qDebug() << "invalid index!" << index;
         }
     }
     ui->noteLabel->setText(m_currentToneString);
 }

qreal GuitarTuner::getVolume() const
 {
     return m_outputVolumeLevel;
 }

bool GuitarTuner::getMuteState() const
 {
     return m_muted;
 }

qreal GuitarTuner::getMicrophoneSensitivity() const
 {
     return m_inputVolumeLevel;
 }

bool GuitarTuner::isInputModeActive() const
{
    return !m_outputActive;
}

qreal GuitarTuner::getFrequency() const
 {
     return m_currentToneFrequency;
 }

void GuitarTuner::toggleSound(bool noSound)
 {
     if (!m_outputActive) {
         return;
     }
     m_muted = noSound;
     emit muteChanged(m_muted);
 }

void GuitarTuner::changeVolume()
 {
     qreal resultingAmplitude = getVolumeFromSoundSlider();
     qDebug() << "resultingAmplitude" << resultingAmplitude;
     if (m_outputActive) {
         m_outputVolumeLevel = resultingAmplitude;
         emit volumeChanged(resultingAmplitude);
     }
     else {
         m_inputVolumeLevel = resultingAmplitude;
         emit microphoneSensitivityChanged(1.0-resultingAmplitude);
     }
 }

void GuitarTuner::toggleInputOrOutput()
 {
     if (m_outputActive) {
         m_outputActive = false;
         ui->soundSlider->setValue(m_inputVolumeLevel*100);
         ui->soundButton->setDisabled(true);
         ui->soundButton->hide();
         ui->micSensitivityLabel->show();
         emit modeChanged(true);
         ui->modeButton->setText("To tone mode");
     } else {
         m_outputActive = true;
         ui->soundSlider->setValue(m_outputVolumeLevel*100);
         ui->soundButton->setDisabled(false);
         ui->micSensitivityLabel->hide();
         ui->soundButton->show();
         emit modeChanged(false);
         ui->modeButton->setText("To listen mode");
     }
 }

void GuitarTuner::lowVoice()
{
    if (ui->noteLabel->font().bold()) {
        QFont font;
        font.setBold(false);
        font.setUnderline(false);
        ui->noteLabel->setFont(font);
    }
}

void GuitarTuner::voiceDifference(qreal difference)
 {
     if (ui->noteLabel->font().bold()) {
         QFont font;
         font.setBold(false);
         font.setUnderline(false);
         ui->noteLabel->setFont(font);
     }
     ui->correctSoundSlider->setValue(difference*m_maximumPrecision);
 }

void GuitarTuner::correctFrequencyObtained()
{
    qDebug() << "CORRECT FREQUENCY";
    QFont font;
    font.setBold(true);
    font.setUnderline(true);
    ui->noteLabel->setFont(font);
}

void GuitarTuner::setMaximumVoiceDifference(int max)
 {
     Q_ASSERT(m_maximumPrecision != 0);
     ui->correctSoundSlider->setMaximum(max*m_maximumPrecision);
     ui->correctSoundSlider->setMinimum(-max*m_maximumPrecision);
     ui->correctSoundSlider->setTickInterval(max*m_maximumPrecision);
 }

void GuitarTuner::setMaximumPrecisionPerNote(int max)
 {
     m_maximumPrecision = max;
 }

void GuitarTuner::next()
{
    changeTone((m_currentToneIndex + 1) % 6);
}

void GuitarTuner::prev()
 {
     changeTone((m_currentToneIndex + 5) % 6);
 }

void GuitarTuner::changeTone(int newIndex)
{
    m_currentToneIndex = newIndex;
    updateFrequencyByToneIndex(m_currentToneIndex);
    qDebug() << "targetFrequencyChanged" << m_currentToneFrequency;
    emit targetFrequencyChanged(m_currentToneFrequency);
}

void GuitarTuner::outputStateChanged(QAudio::State state)
{
    if (QAudio::ActiveState == state && m_muted) {
        m_audioOutput->suspend();
    }
}

void GuitarTuner::muteStateChanged(bool isMuted)
 {
     if (isMuted) {
         m_audioOutput->suspend();
     }
     else {
         m_audioOutput->resume();
     }
 }

void GuitarTuner::targetFrequencyChanged(qreal targetFrequency)
{
    if (m_outputActive) {
        m_audioOutput->stop();
        m_voicegenerator->stop();
        m_voicegenerator->setFrequency(targetFrequency);
        m_voicegenerator->start();
        m_audioOutput->start(m_voicegenerator);

    }
    else {

        m_audioInput->stop();
        m_analyzer->stop();
        m_analyzer->start(targetFrequency);
        m_audioInput->start(m_analyzer);

    }
}

void GuitarTuner::modeChanged(bool isInput)
{
    if (isInput) {
        m_audioOutput->stop();
        m_voicegenerator->stop();
        m_analyzer->start(getFrequency());
        m_audioInput->start(m_analyzer);

    }
    else {
        m_audioInput->stop();
        m_analyzer->stop();
        if (m_voicegenerator->frequency() != getFrequency()) {
            m_voicegenerator->setFrequency(getFrequency());
        }

        m_voicegenerator->start();
        m_audioOutput->start(m_voicegenerator);
    }
}

void GuitarTuner::printLevelSound(){
    ui->level_val->setText(QString::number(20*log10(m_audioInfo->level())));
}
