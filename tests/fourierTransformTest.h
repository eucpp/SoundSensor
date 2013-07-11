#ifndef FOURIERTRANSFORMTEST_H
#define FOURIERTRANSFORMTEST_H

#include <ctime>
#include <cmath>
#include <iostream>
#include <QObject>
#include <QtTest/QtTest>
#include "../fourierTransform.h"
#include "../fftrealWrap.h"

class FourierTransformTest : public QObject
{
    Q_OBJECT
private slots:
    // тестируем Фурье на функции с известным спектром.
    void FTTest()
    {
        const int size = 64;
        QScopedPointer<FourierTransform> ft(new FFTRealWrap(size));

        QScopedArrayPointer<RealNum> signal(new RealNum[size]);
        for (int i = 0; i < size; i++)
            signal[i] = RealNum(3 * cos(2 * Pi * i / 16));
        QScopedArrayPointer<RealNum> spectrum(new RealNum[size]);
        ft->fourierTransform(signal.data(), spectrum.data());

        for (int i = 0; i < size; i++)
            if (i != 4)
                QVERIFY(qAbs(spectrum[i] - 0) < eps);
        QVERIFY(qAbs(spectrum[4] - 96) < eps);
    }
    // считаем прямое и обратное БПФ и сравниваем исходный сигнал с получившимся после преобразований
    void IFTTest()
    {
        const int size = 8;
        QScopedPointer<FourierTransform> ft(new FFTRealWrap(size));

        QScopedArrayPointer<RealNum> signal(new RealNum[size]);
        for (int i = 0; i < size; i++)
            signal[i] = cos(2* Pi * i / size);
        QScopedArrayPointer<RealNum> spectrum(new RealNum[size]);
        ft->fourierTransform(signal.data(), spectrum.data());
        QScopedArrayPointer<RealNum> newSignal(new RealNum[size]);
        ft->inverseFourierTransform(spectrum.data(), newSignal.data());

        for (int i = 0; i < size; i++)
        {
            newSignal[i] = newSignal[i] / size;
            QVERIFY(qAbs(newSignal[i] - signal[i]) < eps);
        }
    }

private:
    static const RealNum Pi;
    static const RealNum eps;
};


#endif // FOURIERTRANSFORMTEST_H
