#ifndef SPECTRUMELEMENT_H
#define SPECTRUMELEMENT_H

#include <complex>

template <typename Type> class SpectrumElement
{
public:
    SpectrumElement();
    SpectrumElement(const std::complex<Type>& z);

    void inline set(const std::complex<Type>& z);
    Type inline amplitude() const;
    Type inline phase() const;
private:
    std::complex<Type> value;
};

template <typename Type>
SpectrumElement::SpectrumElement<Type>():
    value(0)
{}

template <typename Type>
SpectrumElement<Type>::SpectrumElement(const std::complex<Type>& z):
    value(z)
{}

template <typename Type>
void inline SpectrumElement<Type>::set(const std::complex<Type>& z)
{
    value = z;
}

template <typename Type>
Type inline SpectrumElement<Type>::amplitude() const
{
    return std::abs(value);
}

template <typename Type>
Type inline SpectrumElement<Type>::phase() const
{
    return std::arg(value);
}

#endif // SPECTRUMELEMENT_H
