#ifndef FFTCORRELATOR_H
#define FFTCORRELATOR_H

#include <ctime>
#include <cstring>
#include <iostream>
#include <QObject>
#include <QFile>
#include "../fourierTransform/fourierTransform.h"
#include "../fourierTransform/fftrealWrap.h"
#include "correlator.h"

class FFTCorrelator : public Correlator
{
    Q_OBJECT
public slots:
    void correlation(Signal signal, Signal pattern, RealNum* out);
//signals:
//    void correlationCalculated(double*) const;
private:
    FourierTransform* ft;
};


#endif // FFTCORRELATOR_H
