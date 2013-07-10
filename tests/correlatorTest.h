#ifndef CORRELATORTEST_H
#define CORRELATORTEST_H

#include <iostream>
#include <QObject>
#include <QtTest/QtTest>
#include "../wavFile.h"
#include "../correlator.h"
#include "../alglibCorrelator.h"
#include "../simpleCorrelator.h"
#include "../fftCorrelator.h"

class CorrelatorTest : public QObject
{
    Q_OBJECT
private slots:
    void init()
    {
        correlator = new FFTCorrelator();
    }
    void cleanup()
    {
        delete correlator;
    }
    // простой тест для корреляции.
    // для данных сигналов максимум должен быть в позиции 1.
    void correlationTest1()
    {
        QScopedArrayPointer<RealNum> signal(new RealNum[8]);
        signal[0] = 0;
        signal[1] = 10;
        signal[2] = 20;
        signal[3] = 100;
        signal[4] = 80;
        signal[5] = -100;
        signal[6] = -10;
        signal[7] = 0;
        QScopedArrayPointer<RealNum> pattern(new RealNum[4]);
        pattern[0] = 0;
        pattern[1] = 10;
        pattern[2] = 10;
        pattern[3] = 10;

        QScopedArrayPointer<RealNum> corr(new RealNum[8 + 4 - 1]);
        correlator->correlation(signal.data(), 8, pattern.data(), 4, corr.data());

        int max = 0;
        for (int i = 1; i < 8 + 4 - 1; i++)
            if (corr[max] < corr[i])
                max = i;

        QCOMPARE(max, 1);
    }

    /*
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
    */

    // тест корреляции, использует тестовые wav файлы
    void correlationTest2()
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
            QScopedArrayPointer<RealNum> s(signal.toFloatArray());
            QScopedArrayPointer<RealNum> p(pattern.toFloatArray());
            correlator->correlation(s.data(), signal.size(), p.data(), pattern.size(), corr.data());

            int max = 0;
            for (int i = 1; i < signal.size() + pattern.size() - 1; i++)
                if (corr[max] < corr[i])
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
