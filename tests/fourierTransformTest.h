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
        Spectrum spectrum = ft->fourierTransform(signal);

        float error[size];
        for (int i = 0; i < spectrum.size(); i++)
        {
            std::cout << "Спектр [" << i << "] Re: " << realNumToFloat(spectrum[i].getRe())
                      << ", Im: " << realNumToFloat(spectrum[i].getIm()) << std::endl;
            if (i == 4)
                error[i] = realNumToFloat(spectrum[i].getRe() / 96);
            else
                error[i] = realNumToFloat((spectrum[i].getRe() + 1) / 1);
            error[size / 2 + i] = realNumToFloat((spectrum[i].getIm() + 1) / 1);
        }

        int errInd = 0;
        for (int i = 1; i < size; i++)
            if (qAbs(error[i] - 1) > qAbs(error[errInd] - 1))
                errInd = i;
        std::cout << "Max Error: " << error[errInd] << ",  at pos: " << errInd << std::endl;


        for (int i = 0; i < spectrum.size(); i++)
            if (i != 4)
            {
                QVERIFY(qAbs(spectrum[i].getRe() - 0) < eps);
                QVERIFY(qAbs(spectrum[i].getIm() - 0) < eps);
            }
        QVERIFY(qAbs(spectrum[4].getRe() - 96) < eps);
        QVERIFY(qAbs(spectrum[4].getIm() - 0) < eps);
    }
    // считаем прямое и обратное БПФ и сравниваем исходный сигнал с получившимся после преобразований
    void IFTTest()
    {
        const int size = 8;
        QScopedPointer<FourierTransform> ft(new FFTRealWrap(size));

        Signal signal(size);
        for (int i = 0; i < size; i++)
            signal[i] = cos(2* Pi * i / size);
        Spectrum spectrum = ft->fourierTransform(signal);
        Signal newSignal = ft->inverseFourierTransform(spectrum);

        float error[size];
        for (int i = 0; i < size; i++)
        {
            newSignal[i] = newSignal[i].toFloat() / size;
            std::cout << "origin [" << i << "] = " << signal[i].toFloat();
            std::cout << "; ifft [" << i << "] = " << newSignal[i].toFloat() << std::endl;

            if ((newSignal[i].toFloat() == 0) || (signal[i].toFloat() == 0))
                error[i] = (newSignal[i].toFloat() + 1) / (signal[i].toFloat() + 1);
            else
                error[i] = newSignal[i].toFloat() / signal[i].toFloat();

            QVERIFY(qAbs(newSignal[i].toFloat() - signal[i].toFloat()) < eps);
        }

        int errInd = 0;
        for (int i = 1; i < size; i++)
            if (qAbs(error[i] - 1) > qAbs(error[errInd] - 1))
                errInd = i;
        std::cout << "Max Error: " << error[errInd] << ",  at pos: " << errInd << std::endl;
    }

private:
    static const float Pi;
    static const float eps;
};


#endif // FOURIERTRANSFORMTEST_H
