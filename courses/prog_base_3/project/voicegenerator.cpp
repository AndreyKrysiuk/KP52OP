#include "voicegenerator.h"

 const int BufferSizeMilliseconds = 100;

VoiceGenerator::VoiceGenerator(const QAudioFormat &format, qreal frequency, qreal amplitude, QObject *parent):
    QIODevice(parent),
    m_format(format),
    m_amplitude(0.5)
{
    Q_ASSERT(m_format.sampleSize() % 8 == 0);
    int sampleBytes = m_format.channelCount() * (m_format.sampleSize() / 8);
    qint64 samplesInBuffer = m_format.sampleRate() * BufferSizeMilliseconds / 1000 + 1;
    qint64 length = samplesInBuffer * sampleBytes;
    m_buffer.resize(length);
    m_max_position = 0;
    m_position = 0;
    m_amplitude = amplitude;
    setFrequency(frequency);
}

VoiceGenerator::~VoiceGenerator(){}

void VoiceGenerator::start()
{
    open(QIODevice::ReadOnly);
}

void VoiceGenerator::stop()
{
    close();
    m_position = 0;
}

void VoiceGenerator::setFrequency(qreal frequency)
{
    Q_ASSERT(1 / frequency < BufferSizeMilliseconds);
    this->m_frequency = frequency;
    refreshData();
}

void VoiceGenerator::setAmplitude(qreal amplitude)
{
    Q_ASSERT(amplitude >= 0);
    m_amplitude = amplitude;
    refreshData();
}

qreal VoiceGenerator::frequency()
{
    return m_frequency;
}

void VoiceGenerator::refreshData()
{
    const int channelBytes = m_format.sampleSize() / 8;
    const int sampleSize = m_format.channelCount() * channelBytes;
    const qint64 voiceOscillationsInBuffer = BufferSizeMilliseconds * m_frequency / 1000;
    const qint64 voiceSamplesInBuffer = voiceOscillationsInBuffer * m_format.sampleRate() / m_frequency;
    m_max_position = voiceSamplesInBuffer * sampleSize;
    qint64 dataGenerationLength = m_buffer.size();

    Q_ASSERT(m_max_position % (sampleSize) == 0);
    Q_ASSERT(dataGenerationLength <= m_buffer.size());

    uchar * ptr = reinterpret_cast<uchar *>(m_buffer.data());
    int sampleIndex = 0;
    while ( dataGenerationLength > 0){
        qreal realValue = 0;
        if(sampleIndex < voiceSamplesInBuffer){
            realValue = m_amplitude * qSin(2.0f * M_PI * m_frequency * qreal(sampleIndex % m_format.sampleRate()) / m_format.sampleRate());
        }
        for(int i = 0; i < m_format.channelCount(); i++){
            setValue(ptr, realValue);
            ptr += channelBytes;
            dataGenerationLength -= channelBytes;
        }
        sampleIndex++;
    }
}

void VoiceGenerator::setValue(uchar *ptr, qreal realValue)
{
    if(m_format.sampleSize() == 8)
    {
        quint8 value = 0;
        if(m_format.sampleType() == QAudioFormat::UnSignedInt)
        {
            value = static_cast<quint8>(qRound((1.0 + realValue) / 2 * M_MAX_AMPLITUDE_8BIT_SIGNED));

        } else if(m_format.sampleType() == QAudioFormat::SignedInt){
            value = static_cast<qint8>(qRound(realValue * M_MAX_AMPLITUDE_8BIT_SIGNED));
        }
        *reinterpret_cast<quint8*>(ptr) = value;
    } else if (m_format.sampleSize() == 16){
        quint16 value = 0;
        if (m_format.sampleType() == QAudioFormat::UnSignedInt){
            value = static_cast<quint16>(qRound((1.0 + realValue) / 2 * M_MAX_AMPLITUDE_16BIT_UNSIGNED));
        } else if (m_format.sampleType() == QAudioFormat::SignedInt) {
            value = static_cast<qint16>(qRound(realValue * M_MAX_AMPLITUDE_16BIT_SIGNED));
        }

        if (m_format.byteOrder() == QAudioFormat::LittleEndian)
            qToLittleEndian<qint16>(value, ptr);
        else
            qToBigEndian<qint16>(value, ptr);
    }
}

qint64 VoiceGenerator::bytesAvailable() const
{
    return m_max_position + QIODevice::bytesAvailable();
}

qint64 VoiceGenerator::readData(char *data, qint64 maxlen)
{
    qint64 total = 0;
    qint64 chunk = 0;
    while (total < maxlen){
        if(maxlen - total >= m_max_position - m_position){
            chunk = m_max_position - m_position;
            memcpy(data, m_buffer.constData() + m_position, chunk);
            m_position = 0;
        } else {
            chunk = maxlen - total;
            memcpy(data, m_buffer.constData() + m_position, chunk);
            m_position = (m_position + chunk) % m_max_position;
        }
        data += chunk;
        total += chunk;
    }
    return total;
}

qint64 VoiceGenerator::writeData(const char *data, qint64 maxlen)
{
    Q_UNUSED(data);
    Q_UNUSED(maxlen);

    return 0;
}
