#ifndef VOICEGENERATOR_H
#define VOICEGENERATOR_H

#include <QIODevice>
#include <QByteArray>
#include <QAudioFormat>
#include <QtCore/qmath.h>
#include <QtCore/qendian.h>
#include <QDebug>

#include "voiceanalyzer.h"

class VoiceGenerator : public QIODevice
{
    Q_OBJECT
public:
    VoiceGenerator(const QAudioFormat &format, qreal frequency, qreal amplitude, QObject *parent = 0);
    ~VoiceGenerator();
    void setFrequency(qreal frequency);
    qint64 readData(char * data, qint64 maxlen);
    qint64 writeData(const char * data, qint64 maxlen);
    qint64 bytesAvailable() const;
    qreal frequency();

public slots:
    void setAmplitude(qreal amplitude);
    void start();
    void stop();

private:
    void setValue(uchar *ptr, qreal realValue);
    void refreshData();

    const QAudioFormat m_format;
    QByteArray m_buffer;
    qint64 m_position;
    qint64 m_max_position;
    qreal m_amplitude;
    qreal m_frequency;


};

#endif // VOICEGENERATOR_H
