#ifndef CORRELATIORSTIMETEST_H
#define CORRELATIORSTIMETEST_H

#include <ctime>
#include <iostream>
#include <QObject>
#include <QtTest>
#include "../signal/correlation/fftCorrelator.h"
#include "../signal/correlation/alglibCorrelator.h"
#include "../recording/wavFile.h"

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

            clock_t time1 = clock();
            FFTCorrelator().correlation(signal, pattern, corr.data());
            clock_t time2 = clock();
            std::cout << "Algorythm using FFTReal time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;

            time1 = clock();
            alglib::real_1d_array aCorr = AlglibCorrelator().correlation(signal, pattern);
            time2 = clock();
            std::cout << "Alglib algorythm time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << "ms" << std::endl;

            int size = signal.size() + pattern.size() - 1;
            float error[size];
            for (int i = 0 ; i < size; i++)
            {
                RealNum c(aCorr[i]);
                if ((corr[i] == 0) || (c == 0))
                    error[i] = realNumToFloat((corr[i] + 1) / (c + 1));
                else
                    error[i] = realNumToFloat(corr[i] / c);
            }

            int errInd = 0;
            float aver = error[0];
            for (int i = 1; i < size; i++)
            {
                if (qAbs(error[i] - 1) > qAbs(error[errInd] - 1))
                    errInd = i;
                aver += error[i];
            }
            std::cout << "Max Error: " << error[errInd] << ",  at pos: " << errInd << std::endl;
            std::cout << "Average: " << aver / size << std::endl;
            std::cout << size << std::endl;
        }
        catch (WavFile::OpenFileExc)
        {
            QFAIL("Test files don't found!");
        }
    }
};

#endif // CORRELATIORSTIMETEST_H
