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
        Signal signal(8);
        signal[0] = (char)0;
        signal[1] = (char)10;
        signal[2] = (char)20;
        signal[3] = (char)100;
        signal[4] = (char)80;
        signal[5] = (char)-100;
        signal[6] = (char)-10;
        signal[7] = (char)0;
        Signal pattern(4);
        pattern[0] = (char)0;
        pattern[1] = (char)10;
        pattern[2] = (char)10;
        pattern[3] = (char)10;

        QScopedArrayPointer<RealNum> corr(new RealNum[8 + 4 - 1]);
        correlator->correlation(signal, pattern, corr.data());

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
            correlator->correlation(signal, pattern, corr.data());


            int max = 0;
            for (int i = 1; i < signal.size() + pattern.size() - 1; i++)
                if (corr[max] < corr[i])
                    max = i;

            std::cout << "MAX: " << max << std::endl;
            // погрешность максимума корреляции = 10 миллисекунд
            QVERIFY(qAbs(max - 14633) < 10 * signal.getFormat().sampleRate() / 1000);
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
