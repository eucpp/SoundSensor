#include "simpleCorrelator.h"

void SimpleCorrelator::correlation(Signal signal, Signal pattern, RealNum* out) const
{
    for (int i = 0; i < signal.size(); i++)
    {
        out[i] = 0;
        for (int j = 0; j < pattern.size(); j++)
        {
            if (i + j < signal.size())
                out[i] += signal[i + j].toInt() * pattern[j].toInt();
        }
    }
    //emit correlationCalculated(corr);
}
