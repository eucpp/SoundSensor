#pragma once

//#include <QObject>
#include <QVector>
#include <spectrumElement.h>

/**
  * Класс-контейнер для спектра.
  */
template <typename Type> class Spectrum
{
public:
    Spectrum(int size);
    Spectrum(std::complex<Type> array[], int size);

    void set(std::complex<Type> array[], int size);
    inline SpectrumElement<Type>&  operator[](int i);
    inline const SpectrumElement<Type>&  operator[](int i) const;
    int inline size() const;
private:
    typedef SpectrumElement<Type> Element;
    QVector<Element> elements;
};

template <typename Type>
Spectrum<Type>::Spectrum(int size):
    elements(size)
{}

template <typename Type>
Spectrum<Type>::Spectrum(std::complex<Type> array[], int size):
    elements(size)
{
    for (int i = 0; i < size; i++)
        elements[i] = array[i];
}

template <typename Type>
void Spectrum<Type>::set(std::complex<Type> array[], int size)
{
    elements.resize(size);
    for (int i = 0; i < size; i++)
        elements[i] = array[i];
}

template <typename Type>
inline SpectrumElement<Type>& Spectrum<Type>::operator[](int i)
{
    return elements[i];
}

template <typename Type>
inline const SpectrumElement<Type>& Spectrum<Type>::operator[](int i) const
{
    return elements[i];
}

template <typename Type>
int inline Spectrum<Type>::size() const
{
    return elements.size();
}

