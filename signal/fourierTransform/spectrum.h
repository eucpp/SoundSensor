#pragma once

//#include <QObject>
#include <QVector>
#include "spectrumElement.h"

/**
  * Класс-контейнер для спектра.
  */
class Spectrum
{
public:
    class IncorrectInputArray {};

    Spectrum();
    Spectrum(int size);
    // подразумевается, что в массиве все вещественные части расположены в первых N/2 ячейках,
    // комплексные в последних N/2 ячейках (со знаком минус)
    // (это всё для FFTReal)
    // size - размер входного массива, должен быть чётным числом
    Spectrum(RealNum array[], int size);

    void set(RealNum array[], int size);
    inline SpectrumElement&  operator[](int i);
    inline const SpectrumElement&  operator[](int i) const;
    int size() const;
    RealNum* data();
private:
    QVector<SpectrumElement> elements;
};

inline SpectrumElement& Spectrum::operator[](int i)
{
    return elements[i];
}

inline const SpectrumElement& Spectrum::operator[](int i) const
{
    return elements[i];
}

inline int Spectrum::size() const
{
    return elements.size();
}

