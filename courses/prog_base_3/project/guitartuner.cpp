#include "guitartuner.h"
#include "ui_guitartuner.h"

#include <QMainWindow>
#include <math.h>
#include <windows.h>

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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(setNoteInChromatic()));
    timer->start(5);

    m_outputActive = false;
    m_muted = false;
    m_outputVolumeLevel = getVolumeFromSoundSlider();
    m_inputVolumeLevel = 1.0 - m_outputVolumeLevel;

    m_currentToneIndex = 5;


    updateFrequencyByToneIndex(m_currentToneIndex);

    connect(ui->soundSlider, SIGNAL(valueChanged(int)),
           SLOT(changeVolume()));
    connect(ui->modeButton, SIGNAL(clicked()),
           SLOT(toggleInputOrOutput()));
    connect(ui->buttonNext, SIGNAL(clicked()), SLOT(next()));
    connect(ui->buttonPrev, SIGNAL(clicked()), SLOT(prev()));

    initAudioInput();
    initAudioOutput();

    connect(this, SIGNAL(volumeChanged(qreal)), m_voicegenerator, SLOT(setAmplitude(qreal)));
    connect(this, SIGNAL(microphoneSensitivityChanged(qreal)),m_analyzer, SLOT(setCutOffPercentage(qreal)));
    connect(m_analyzer, SIGNAL(lowVoice()),this, SLOT(lowVoice()));
    connect(m_analyzer, SIGNAL(correctFrequency()), this, SLOT(correctFrequencyObtained()));

    modeChanged(m_outputActive);

    toggleInputOrOutput();
}

