#ifndef SPECTRUMELEMENT_H
#define SPECTRUMELEMENT_H

#include "define.h"
#include <cmath>

class SpectrumElement
{
public:
    class ComplexNullPhaseUndefExc {};

    inline SpectrumElement();
    inline SpectrumElement(int freq);
    inline SpectrumElement(RealNum rePart, RealNum imPart);
    inline void set(RealNum rePart, RealNum imPart);
    inline void setRe(RealNum val);
    inline RealNum getRe();
    inline void setIm(RealNum val);
    inline RealNum getIm();
    inline float amplitude() const;
    inline float phase() const;
    inline int getFrequency() const;
    inline void setFrequency(int freq);
private:
    float re;
    float im;
    int frequency;
};

inline SpectrumElement::SpectrumElement():
    re(0),
    im(0),
    frequency(0)
{}

SpectrumElement::SpectrumElement(int freq):
    re(0),
    im(0),
    frequency(freq)
{
}

inline SpectrumElement::SpectrumElement(RealNum rePart, RealNum imPart):
    re(rePart),
    im(imPart),
    frequency(0)
{}

void inline SpectrumElement::set(RealNum rePart, RealNum imPart)
{
    re = rePart;
    im = imPart;
}

void inline SpectrumElement::setRe(RealNum val)
{
    re = val;
}

RealNum SpectrumElement::getRe()
{
    return re;
}

void inline SpectrumElement::setIm(RealNum val)
{
    im = val;
}

RealNum SpectrumElement::getIm()
{
    return im;
}

inline float SpectrumElement::amplitude() const
{
    return sqrt(re*re + im*im);
}

inline float SpectrumElement::phase() const
{
    if ((re == (RealNum)0) && (im == (RealNum)0))
        throw ComplexNullPhaseUndefExc();
    return atan2(realNumToFloat(im), realNumToFloat(re));
}

int SpectrumElement::getFrequency() const
{
    return frequency;
}

void SpectrumElement::setFrequency(int freq)
{
    frequency = freq;
}


#endif // SPECTRUMELEMENT_H
