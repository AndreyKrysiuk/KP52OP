#ifndef GUITARTUNER_H
#define GUITARTUNER_H

#include <QTimer>
#include <QDialog>
#include <QAudioInput>
#include <QAudioOutput>
#include <QByteArray>
#include <QComboBox>
#include <QMainWindow>
#include <QObject>
#include <QPixmap>
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

class AudioInfo : public QIODevice
{
    Q_OBJECT

public:
    AudioInfo(const QAudioFormat &format, QObject *parent);
    ~AudioInfo();

    void start();
    void stop();

    qreal level() const { return m_level; }
    qreal m_freq;

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

private:
    const QAudioFormat m_format;
    quint32 m_maxAmplitude;
    qreal m_level; // 0.0 <= m_level <= 1.0

signals:
    void update();
};

class GuitarTuner : public QWidget
{
    Q_OBJECT

public:
    explicit GuitarTuner(QWidget *parent = 0);
    ~GuitarTuner();

    qreal getVolume() const;
     bool getMuteState() const;
     qreal getMicrophoneSensitivity() const;
     bool isInputModeActive() const;
     qreal getFrequency() const;
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
     void voiceDifference(qreal difference);
     void correctFrequencyObtained();


signals:

public slots:
    void modeChanged(bool isInput);
    void muteStateChanged(bool isMuted);
    void targetFrequencyChanged(qreal targetFrequency);
    void outputStateChanged(QAudio::State state);
    void currentFrequency();
    void printLevelSound();
    void setNoteInChromatic();

private:
     void initAudioOutput();
     void initAudioInput();

 signals:
    // void modeChanged(bool isInput);
     void volumeChanged(qreal volume);
     void microphoneSensitivityChanged(qreal sensitivity);
     void muteChanged(bool isMuted);
    // void targetFrequencyChanged(qreal targetFrequency);

 private:
     Ui::GuitarTuner *ui;
     void changeTone(int newIndex);
     qreal getVolumeFromSoundSlider() const;
     int m_currentToneIndex;
     QString m_currentToneString;
     qreal m_currentToneFrequency;
     void updateFrequencyByToneIndex(int index);
     bool m_outputActive;
     bool m_muted;
     qreal m_outputVolumeLevel;
     qreal m_inputVolumeLevel;
     int m_maximumPrecision;

     QAudioDeviceInfo m_device;
     AudioInfo *m_audioInfo;
     QAudioInput *m_audioInput;
     QAudioOutput *m_audioOutput;
     QAudioFormat m_format_output;
     QAudioFormat m_format_input;
     VoiceGenerator *m_voicegenerator;
     VoiceAnalyzer *m_analyzer;
     QTimer * timer;
};




#endif // GUITARTUNER_H
