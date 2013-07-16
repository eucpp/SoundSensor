#ifndef SPECTRUMELEMENT_H
#define SPECTRUMELEMENT_H

#include "define.h"
#include <cmath>

class SpectrumElement
{
public:
    class ComplexNullPhaseUndefExc {};

    inline SpectrumElement();
    inline SpectrumElement(RealNum rePart, RealNum imPart);

    inline void set(RealNum rePart, RealNum imPart);
    inline void setRe(RealNum val);
    inline RealNum getRe();
    inline void setIm(RealNum val);
    inline RealNum getIm();
    inline float amplitude() const;
    inline float phase() const;
private:
    RealNum re;
    RealNum im;
};

inline SpectrumElement::SpectrumElement():
    re(0),
    im(0)
{}

inline SpectrumElement::SpectrumElement(RealNum rePart, RealNum imPart):
    re(rePart),
    im(imPart)
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
    return sqrt(realNumToFloat(re*re + im*im));
}

inline float SpectrumElement::phase() const
{
    if ((re == (RealNum)0) && (im == (RealNum)0))
        throw ComplexNullPhaseUndefExc();
    return atan2(realNumToFloat(im), realNumToFloat(re));
}

#endif // SPECTRUMELEMENT_H
