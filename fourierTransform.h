#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "spectrum.h"
#include "signal.h"

typedef float RealNum;

/**
  * Абстрактный класс, предоставляет интерфейс для алгоритмов преобразования Фурье.
  */
class FourierTransform
{
public:
    virtual ~FourierTransform()
    {}
    virtual void fourierTransform(RealNum* in, RealNum* out) = 0;
    virtual void inverseFourierTransform(RealNum* in, RealNum* out) = 0;
};

#endif // FOURIERTRANSFORM_H
