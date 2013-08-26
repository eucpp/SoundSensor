#include "fftCorrelator.h"

/*
void FFTCorrelator::correlation(Signal signal, Signal pattern, RealNum* out)
{
    //std::cout << "Signal size: " << n << std::endl;
    //std::cout << "Pattern size: " << m << std::endl;
    int n = signal.size();
    int m = pattern.size();

    int l = 2;
    while (l < n + m - 1)
        l *= 2;

    //std::cout << "FFT array length: " << l << std::endl;

    clock_t time1 = clock();
    signal.resize(l);
    clock_t time2 = clock();
    std::cout << "Init first array time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time3 = clock();
    pattern.resize(l);
    clock_t time4 = clock();
    std::cout << "Init second array time: " << (time4 - time3) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time5 = clock();
    ft = new FFTRealWrap(l);
    clock_t time6 = clock();
    std::cout << "Init fft time: " << (time6 - time5) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time7 = clock();
    Spectrum signalSpectrum = ft->fourierTransform(signal);
    clock_t time8 = clock();
    std::cout << "First fft time: " << (time8 - time7) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time9 = clock();
    Spectrum patternSpectrum = ft->fourierTransform(pattern);
    clock_t time10 = clock();
    std::cout << "Second fft time: " << (time10 - time9) / (CLOCKS_PER_SEC / 1000) << std::endl;


    clock_t time11 = clock();
    // перемножаем спектры, сохраняя результат в signalSpectrum
    for (int i = 0; i < l/2; i++)
    {
        RealNum re = signalSpectrum[i].getRe() * patternSpectrum[i].getRe() - signalSpectrum[i].getIm() * (-patternSpectrum[i].getIm());
        RealNum im =  -(signalSpectrum[i].getRe() * (-patternSpectrum[i].getIm()) + signalSpectrum[i].getIm() * patternSpectrum[i].getRe());
        signalSpectrum[i].setRe(re);
        signalSpectrum[i].setIm(im);
    }
    clock_t time12 = clock();
    std::cout << "Spectrum myltiply time: " << (time12 - time11) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time13 = clock();
    // обратное преобразование фурье, результат сохраняем в patternSpectrum
    Signal correlation = ft->inverseFourierTransform(signalSpectrum);
    clock_t time14 = clock();
    std::cout << "Ifft time: " << (time14 - time13) / (CLOCKS_PER_SEC / 1000) << std::endl;



    clock_t time15 = clock();
    //QScopedArrayPointer<RealNum> ptrCorrelation(correlation.toFixedPointArray());
    //memcpy(out, ptrCorrelation.data(), (n + m - 1) * sizeof(RealNum));
    for (int i = 0; i < n + m - 1; i++)
        out[i] = correlation[i].toInt();

    clock_t time16 = clock();
    std::cout << "Finalize time: " << (time16 - time15) / (CLOCKS_PER_SEC / 1000) << std::endl;

    clock_t time17 = clock();
    std::cout << "Total time: " << (time17 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

    return;
}
*/
