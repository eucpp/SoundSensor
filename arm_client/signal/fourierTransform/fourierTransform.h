#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H

#include "define.h"
#include "spectrum.h"
#include "../signal.h"
#include "windowFunction.h"



/**
  * Абстрактный класс, предоставляет интерфейс для алгоритмов преобразования Фурье.
  */
class FourierTransform
{
public:
    class SizeExc {};

    virtual ~FourierTransform()
    {}
    virtual Spectrum fourierTransform(Signal signal) = 0;
    virtual Spectrum fourierTransform(Signal signal, WindowFunction* winFunc) = 0;
    virtual Signal inverseFourierTransform(Spectrum spectrum) = 0;
};

#endif // FOURIERTRANSFORM_H
