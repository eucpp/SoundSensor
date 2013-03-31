#pragma once

#include <QObject>
#include <QByteArray>
#include "Alglib/ap.h"
#include "Alglib/alglibinternal.h"
#include "Alglib/fasttransforms.h"
#include "utils.h"

/**
  * Класс служит для выполнения операций корреляции сигналов
  */
class Correlator : public QObject
{
    Q_OBJECT
public:
    Correlator();
public slots:
    void calcCorrelation(QByteArray signalBytes, QByteArray patternBytes);
signals:
    void correlationCalculated(double*, unsigned int);
};

