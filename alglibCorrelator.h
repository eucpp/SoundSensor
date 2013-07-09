#pragma once

#include <ctime>
#include <iostream>
#include <QObject>
#include "Alglib/ap.h"
#include "Alglib/alglibinternal.h"
#include "Alglib/fasttransforms.h"
#include "correlator.h"

/**
  * Реализация корреляции, использующая библиотеку alglib.
  */
class AlglibCorrelator : public Correlator
{
    Q_OBJECT
public slots:
    alglib::real_1d_array correlation(Signal signal, Signal pattern) const;
signals:
    void correlationCalculated(double*) const;
};

