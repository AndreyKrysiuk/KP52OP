#ifndef GUITARTUNER_H
#define GUITARTUNER_H

#include <QTimer>
#include <QDialog>
#include <QAudioInput>
#include <QAudioOutput>
#include <QComboBox>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

#include "voiceanalyzer.h"
#include "voicegenerator.h"


const int DataFrequencyHzOutput = 44100;
const int DataFrequencyHzInput = 48000;

const qreal frequencyF = 43.65;
const qreal frequencyFmj = 46.25;
const qreal frequencyG = 49.00;
const qreal frequencyGmj = 51.9;
const qreal frequencyA = 55.00;
const qreal frequencyAmj = 58.26;
const qreal frequencyB = 61.74;
const qreal frequencyC = 65.41;
const qreal frequencyCmj = 69.30;
const qreal frequencyD = 73.91;
const qreal frequencyDmj = 77.78;
const qreal frequencyE = 82.41;

const qreal stFrequencyE = 82.407;
 const qreal stFrequencyA = 110.00;
 const qreal stFrequencyD = 146.83;
 const qreal stFrequencyG = 196.00;
 const qreal stFrequencyB = 246.94;
 const qreal stFrequencyE2 = 329.63;


#define MAX_INPUT_VALUE 50
#define MIN_INPUT_VALUE -50

namespace Ui {
class GuitarTuner;
}

class GuitarTuner : public QWidget
{
    Q_OBJECT

public:
    explicit GuitarTuner(QWidget *parent = 0);
    ~GuitarTuner();

     qreal getVolume() const;
     qreal getMicrophoneSensitivity() const;
     qreal getFrequency() const;

     bool getMuteState() const;
     bool isInputModeActive() const;

     int getScaleMaximumValue() const;
     void setMaximumVoiceDifference(int max);
     void setMaximumPrecisionPerNote(int max);


public slots:
     void toggleSound(bool off);
     void next();
     void prev();
     void changeVolume();
     void toggleInputOrOutput();

     void lowVoice();
     void correctFrequencyObtained();
     void modeChanged(bool isInput);
     void muteStateChanged(bool isMuted);
     void targetFrequencyChanged(qreal targetFrequency);
     void outputStateChanged(QAudio::State state);
     void setNoteInChromatic();

private:
     void initAudioOutput();
     void initAudioInput();

 signals:
     void volumeChanged(qreal volume);
     void microphoneSensitivityChanged(qreal sensitivity);
     void muteChanged(bool isMuted);

 private:

     qreal getVolumeFromSoundSlider() const;
     void updateFrequencyByToneIndex(int index);
     void changeTone(int newIndex);

     Ui::GuitarTuner *ui; 
     int m_currentToneIndex;
     int m_maximumPrecision;
     QString m_currentToneString;
     bool m_outputActive;
     bool m_muted;
     qreal m_outputVolumeLevel;
     qreal m_inputVolumeLevel;
     qreal m_currentToneFrequency;
     QAudioDeviceInfo m_device;
     QAudioInput *m_audioInput;
     QAudioOutput *m_audioOutput;
     QAudioFormat m_format_output;
     QAudioFormat m_format_input;
     VoiceGenerator *m_voicegenerator;
     VoiceAnalyzer *m_analyzer;
     QTimer * timer;
};




#endif // GUITARTUNER_H
