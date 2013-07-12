#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "define.h"
#include "spectrum.h"
#include "signal.h"



/**
  * Абстрактный класс, предоставляет интерфейс для алгоритмов преобразования Фурье.
  */
class FourierTransform
{
public:
    class SizeExc {};

    virtual ~FourierTransform()
    {}
    virtual void fourierTransform(Signal signal, RealNum* spectrum) = 0;
    virtual Signal inverseFourierTransform(RealNum* spectrum) = 0;
};

#endif // FOURIERTRANSFORM_H
