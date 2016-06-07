#include "fft.h"


#include "fftpack.c"
// called by __ogg_fdrffti
static void drfti1(int n, float *wa, int *ifac);
void __ogg_fdrffti(int n, float *wsave, int *ifac);
void __ogg_fdcosqi(int n, float *wsave, int *ifac);
// вызывается drftf1
 void dradf2(int ido,int l1,float *cc,float *ch,float *wa1);
// вызывается drftf1
void dradf4(int ido,int l1,float *cc,float *ch,float *wa1,
        float *wa2,float *wa3);
// вызывается drftf1
 void dradfg(int ido,int ip,int l1,int idl1,float *cc,float *c1,
        float *c2,float *ch,float *ch2,float *wa);
// вызывается drftf1
 void drftf1(int n,float *c,float *ch,float *wa,int *ifac);
void __ogg_fdrfftf(int n,float *r,float *wsave,int *ifac);
 void dcsqf1(int n,float *x,float *w,float *xh,int *ifac);
void __ogg_fdcosqf(int n,float *x,float *wsave,int *ifac);
 void dradb2(int ido,int l1,float *cc,float *ch,float *wa1);
 void dradb3(int ido,int l1,float *cc,float *ch,float *wa1,
                          float *wa2);
 void dradb4(int ido,int l1,float *cc,float *ch,float *wa1,
        float *wa2,float *wa3);
 void dradbg(int ido,int ip,int l1,int idl1,float *cc,float *c1,
            float *c2,float *ch,float *ch2,float *wa);
void drftb1(int n, float *c, float *ch, float *wa, int *ifac);
void __ogg_fdrfftb(int n, float *r, float *wsave, int *ifac);
 void dcsqb1(int n,float *x,float *w,float *xh,int *ifac);
void __ogg_fdcosqb(int n,float *x,float *wsave,int *ifac);

FFT::FFT():
    m_waveFloat(0),
    m_workingArray(0),
    m_ifac(0),
    m_last_n(-1)
{
}

FFT::~FFT()
{
    if(m_waveFloat != 0){
        delete [] m_waveFloat;
    }
    if(m_workingArray != 0) {
        delete [] m_workingArray;
    }
    if(m_ifac != 0){
        delete [] m_ifac;
    }
}

void FFT::reserve(int n){
    Q_ASSERT(n > 0);
    if(m_waveFloat != 0){
        delete [] m_waveFloat;
    }
    if(m_workingArray != 0) {
        delete [] m_workingArray;
    }
    if(m_ifac != 0){
        delete [] m_ifac;
    }
    m_workingArray = new float[2*n +15];
    m_waveFloat = new float[n];
    m_ifac = new int[n];
    __ogg_fdrffti(n, m_workingArray, m_ifac);
    m_last_n = n;
}

void FFT::calculateFFT(QList<qint16> wave)
{
    const int n = wave.size();
    if(m_last_n != n){
        reserve(n);
    }
    for(int i = 0; i < n; i++){
        m_waveFloat[i] = (float) wave.at(i);
    }

    __ogg_fdrfftf(n, m_waveFloat, m_workingArray, m_ifac);
}

int FFT::getMaximumDensityIndex()
{
    const int halfN = m_last_n / 2;
    float maxDensity = 0;
    int maxDensityIndex = 0;
    float densitySquared = 0.f;
    for(int k = 1; k < halfN; k++){
        const float cosCoefficient = qAbs(m_waveFloat[2*k - 1]);
        const float sinCoefficient = qAbs(m_waveFloat[2*k]);

        densitySquared = pow(sinCoefficient, 2) + pow(cosCoefficient, 2);
        if(densitySquared > maxDensity){
            maxDensity = densitySquared;
            maxDensityIndex = k;
        }
    }

    if(m_cutOffForDensitySquared < maxDensity){
        return maxDensityIndex;
    } else {
        return -1;
    }
}

void FFT::setCutOffFroDensity(float cutoff)
{
    m_cutOffForDensitySquared = pow(cutoff, 2);
}
