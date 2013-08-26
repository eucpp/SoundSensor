#ifndef HANNWINDOW_H
#define HANNWINDOW_H

#include <cmath>
#include "windowFunction.h"

class HannWindow : public WindowFunction
{
public:
    HannWindow(int windowWidth);
    double operator()(double n);
private:
    int width;

    static const double Pi;
};

#endif // HANNWINDOW_H
