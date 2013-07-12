#include "fftrealWrap.h"

void FFTRealWrap::fourierTransform(Signal signal, RealNum *out)
{
    if (signal.size() != length)
        throw SizeExc();

    QScopedArrayPointer<RealNum> ptrSignal(signal.toFloatArray());
    fourierTransform(ptrSignal.data(), out);
}

Signal FFTRealWrap::inverseFourierTransform(RealNum* spectrum)
{
    QScopedArrayPointer<RealNum> ptrSignal(new RealNum[length]);
    inverseFourierTransform(spectrum, ptrSignal.data());
    return Signal(ptrSignal.data(), length);
}
