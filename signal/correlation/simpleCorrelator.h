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
    void correlation(Signal signal, Signal pattern, RealNum* out) const;
signals:
    void correlationCalculated(double*) const;
};

#endif // SIMPLECORRELATOR_H
