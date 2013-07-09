#ifndef FFTREALWRAP_H
#define FFTREALWRAP_H

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
    fft.do_fft(out, in);
}

void inline FFTRealWrap::inverseFourierTransform(RealNum *in, RealNum *out)
{
    fft.do_ifft(out, in);
}

#endif // FFTREALWRAP_H
