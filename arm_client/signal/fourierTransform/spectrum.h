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
    Spectrum(RealNum array[], int size, int rate);

    void set(RealNum array[], int size, int rate);
    inline void setFrameSize(int fSize);
    inline int getFrameSize() const;
    inline void setSampleRate(int rate);
    inline int getSampleRate() const;
    inline SpectrumElement&  operator[](int i);
    inline const SpectrumElement&  operator[](int i) const;
    int size() const;
    RealNum* data();
private:
    QVector<SpectrumElement> elements;
    int frameSize;
    int sampleRate;
};


void Spectrum::setFrameSize(int fSize)
{
    frameSize = fSize;
}

int Spectrum::getFrameSize() const
{
    return frameSize;
}

void Spectrum::setSampleRate(int rate)
{
    sampleRate = rate;
}

int Spectrum::getSampleRate() const
{
    return sampleRate;
}

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

