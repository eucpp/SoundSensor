#include "simpleCorrelator.h"

alglib::real_1d_array SimpleCorrelator::correlation(Signal signal, Signal pattern) const
{
    if (pattern.size() > signal.size())
        throw SignalsSizeExc();

    double* corr = new double[signal.size()];
    for (int i = 0; i < signal.size(); i++)
    {
        corr[i] = 0;
        for (int j = 0; j < pattern.size(); j++)
        {
            if (i + j < signal.size())
                corr[i] += signal[i + j].toPcm16() * pattern[j].toPcm16();
        }
    }
    //emit correlationCalculated(corr);
    alglib::real_1d_array corrArray;
    corrArray.setcontent(signal.size(), corr);
    return corrArray;
}
