#include "simpleCorrelator.h"

void SimpleCorrelator::correlation(RealNum* signal, int n, RealNum* pattern, int m, RealNum* out) const
{
    for (int i = 0; i < n; i++)
    {
        out[i] = 0;
        for (int j = 0; j < m; j++)
        {
            if (i + j < n)
                out[i] += signal[i + j] * pattern[j];
        }
    }
    //emit correlationCalculated(corr);
}
