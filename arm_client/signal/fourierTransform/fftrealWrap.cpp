#include "fftrealWrap.h"

/*
Spectrum FFTRealWrap::fourierTransform(Signal signal)
{
    if (signal.size() != length)
        throw SizeExc();

    QScopedArrayPointer<RealNum> ptrSignal(signal.toFloatArray());
    QScopedArrayPointer<RealNum> out(new RealNum[length]);

    fourierTransform(ptrSignal.data(), out.data());

    Spectrum spectrum;
    spectrum.set(out.data(), length, signal.getFormat().sampleRate());

    return spectrum;

}

Spectrum FFTRealWrap::fourierTransform(Signal signal, WindowFunction* winFunc)
{
    Signal frame(signal.toFloatArray(), signal.size());
    for (int i = 0; i < signal.size(); i++)
    {
        frame[i] = (*winFunc)(static_cast<float>(frame[i].toPcm16()));
    }

    return fourierTransform(frame);
}

Signal FFTRealWrap::inverseFourierTransform(Spectrum spectrum)
{
    QScopedArrayPointer<RealNum> ptrSignal(new RealNum[length]);
    QScopedArrayPointer<RealNum> ptrSpectrum(spectrum.data());
    inverseFourierTransform(ptrSpectrum.data(), ptrSignal.data());
    Signal signal(length);
    for (int i = 0; i < length; i++)
        signal[i] = realNumToFloat(ptrSignal[i]);
    return signal;
}
*/
