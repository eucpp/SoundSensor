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
    alglib::real_1d_array correlation(Signal signal, Signal pattern) const;
signals:
    void correlationCalculated(double*) const;
};

#endif // SIMPLECORRELATOR_H
