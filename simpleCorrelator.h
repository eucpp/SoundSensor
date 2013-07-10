#ifndef SIMPLECORRELATOR_H
#define SIMPLECORRELATOR_H

#include "correlator.h"

/**
  * Простая реализация алгоритма корреляции.
  */
class SimpleCorrelator : public Correlator
{
    Q_OBJECT
public:
    void correlation(RealNum* signal, int n, RealNum* pattern, int m, RealNum* out) const;
signals:
    void correlationCalculated(double*) const;
};

#endif // SIMPLECORRELATOR_H
