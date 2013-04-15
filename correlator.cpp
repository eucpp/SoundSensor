#include "correlator.h"

Correlator::Correlator()
{}

Signal Correlator::calcCorrelation(Signal signal, Signal pattern)
{
    alglib::real_1d_array signalArray;
    signalArray.setcontent(signal.size(), signal.getData());
    alglib::real_1d_array patternArray;
    patternArray.setcontent(pattern.size(), pattern.getData());
    alglib::real_1d_array corrArray;
    alglib::corrr1d(signalArray, signal.size(), patternArray, pattern.size(), corrArray);


    // копируем массив, потому что real_1d_array удаляет свои данные в деструкторе
    double* copy = new double[signal.size()];
    for (unsigned int i = 0; i < pattern.size(); i++)
        copy[i] = corrArray[i];

    Signal correlation(copy, signal.size());
    emit correlationCalculated(correlation);
    return correlation;
}
