#include "voiceanalyzer.h"

const static float CutOffScaler = 0.05;

const static int PrecisionPerNote = 4;

const static int TargetFrequencyParameter = 4;

VoiceAnalyzer::VoiceAnalyzer(const QAudioFormat &format, QObject * parent):
    QIODevice(parent),
    m_format(format),
    m_frequency(0),
    m_position(0),
    m_fftHelper(new FFT())
{
    Q_ASSERT(qFuzzyCompare(M_SAMPLE_COUNT_MULTIPLIER,
                           float(2)/(M_TWELTH_ROOT_OF_2 - 1.0)));
        m_totalSampleCount = qRound(qreal(PrecisionPerNote) * TargetFrequencyParameter * M_SAMPLE_COUNT_MULTIPLIER);
        m_samples.reserve(m_totalSampleCount);
        int i = 2;
        int j = 2;
        for(; i < TargetFrequencyParameter; i *=2){
            j++;
        }
        m_maximumVoiceDifference = j*12;

        setCutOffPercentage(CutOffScaler);
}

void VoiceAnalyzer::start(qreal frequency)
{
    m_stepSize = (qreal) 1.0 * m_format.sampleRate() / (TargetFrequencyParameter*2*frequency);
    m_frequency = frequency;
    open(QIODevice::WriteOnly);
}


void VoiceAnalyzer::stop()
{
    m_samples.clear();
    m_samples.reserve(m_totalSampleCount);
    close();
}

qint64 VoiceAnalyzer::writeData(const char *data, qint64 maxlen)
{
    const int channelBytes = m_format.sampleSize() / 8;
    int sampleSize = m_format.channelCount() * channelBytes;
    int m_stepSizeInBytes = m_stepSize*sampleSize;
    Q_ASSERT((m_position % sampleSize) == 0);
    const uchar * ptr = reinterpret_cast<const uchar *>(data);
    while(m_position < maxlen){
        if(m_samples.size() < m_totalSampleCount){
            m_samples.append(getValueInt16(ptr + m_position));
        } else {
            analyzeVoice();
            m_samples.clear();
            m_samples.reserve(m_totalSampleCount);
            m_position += ((m_stepSizeInBytes - 1 + maxlen - m_position) / m_stepSizeInBytes) * m_stepSizeInBytes;
            break;
        }
        m_position += m_stepSizeInBytes;
    }
    m_position -= maxlen;
    return maxlen;
}

qint16 VoiceAnalyzer::getValueInt16(const uchar *ptr)
{
    qint16 realValue = 0;
    if(m_format.sampleSize() == 8){
        const qint16 value = *reinterpret_cast<const quint8 *>(ptr);
        if(m_format.sampleType() == QAudioFormat::UnSignedInt){
            realValue = value - M_MAX_AMPLITUDE_8BIT_SIGNED - 1;
        } else if (m_format.sampleType() == QAudioFormat::SignedInt){
            realValue = value;
        }
    } else if(m_format.sampleSize() == 16){
        qint16 value = 0;
        if(m_format.byteOrder() == QAudioFormat::LittleEndian){
            value = qFromLittleEndian<quint16>(ptr);
        } else {
            value = qFromBigEndian<quint16>(ptr);
        }
        if(m_format.sampleType() == QAudioFormat::UnSignedInt){
            realValue = value - M_MAX_AMPLITUDE_16BIT_SIGNED - 1;
        } else if (m_format.sampleType() == QAudioFormat::SignedInt){
            realValue = value;
        }
    }
    return realValue;
}

void VoiceAnalyzer::setCutOffPercentage(qreal cutoff)
{
    cutoff = CutOffScaler * cutoff;
    if(m_format.sampleSize() == 8 ){
        float t = cutoff * m_totalSampleCount * M_MAX_AMPLITUDE_8BIT_SIGNED;
        m_fftHelper -> setCutOffFroDensity(t);
    } else if (m_format.sampleSize() == 16){
        float t = cutoff * m_totalSampleCount * M_MAX_AMPLITUDE_16BIT_SIGNED;
        m_fftHelper -> setCutOffFroDensity(t);
    }
}

qreal VoiceAnalyzer::frequency()
{
    return m_frequency;
}

int VoiceAnalyzer::getMaximumVoiceDifference()
{
    return m_maximumVoiceDifference;
}

int VoiceAnalyzer::getMaximumPrecisionPerNote()
{
    return PrecisionPerNote;
}

void VoiceAnalyzer::analyzeVoice()
{
    m_fftHelper->calculateFFT(m_samples);
    int index = m_fftHelper->getMaximumDensityIndex();

    if(index == -1)
    {
        emit lowVoice();
        qDebug() << "low voice";
        return;
    }

    qreal stepSizeInFrequency = (qreal)m_format.sampleRate() / (m_totalSampleCount * m_stepSize);
    qreal newFrequency = (qreal)(index) * stepSizeInFrequency;
    m_currentFrequency = newFrequency;

    int correctIndex = qRound(m_frequency / stepSizeInFrequency);
    qreal value = 0;

    if (m_frequency > newFrequency * TargetFrequencyParameter){

        qDebug() << "compare" << "low" << newFrequency << m_frequency - stepSizeInFrequency * correctIndex << (m_frequency - stepSizeInFrequency * correctIndex) / stepSizeInFrequency;
        value = -m_maximumVoiceDifference;
    } else if (m_frequency * TargetFrequencyParameter < newFrequency){
        qDebug() << "compare" << "high" << newFrequency << m_frequency - stepSizeInFrequency * correctIndex << ( m_frequency - stepSizeInFrequency * correctIndex) / stepSizeInFrequency;
        value = m_maximumVoiceDifference;
    } else {
        value = log(newFrequency / (stepSizeInFrequency * correctIndex)) * 12 / M_LN2;
        qDebug() << "compare" << value << newFrequency << m_frequency - stepSizeInFrequency * correctIndex << ( m_frequency - stepSizeInFrequency * correctIndex) / stepSizeInFrequency;
    }

    QVariant valueVar(value);
    emit voiceDifference(valueVar);

    if(correctIndex == index){
        emit(correctFrequency());
    }
}

qint64 VoiceAnalyzer::readData(char *data, qint64 maxlen)
 {
     Q_UNUSED(data);
     Q_UNUSED(maxlen);

     return 0;
 }

qreal VoiceAnalyzer::getCurrFrequency()
{
    return m_currentFrequency;
}
