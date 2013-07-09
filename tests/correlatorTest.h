#ifndef CORRELATORTEST_H
#define CORRELATORTEST_H

#include <iostream>
#include <QObject>
#include <QtTest/QtTest>
#include "../wavFile.h"
#include "../correlator.h"
#include "../alglibCorrelator.h"
#include "../simpleCorrelator.h"

class CorrelatorTest : public QObject
{
    Q_OBJECT
private slots:
    void init()
    {
        correlator = new AlglibCorrelator();
    }
    void cleanup()
    {
        delete correlator;
    }
    // простой тест для корреляции.
    // для данных сигналов максимум должен быть в позиции 1.
    void correlationTest1()
    {
        Signal signal(8);
        signal[0] = (short)0;
        signal[1] = (short)10;
        signal[2] = (short)20;
        signal[3] = (short)100;
        signal[4] = (short)80;
        signal[5] = (short)-100;
        signal[6] = (short)-10;
        signal[7] = (short)0;
        Signal pattern(4);
        pattern[0] = (short)0;
        pattern[1] = (short)10;
        pattern[2] = (short)10;
        pattern[3] = (short)10;

        alglib::real_1d_array correlation = correlator->correlation(signal, pattern);

        int max = 0;
        for (int i = 1; i < signal.size(); i++)
            if (correlation[max] < correlation[i])
                max = i;
        //delete[] correlation;

        QCOMPARE(max, 1);
    }
    // проверяем, бросается ли исключение, если размер шаблона больше размера сигнала
    void correlationTest2()
    {
        try
        {
            Signal signal(10);
            Signal pattern(20);
            correlator->correlation(signal, pattern);
            QFAIL("SignalsSizeExc must be thrown");
        }
        catch (Correlator::SignalsSizeExc)
        {}
    }

    // тест корреляции, использует тестовые wav файлы
    void correlationTest3()
    {
        try
        {
            WavFile signalFile("corr_test_signal.wav");
            signalFile.open(WavFile::ReadOnly);
            Signal signal = signalFile.readAll();
            WavFile patternFile("corr_test_pattern.wav");
            patternFile.open(WavFile::ReadOnly);
            Signal pattern = patternFile.readAll();

            alglib::real_1d_array correlation = correlator->correlation(signal, pattern);

            int max = 0;
            for (int i = 1; i < signal.size(); i++)
                if (correlation[max] < correlation[i])
                    max = i;

            // погрешность максимума корреляции = 100 сэмплов
            QVERIFY(qAbs(max - 14633) < 100);
        }
        catch (WavFile::OpenFileExc)
        {
            QFAIL("Test files don't found!");
        }
    }

private:
    Correlator* correlator;
};
#endif // CORRELATORTEST_H