GuitarTuner::~GuitarTuner()
{
    delete ui;
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
             m_currentToneFrequency = stFrequencyE;
             m_currentToneString = "E";
             break;
         }
     case 1: {
             m_currentToneFrequency = stFrequencyA;
             m_currentToneString = "A";
             break;
         }
     case 2: {
             m_currentToneFrequency = stFrequencyD;
             m_currentToneString = "D";
             break;
         }
     case 3: {
             m_currentToneFrequency = stFrequencyG;
             m_currentToneString = "G";
             break;
         }
     case 4: {
             m_currentToneFrequency = stFrequencyB;
             m_currentToneString = "B";
             break;
         }
     case 5: {
             m_currentToneFrequency = stFrequencyE2;
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
         ui->micSensitivityLabel->show();
         emit modeChanged(true);
         ui->modeButton->setText("To tone mode");
     } else {
         m_outputActive = true;
         ui->soundSlider->setValue(m_outputVolumeLevel*100);
         ui->micSensitivityLabel->hide();
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

void GuitarTuner::correctFrequencyObtained()
{
    qDebug() << "CORRECT FREQUENCY";
    QFont font;
    font.setBold(true);
    font.setUnderline(true);
    ui->noteLabel->setFont(font);
}

void GuitarTuner::setMaximumPrecisionPerNote(int max)
 {
     m_maximumPrecision = max;
 }

void GuitarTuner::next()
{
    if(m_outputActive)
        changeTone((m_currentToneIndex + 1) % 6);
}

void GuitarTuner::prev()
{
    if(m_outputActive)
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

void GuitarTuner::setNoteInChromatic()
{
   qreal maxSliderRange = 0;
   qreal minSliderRange = 0;
   qreal currFrequency = m_analyzer->getCurrFrequency();
   if(currFrequency > 30 && !m_outputActive){
        for(int i = 0; i < 7; i++){
           if(currFrequency < frequencyE * pow(2, i) + (frequencyE - frequencyDmj) * pow(2,i - 1)
                   && currFrequency > frequencyE * pow(2, i) - (frequencyE - frequencyDmj) * pow(2,i - 1)){
               m_currentToneString = "E";
               maxSliderRange = frequencyE * pow(2, i) + (frequencyE - frequencyDmj) * pow(2,i - 1);
               minSliderRange = frequencyE * pow(2, i) - (frequencyE - frequencyDmj) * pow(2,i - 1);
               break;
           } else if(currFrequency < frequencyDmj * pow(2, i) + (frequencyDmj - frequencyD) * pow(2,i - 1)
                     && currFrequency > frequencyDmj * pow(2, i) - (frequencyDmj - frequencyD) * pow(2,i - 1)){
               m_currentToneString = "D#";
               maxSliderRange = frequencyDmj * pow(2, i) + (frequencyDmj - frequencyD) * pow(2,i - 1);
               minSliderRange = frequencyDmj * pow(2, i) - (frequencyDmj - frequencyD) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyD * pow(2, i) + (frequencyD - frequencyCmj) * pow(2, i - 1)
                     && currFrequency > frequencyD * pow(2, i) - (frequencyD - frequencyCmj) * pow(2, i - 1)){
               m_currentToneString = "D";
               maxSliderRange = frequencyD * pow(2, i) + (frequencyD - frequencyCmj) * pow(2,i - 1);
               minSliderRange = frequencyD * pow(2, i) - (frequencyD - frequencyCmj) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyCmj * pow(2, i) + (frequencyCmj - frequencyC) * pow(2,i - 1)
                     && currFrequency > frequencyCmj * pow(2, i) - (frequencyCmj - frequencyC) * pow(2,i - 1)){
               m_currentToneString = "C#";
               maxSliderRange = frequencyCmj * pow(2, i) + (frequencyCmj - frequencyC) * pow(2,i - 1);
               minSliderRange = frequencyCmj * pow(2, i) - (frequencyCmj - frequencyC) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyC * pow(2, i) + (frequencyC - frequencyB) * pow(2,i - 1)
                     && currFrequency > frequencyC * pow(2, i) - (frequencyC - frequencyB) * pow(2,i - 1)){
               m_currentToneString = "C";
               maxSliderRange = frequencyC * pow(2, i) + (frequencyC - frequencyB) * pow(2,i - 1);
               minSliderRange = frequencyC * pow(2, i) - (frequencyC - frequencyB) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyB * pow(2, i) + (frequencyB - frequencyAmj) * pow(2,i - 1)
                     && currFrequency > frequencyB * pow(2, i) - (frequencyB - frequencyAmj) * pow(2,i - 1)){
               m_currentToneString = "B";
               maxSliderRange = frequencyB * pow(2, i) + (frequencyB - frequencyAmj) * pow(2,i - 1);
               minSliderRange = frequencyB * pow(2, i) - (frequencyB - frequencyAmj) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyAmj * pow(2, i) + (frequencyAmj - frequencyA) * pow(2,i - 1)
                    && currFrequency > frequencyAmj * pow(2, i) - (frequencyAmj - frequencyA) * pow(2,i - 1)){
               m_currentToneString = "A#";
               maxSliderRange = frequencyAmj * pow(2, i) + (frequencyAmj - frequencyA) * pow(2,i - 1);
               minSliderRange = frequencyAmj * pow(2, i) - (frequencyAmj - frequencyA) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyA * pow(2, i) + (frequencyA - frequencyGmj) * pow(2,i - 1)
                     && currFrequency > frequencyA * pow(2, i) - (frequencyA - frequencyGmj) * pow(2,i - 1)){
               m_currentToneString = "A";
               maxSliderRange = frequencyA * pow(2, i) + (frequencyA - frequencyGmj) * pow(2,i - 1);
               minSliderRange = frequencyA * pow(2, i) - (frequencyA - frequencyGmj) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyGmj * pow(2, i) + (frequencyGmj - frequencyG) * pow(2,i - 1)
                     && currFrequency > frequencyGmj * pow(2, i) - (frequencyGmj - frequencyG) * pow(2,i - 1)){
               m_currentToneString = "G#";
               maxSliderRange = frequencyGmj * pow(2, i) + (frequencyGmj - frequencyG) * pow(2,i - 1);
               minSliderRange = frequencyGmj * pow(2, i) - (frequencyGmj - frequencyG) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyG * pow(2, i) + (frequencyG - frequencyFmj) * pow(2,i - 1)
                     && currFrequency > frequencyG * pow(2, i) - (frequencyG - frequencyFmj) * pow(2,i - 1)){
               m_currentToneString = "G";
               maxSliderRange = frequencyG * pow(2, i) + (frequencyG - frequencyFmj) * pow(2,i - 1);
               minSliderRange = frequencyG * pow(2, i) - (frequencyG - frequencyFmj) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyFmj * pow(2, i) + (frequencyFmj - frequencyF) * pow(2,i - 1)
                     && currFrequency > frequencyFmj * pow(2, i) - (frequencyFmj - frequencyF) * pow(2,i - 1)){
               m_currentToneString = "F#";
               maxSliderRange = frequencyFmj * pow(2, i) + (frequencyFmj - frequencyF) * pow(2,i - 1);
               minSliderRange = frequencyFmj * pow(2, i) - (frequencyFmj - frequencyF) * pow(2,i - 1);
               break;

           } else if(currFrequency < frequencyF * pow(2, i) + (frequencyF - frequencyE/2) * pow(2,i - 1)
                     && currFrequency > frequencyF * pow(2, i) - (frequencyF - frequencyE/2) * pow(2,i - 1)){          
               m_currentToneString = "F";
               maxSliderRange = frequencyF * pow(2, i) + (frequencyF - frequencyE/2) * pow(2,i - 1);
               minSliderRange = frequencyF * pow(2, i) - (frequencyF - frequencyE/2) * pow(2,i - 1);
               break;
           }
        }
   }
   ui->noteLabel->setText(m_currentToneString);
   ui->FrequencySlider->setRange(minSliderRange,  maxSliderRange);
   ui->FrequencySlider->setValue(currFrequency);
   Sleep(50);
}
