#ifndef VOICEANALYZER_H
#define VOICEANALYZER_H

#define M_MAX_AMPLITUDE_8BIT_SIGNED 127
#define M_MAX_AMPLITUDE_8BIT_UNSIGNED 255
#define M_MAX_AMPLITUDE_16BIT_SIGNED 32767
#define M_MAX_AMPLITUDE_16BIT_UNSIGNED 65535

#define M_TWELTH_ROOT_OF_2 1.05946309435930000000

// M_SAMPLE_COUNT_MULTIPLIER is 2/(M_TWELTH_ROOT_OF_2 - 1)
#define M_SAMPLE_COUNT_MULTIPLIER 33.63430749021150000000


#include <QObject>
#include <QAudioFormat>
#include <QDebug>
#include <qmath.h>
#include <qendian.h>
#include <QVariant>

#include "fft.h"

class VoiceAnalyzer : public QIODevice
{
    Q_OBJECT
public:
    VoiceAnalyzer(const QAudioFormat &format, QObject * parent = 0);
    qint64 writeData(const char *data, qint64 maxlen);
    qint64 readData(char *data, qint64 maxlen);
    void start(qreal frequency);
    void stop();
    qreal frequency();
    int getMaximumVoiceDifference();
    int getMaximumPrecisionPerNote();

public slots:
    void setCutOffPercentage(qreal cutoff);

private:
    const QAudioFormat m_format;
    QList<qint16> m_samples;
    int m_totalSampleCount;
    int m_maximumVoiceDifference;

    qint16 getValueInt16(const uchar * ptr);
    int m_stepSize;
    qreal m_frequency;
    qint64 m_position;
    FFT * m_fftHelper;
    void analyzeVoice();

signals:
    void voiceDifference(QVariant frequency);
    void correctFrequency();
    void lowVoice();
};

#endif // VOICEANALYZER_H

