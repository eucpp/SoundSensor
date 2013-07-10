#ifndef SPECTRUMELEMENT_H
#define SPECTRUMELEMENT_H

#include <complex>

template <typename Type> class SpectrumElement
{
public:
    SpectrumElement();
    SpectrumElement(const std::complex<Type>& z);

    void inline set(const std::complex<Type>& z);
    inline Type amplitude() const;
    inline Type phase() const;
private:
    std::complex<Type> value;
};

template <typename Type>
SpectrumElement<Type>::SpectrumElement():
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
inline Type SpectrumElement<Type>::amplitude() const
{
    return std::abs(value);
}

template <typename Type>
inline Type SpectrumElement<Type>::phase() const
{
    return std::arg(value);
}

#endif // SPECTRUMELEMENT_H
