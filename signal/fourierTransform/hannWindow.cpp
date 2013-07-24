#include "hannWindow.h"

const double HannWindow::Pi = 3.1415926535897932384626433832795;

HannWindow::HannWindow(int windowWidth):
    width(windowWidth)
{}

double HannWindow::operator()(double n)
{
    return (0.5 * (1 - cos(2 * Pi * n / (width - 1))));
}
