#ifndef FFTREALWRAP_H
#define FFTREALWRAP_H

#include <iostream>
#include <ctime>
#include "fftreal/ffft/FFTReal.h"
#include "fourierTransform.h"

class FFTRealWrap : public FourierTransform
{
public:
    FFTRealWrap(int length):
        fft(length)
    {}
    void inline fourierTransform(RealNum* in, RealNum* out);
    void inline inverseFourierTransform(RealNum* in, RealNum* out);
private:
    ffft::FFTReal<RealNum> fft;
};

void inline FFTRealWrap::fourierTransform(RealNum *in, RealNum *out)
{
    //clock_t time1 = clock();
    fft.do_fft(out, in);
    //clock_t time2 = clock();
    //std::cout << "Algorytm time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;
}

void inline FFTRealWrap::inverseFourierTransform(RealNum *in, RealNum *out)
{
    fft.do_ifft(in, out);
}

#endif // FFTREALWRAP_H
