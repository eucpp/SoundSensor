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

        Signal signal(size);
        // тут надо переделать, убрать коэфф. 3 перед косинусом
        for (int i = 0; i < size; i++)
            signal[i] = 3 * cos(2 * Pi * i / 16);
        QScopedArrayPointer<RealNum> spectrum(new RealNum[size]);
        ft->fourierTransform(signal, spectrum.data());

        /*
        for (int i = 0; i < size; i++)
            std::cout << "Спектр [" << i << "]" << spectrum[i] << std::endl;
        */
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

        Signal signal(size);
        for (int i = 0; i < size; i++)
            signal[i] = cos(2* Pi * i / size);
        QScopedArrayPointer<RealNum> spectrum(new RealNum[size]);
        ft->fourierTransform(signal, spectrum.data());
        Signal newSignal = ft->inverseFourierTransform(spectrum.data());

        for (int i = 0; i < size; i++)
        {
            newSignal[i] = newSignal[i].toFloat() / size;
            QVERIFY(qAbs(newSignal[i].toFloat() - signal[i].toFloat()) < eps);
        }
    }

private:
    static const RealNum Pi;
    static const RealNum eps;
};


#endif // FOURIERTRANSFORMTEST_H
