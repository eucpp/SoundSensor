#ifndef CORRELATIORSTIMETEST_H
#define CORRELATIORSTIMETEST_H

#include <ctime>
#include <iostream>
#include <QObject>
#include <QtTest>
#include "fftCorrelator.h"
#include "alglibCorrelator.h"
#include "../wavFile.h"

class CorrelatorsTimeTest : public QObject
{
    Q_OBJECT
private slots:
    void test()
    {
        try
        {
            WavFile signalFile("corr_test_signal.wav");
            signalFile.open(WavFile::ReadOnly);
            Signal signal = signalFile.readAll();
            WavFile patternFile("corr_test_pattern.wav");
            patternFile.open(WavFile::ReadOnly);
            Signal pattern = patternFile.readAll();

            QScopedArrayPointer<RealNum> corr(new RealNum[signal.size() + pattern.size() - 1]);
            QScopedArrayPointer<RealNum> s(signal.toFixedPointArray());
            QScopedArrayPointer<RealNum> p(signal.toFixedPointArray());

            clock_t time1 = clock();
            FFTCorrelator().correlation(s.data(), signal.size(), p.data(), pattern.size(), corr.data());
            clock_t time2 = clock();
            std::cout << "Algorythm using FFTReal time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;

            time1 = clock();
            AlglibCorrelator().correlation(signal, pattern);
            time2 = clock();
            std::cout << "Alglib algorythm time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
        }
        catch (WavFile::OpenFileExc)
        {
            QFAIL("Test files don't found!");
        }
    }
};

#endif // CORRELATIORSTIMETEST_H
