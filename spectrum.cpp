#include "spectrum.h"

Spectrum::Spectrum():
    elements(0)
{}

Spectrum::Spectrum(int size):
    elements(size)
{}

Spectrum::Spectrum(RealNum array[], int size)
{
    if (size % 2 == 1)
        throw IncorrectInputArray();
    elements.resize(size / 2);
    for (int i = 0; i < size / 2; i++)
    {
        elements[i].setRe(array[i]);
        elements[i].setIm(-array[size / 2 + i]);
    }
}

void Spectrum::set(RealNum array[], int size)
{
    if (size % 2 == 1)
        throw IncorrectInputArray();
    elements.resize(size / 2);
    for (int i = 0; i < size / 2; i++)
    {
        elements[i].setRe(array[i]);
        elements[i].setIm(-array[size / 2 + i]);
    }
}

RealNum* Spectrum::data()
{
    int n = elements.size();
    RealNum* ptr = new RealNum[n * 2];
    for (int i = 0; i < elements.size(); i++)
    {
        ptr[i] = elements[i].getRe();
        ptr[n / 2 + i] = -elements[i].getIm();
    }
    return ptr;
}
