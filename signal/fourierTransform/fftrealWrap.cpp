#include "fftrealWrap.h"

Spectrum FFTRealWrap::fourierTransform(Signal signal)
{
    if (signal.size() != length)
        throw SizeExc();

    clock_t time1 = clock();
    QScopedArrayPointer<RealNum> ptrSignal(signal.toFloatArray());
    QScopedArrayPointer<RealNum> out(new RealNum[length]);
    clock_t time2 = clock();
    std::cout << "Init fft data time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

    time1 = clock();
    fourierTransform(ptrSignal.data(), out.data());
    time2 = clock();
    std::cout << "do_fft time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

    time1 = clock();
    Spectrum spectrum;
    spectrum.set(out.data(), length);
    time2 = clock();
    std::cout << "Spectrum object init: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

    return spectrum;
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
