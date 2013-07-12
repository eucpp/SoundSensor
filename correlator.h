#ifndef CORRELATOR_H
#define CORRELATOR_H

#include <QObject>
#include "Alglib/ap.h"
#include "define.h"
#include "signal.h"

/**
  * Абстрактный класс, предоставляет интерфейс для алгоритмов корреляции.
  */
class Correlator : public QObject
{
    Q_OBJECT
public:
    /**
      * Исключение, генерируемое, если размер шаблона больше размера сигнала.
      */
    //class SignalsSizeExc {};
    virtual ~Correlator()
    {}
public slots:
    virtual void correlation(Signal signal, Signal pattern, RealNum* out) = 0;
//signals:
    //void correlationCalculated(RealNum*) const;
};

#endif // CORRELATOR_H
