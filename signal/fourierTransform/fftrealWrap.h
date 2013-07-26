#ifndef FFTREALWRAP_H
#define FFTREALWRAP_H

#include <iostream>
#include <ctime>
#include "fftreal/ffft/FFTReal.h"
#include "fourierTransform.h"

class FFTRealWrap : public FourierTransform
{
public:
    FFTRealWrap(int transformLength):
        length(transformLength),
        fft(transformLength)
    {}
    Spectrum fourierTransform(Signal signal);
    Spectrum fourierTransform(Signal signal, WindowFunction* winFunc);
    Signal inverseFourierTransform(Spectrum spectrum);
private:
    inline void fourierTransform(RealNum* in, RealNum* out);
    inline void inverseFourierTransform(RealNum* in, RealNum* out);

    ffft::FFTReal<RealNum> fft;
    int length;
};

inline void FFTRealWrap::fourierTransform(RealNum *in, RealNum *out)
{
    //clock_t time1 = clock();
    fft.do_fft(out, in);
    //clock_t time2 = clock();
    //std::cout << "Algorytm time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;
}

inline void FFTRealWrap::inverseFourierTransform(RealNum *in, RealNum *out)
{
    fft.do_ifft(in, out);
}

#endif // FFTREALWRAP_H
