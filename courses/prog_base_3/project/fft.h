#ifndef FFT_H
#define FFT_H

#include <Qlist>
#include <QObject>

class FFT : public QObject
{
    Q_OBJECT

public:
    FFT();
    ~FFT();
    void reserve(int n);
    void calculateFFT(QList<qint16> wave);
    int getMaximumDensityIndex();
    void setCutOffFroDensity(float cutoff);

private:
    float *m_waveFloat;
    float *m_workingArray;
    int *m_ifac;
    int m_last_n;
    float m_cutOffForDensitySquared;
};

#endif // FFT_H
