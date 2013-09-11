#pragma once

#include <QObject>
#include <QByteArray>
#include <QtTest/QtTest>

#include "signal/signal.h"

class SignalTest : public QObject
{
    Q_OBJECT
private slots:
    // операторы доступа к сэмплам (operator[]) косвенно тестируются в SampleTest.h

    // тестирование создания объекта-сигнала из QByteArray
    void ConstructFromQByteArrayTest()
    {
        QAudioFormat format = createFormat();

        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0x7F); // = 32767 ~ 1.0
        bytes.append(static_cast<char>(0));
        bytes.append(static_cast<char>(0)); // = 0
        bytes.append(static_cast<char>(0));
        bytes.append(0xC0); // = -16384 ~ -0.5
        bytes.append(0x01);
        bytes.append(0xA0); // = -24575 ~ -0.75

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0].toInt(), 32767));
        QVERIFY(compare(signal[1].toInt(), 0));
        QVERIFY(compare(signal[2].toInt(), -16384));
        QVERIFY(compare(signal[3].toInt(), -24575));
    }
    // тестируем, что функция возвращает правильный размер сигнала в сэмлах
    void sizeTest()
    {
        QAudioFormat format = createFormat();
        QByteArray bytes;
        for (int i = 0; i < 100; i++)
        {
            bytes.append((char)0);
        }

        Signal signal1(bytes, format);
        format.setSampleSize(8);
        Signal signal2(bytes, format);

        QCOMPARE(signal1.size(), 50);
        QCOMPARE(signal2.size(), 100);
    }
    void resizeTest()
    {
        QAudioFormat format = createFormat();
        QByteArray bytes(100, (char)0);
        Signal signal(bytes, format);

        signal.resize(52);

        QCOMPARE(signal.size(), 52);
        QCOMPARE(signal[51].toInt(), 0);
    }

    // тестируем метод time
    void timeTest()
    {
        QAudioFormat format = createFormat();
        Signal signal(44100, format);

        QCOMPARE(signal.time(44099), 1000);
        QCOMPARE(signal.time(22050), 500);
        QCOMPARE(signal.time(0), 0);
    }

    // тестируем выделение подсигнала
    void subSignalTest()
    {
        QAudioFormat format = createFormat();
        format.setSampleSize(16);
        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0x7F); // = 32767
        bytes.append((char)(0));
        bytes.append((char)(0)); // = 0
        bytes.append((char)(0));
        bytes.append(0xC0); // = -16384
        bytes.append(0x01);
        bytes.append(0xA0); // = -24575

        Signal signal(bytes, format);
        Signal subSignal1 = signal.subSignal(2);
        Signal subSignal2 = signal.subSignal(1, 2);

        QCOMPARE(subSignal1[0].toInt(), -16384);
        QCOMPARE(subSignal2[0].toInt(), 0);
        QCOMPARE(subSignal2[1].toInt(), -16384);
    }

private:
    QAudioFormat createFormat()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleRate(44100);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        return format;
    }

    bool compare(double d1, double d2)
    {
        return (qAbs(d1 - d2) < eps);
    }
    static const double eps = 0.001;
};

/*
void AccessOperatorTest()
{
    double* values = new double[4];
    values[0] = 1.0;
    values[1] = 0.5;
    values[2] = 0.25;
    values[3] = 0.125;
    Signal signal(values, 4);
    QCOMPARE(signal[0].toPcm16(), (short)32767);
    QCOMPARE(signal[1].toPcm16(), (short)16384);
    QCOMPARE(signal[2].toPcm16(), (short)8192);
    QCOMPARE(signal[3].toPcm16(), (short)4096);
}
*/

/*
void EqualityOperatorTest()
{
    Signal signal1(2);
    signal1[0] = 16000;
    signal1[1] = 0;
    Signal signal2(2);
    signal2[0] = 16000;
    signal2[1] = 0;
    QVERIFY(signal1 == signal2);
}
*/
