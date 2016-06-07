#include "guitartuner.h"
#include "ui_guitartuner.h"


#include <math.h>
#include <QDateTime>
#include <QDebug>
#include <QPainter>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <qendian.h>

const int BufferSize = 4096;

GuitarTuner::GuitarTuner(QWidget *parent) :
    QDialog(parent),
    m_canvas(0),
    m_device(QAudioDeviceInfo::defaultInputDevice()),
    m_audioInfo(0),
    m_audioInput(0),
    m_input(0),
    m_pullMode(false),
    m_buffer(BufferSize, 0),
    ui(new Ui::GuitarTuner)
{

    initAudioOutput();
    initAudioInput();
    //ui->setupUi(this);
    initializeWindow();
    initializeAudio();

}

GuitarTuner::~GuitarTuner()
{
    delete ui;
}

AudioInfo::AudioInfo(const QAudioFormat &format, QObject *parent)
    :   QIODevice(parent)
    ,   m_format(format)
    ,   m_maxAmplitude(0)
    ,   m_level(0.0)

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

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    m_level = 0;
    setMinimumHeight(30);
    setMinimumWidth(200);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    painter.setPen(Qt::black);
    painter.drawRect(QRect(painter.viewport().left()+10,
                           painter.viewport().top()+10,
                           painter.viewport().right()-20,
                           painter.viewport().bottom()-20));
    if (m_level == 150.0)
        return;

    int pos = ((painter.viewport().right()-20)-(painter.viewport().left()+11))*m_level;
    painter.fillRect(painter.viewport().left()+11,
                     painter.viewport().top()+10,
                     pos,
                     painter.viewport().height()-21,
                     Qt::red);
}

void RenderArea::setLevel(qreal value)
{
    m_level = value;
    update();
}

void GuitarTuner::initializeWindow()
{
    //QScopedPointer<QWidget> window(new QWidget);
   QVBoxLayout *layout = new QVBoxLayout;

    m_canvas = new RenderArea(this);
    layout->addWidget(m_canvas);

    m_display = new QLineEdit;
    layout->addWidget(m_display);

    m_frequency = new QLineEdit;
    layout->addWidget(m_display);


    m_volumeSlider = new QSlider(Qt::Horizontal, this);
    m_volumeSlider->setRange(0, 100);
    m_volumeSlider->setValue(100);
    connect(m_volumeSlider, SIGNAL(valueChanged(int)), SLOT(sliderChanged(int)));
    layout->addWidget(m_volumeSlider);

    setLayout(layout);
}

void GuitarTuner::initializeAudio()
{
    m_pullMode = true;

    m_format.setSampleRate(8000);
    m_format.setChannelCount(1);
    m_format.setSampleSize(16);
    m_format.setSampleType(QAudioFormat::SignedInt);
    m_format.setByteOrder(QAudioFormat::LittleEndian);
    m_format.setCodec("audio/pcm");

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultInputDevice());
    if (!info.isFormatSupported(m_format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        m_format = info.nearestFormat(m_format);
    }

    m_audioInfo  = new AudioInfo( m_format, this);
    connect(m_audioInfo, SIGNAL(update()), SLOT(refreshDisplay()));
    connect(m_audioInfo, SIGNAL(update()), SLOT(refreshDisplay2()));

    createAudioInput();
}

void GuitarTuner::createAudioInput()
{
    m_audioInput = new QAudioInput(m_device, m_format, this);
    m_volumeSlider->setValue(m_audioInput->volume() * 100);
    m_audioInfo->start();
    m_audioInput->start(m_audioInfo);
}

void GuitarTuner::readMore()
{
    if (!m_audioInput)
        return;
    qint64 len = m_audioInput->bytesReady();
    if (len > BufferSize)
        len = BufferSize;
    qint64 l = m_input->read(m_buffer.data(), len);
    if (l > 0)
        m_audioInfo->write(m_buffer.constData(), l);
}


void GuitarTuner::refreshDisplay()
{
    m_canvas->setLevel(m_audioInfo->level());
}

void GuitarTuner::refreshDisplay2()
{
    m_display->setText(QString::number(20*log10(m_audioInfo->level())));
}

void GuitarTuner::sliderChanged(int value)
{
    if (m_audioInput)
        m_audioInput->setVolume(qreal(value) / 100);
}

void GuitarTuner::initAudioOutput()
{
    m_format_output.setSampleRate(DataFrequencyHzOutput);
    m_format_output.setCodec("audio/pcm");
    m_format_output.setSampleSize(16);
    m_format_output.setChannelCount(1);
    m_format_output.setByteOrder(QAudioFormat::LittleEndian);
    m_format_output.setSampleType(QAudioFormat::SignedInt);


    QAudioDeviceInfo outputDeviceInfo(QAudioDeviceInfo::defaultOutputDevice());
    if (!outputDeviceInfo.isFormatSupported(m_format_output))
            m_format_output = outputDeviceInfo.nearestFormat(m_format_output);

    m_audioOutput = new QAudioOutput(outputDeviceInfo, m_format_output, this);
    m_generator = new VoiceGenerator(m_format_output, 82.407, 0.5, this);
}

void GuitarTuner::initAudioInput()
{
    m_format_input.setSampleRate(DataFrequencyHzInput);
    m_format_input.setCodec("audio/pcm");
    m_format_input.setSampleSize(16);
    m_format_input.setChannelCount(1);
    m_format_input.setByteOrder(QAudioFormat::LittleEndian);
    m_format_input.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo inputDeviceInfo(QAudioDeviceInfo::defaultInputDevice());
    if (!inputDeviceInfo.isFormatSupported(m_format_input))
            m_format_input = inputDeviceInfo.nearestFormat(m_format_input);

    m_audioInput = new QAudioInput(inputDeviceInfo, m_format_input, this);
    m_analyzer = new VoiceAnalyzer(m_format_input, this);
    m_analyzer->setCutOffPercentage(0.5);

}

void GuitarTuner::targetFrequencyChanged(qreal targetFrequency)
{
    m_audioOutput->stop();
    m_generator->stop();

    m_generator->setFrequency(targetFrequency);

    m_generator->start();
    m_audioOutput->start();
}
