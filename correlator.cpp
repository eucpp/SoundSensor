#include "correlator.h"

Correlator::Correlator()
{}

Signal Correlator::calcCorrelation(Signal signal, Signal pattern)
{
    alglib::real_1d_array signalArray;
    signalArray.setcontent(signal.getSize(), signal.getData());
    alglib::real_1d_array patternArray;
    patternArray.setcontent(pattern.getSize(), pattern.getData());
    alglib::real_1d_array corrArray;
    alglib::corrr1d(signalArray, signal.getSize(), patternArray, pattern.getSize(), corrArray);

    double* copy = new double[signal.getSize()];
    for (unsigned int i = 0; i < pattern.getSize(); i++)
        copy[i] = corrArray[i];

    Signal correlation(copy, signal.getSize());
    emit correlationCalculated(correlation);
    return correlation;
}
