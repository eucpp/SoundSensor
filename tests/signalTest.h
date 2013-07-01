#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../signal.h"
#include "../soundRecorder.h"

class SignalTest : public QObject
{
    Q_OBJECT
private slots:
    void AccessOperatorTest()
    {
        double* values = new double[4];
        values[0] = 1.0;
        values[1] = 0.5;
        values[2] = 0.25;
        values[3] = 0.125;
        Signal signal(values, 4);
        QCOMPARE(signal[0].toDouble(), 1.0);
        QCOMPARE(signal[1].toDouble(), 0.5);
        QCOMPARE(signal[2].toDouble(), 0.25);
        QCOMPARE(signal[3].toDouble(), 0.125);
    }
    // тестирование создания объекта-сигнала из QByteArray
    void ConstructFromQByteArrayTest()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

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

        QVERIFY(compare(signal[0].toDouble(), 1.0));
        QVERIFY(compare(signal[1].toDouble(), 0));
        QVERIFY(compare(signal[2].toDouble(), -0.5));
        QVERIFY(compare(signal[3].toDouble(), -0.75));
    }
    void toByteArrayTest1()
    {
        Signal signal(4);
        signal[0] = 1.0;
        signal[1] = 0.5;
        signal[2] = 0.0;
        signal[3] = -0.2;

        QAudioFormat format;
        format.setSampleSize(8);
        QByteArray bytes = signal.toByteArray(format);
        QCOMPARE((char)bytes[0], (char)127);
        QCOMPARE((char)bytes[1], (char)64);
        QCOMPARE((char)bytes[2], (char)0);
        QCOMPARE((char)bytes[3], (char)-25);
    }
    void toByteArrayTest2()
    {
        Signal signal(4);
        signal[0] = 1.0;
        signal[1] = 0.5;
        signal[2] = 0.0;
        signal[3] = -0.2;

        QAudioFormat format;
        format.setSampleSize(16);
        format.setByteOrder(QAudioFormat::BigEndian);
        QByteArray bytes = signal.toByteArray(format);
        QCOMPARE((char)bytes[0], (char)0x7F);
        QCOMPARE((char)bytes[1], (char)0xFF);
        QCOMPARE((char)bytes[2], (char)0x40);
        QCOMPARE((char)bytes[3], (char)0x00);
        QCOMPARE((char)bytes[4], (char)0x00);
        QCOMPARE((char)bytes[5], (char)0x00);
        QCOMPARE((char)bytes[6], (char)0xE6);
        QCOMPARE((char)bytes[7], (char)0x67);
    }

    /*
    void pcmToDoubleTest()
    {
        QVERIFY(compare(Signal::pcmToDouble(255, 8), 1.0));
        QVERIFY(compare(Signal::pcmToDouble(128, 8), 0.5));
        QVERIFY(compare(Signal::pcmToDouble(64, 8), 0.25));
        QVERIFY(compare(Signal::pcmToDouble(32, 8), 0.125));

        QVERIFY(compare(Signal::pcmToDouble(65535, 16), 1.0));
        QVERIFY(compare(Signal::pcmToDouble(32767, 16), 0.5));
        QVERIFY(compare(Signal::pcmToDouble(16384, 16), 0.25));
        QVERIFY(compare(Signal::pcmToDouble(8192, 16), 0.125));
    }
    void doubleToPcmTest()
    {
        QCOMPARE(Signal::doubleToPcm(1.0, 8), 255);
        QCOMPARE(Signal::doubleToPcm(0.5, 8), 128);
        QCOMPARE(Signal::doubleToPcm(0.25, 8), 64);
        QCOMPARE(Signal::doubleToPcm(0.125, 8), 32);

        QCOMPARE(Signal::doubleToPcm(1.0, 16), 65535);
        QCOMPARE(Signal::doubleToPcm(0.5, 16), 32768);
        QCOMPARE(Signal::doubleToPcm(0.25, 16), 16384);
        QCOMPARE(Signal::doubleToPcm(0.125, 16), 8192);
    }

    void accessOperatorTest1()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(8);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

        QByteArray bytes;
        bytes.append(127); // ~ 1.0
        bytes.append(static_cast<char>(0)); // ~ 0.5
        bytes.append(-64); // ~ 0.25
        bytes.append(-96); // ~ 0.125

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0], 1.0));
        QVERIFY(compare(signal[1], 0.5));
        QVERIFY(compare(signal[2], 0.25));
        QVERIFY(compare(signal[3], 0.125));
    }
    void accessOperatorTest2()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0x7F); // = 32767 ~ 1.0
        bytes.append(static_cast<char>(0));
        bytes.append(static_cast<char>(0)); // = 0 ~ 0.5
        bytes.append(static_cast<char>(0));
        bytes.append(0xC0); // = -16384 ~ 0.25
        bytes.append(0x01);
        bytes.append(0xA0); // = -24575 ~ 0.125

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0], 1.0));
        QVERIFY(compare(signal[1], 0.5));
        QVERIFY(compare(signal[2], 0.25));
        QVERIFY(compare(signal[3], 0.125));
    }
    void accessOperatorTest3()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(8);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

        QByteArray bytes;
        bytes.append(255); // ~ 1.0
        bytes.append(128); // ~ 0.5
        bytes.append(64); // ~ 0.25
        bytes.append(32); // ~ 0.125

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0], 1.0));
        QVERIFY(compare(signal[1], 0.5));
        QVERIFY(compare(signal[2], 0.25));
        QVERIFY(compare(signal[3], 0.125));
    }
    void accessOperatorTest4()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);

        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0xFF); // = 65535 ~ 1.0
        bytes.append(0xFF);
        bytes.append(0x7F); // = 32767 ~ 0.5
        bytes.append(static_cast<char>(0));
        bytes.append(0x40); // = 16384 ~ 0.25
        bytes.append(static_cast<char>(0));
        bytes.append(0x20); // = 8192 ~ 0.125

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0], 1.0));
        QVERIFY(compare(signal[1], 0.5));
        QVERIFY(compare(signal[2], 0.25));
        QVERIFY(compare(signal[3], 0.125));
    }
    void accessOperatorTest5()
    {
        QAudioFormat format;
        format.setChannels(1);
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);

        QByteArray bytes;
        bytes.append(0xFF);
        bytes.append(0xFF); // = 65535 ~ 1.0
        bytes.append(0x7F);
        bytes.append(0xFF); // = 32767 ~ 0.5
        bytes.append(0x40);
        bytes.append(static_cast<char>(0)); // = 16384 ~ 0.25
        bytes.append(0x20);
        bytes.append(static_cast<char>(0)); // = 8192 ~ 0.125

        Signal signal(bytes, format);

        QVERIFY(compare(signal[0], 1.0));
        QVERIFY(compare(signal[1], 0.5));
        QVERIFY(compare(signal[2], 0.25));
        QVERIFY(compare(signal[3], 0.125));
    }

    // проверка приведения массива double в массив 8-битных pcm
    void getBytesTest1()
    {
        double* values = new double[4];
        values[0] = 1.0;
        values[1] = 0.5;
        values[2] = 0.25;
        values[3] = 0.125;

        Signal signal(values, 4);
        QAudioFormat format;
        format.setSampleSize(8);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        signal.setFormat(format);
        QByteArray bytes = signal.getBytes();

        QCOMPARE((char)bytes[0], (char)255);
        QCOMPARE((char)bytes[1], (char)128);
        QCOMPARE((char)bytes[2], (char)64);
        QCOMPARE((char)bytes[3], (char)32);
    }
    // проверка приведения массива double в массив 16-битных pcm (беззнаковых)
    // с big-endian порядком байт
    void getBytesTest2()
    {
        double* values = new double[4];
        values[0] = 1.0;
        values[1] = 0.5;
        values[2] = 0.25;
        values[3] = 0.125;

        Signal signal(values, 4);
        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);
        signal.setFormat(format);
        QByteArray bytes = signal.getBytes();

        QCOMPARE((char)bytes[0], (char)0x7F);
        QCOMPARE((char)bytes[1], (char)0xFF);
        QCOMPARE((char)bytes[2], (char)0x00);
        QCOMPARE((char)bytes[3], (char)0x00);
        QCOMPARE((char)bytes[4], (char)0xC0);
        QCOMPARE((char)bytes[5], (char)0x00);
        QCOMPARE((char)bytes[6], (char)0xA0);
        QCOMPARE((char)bytes[7], (char)0x00);
    }
    // проверка приведения массива байт в массив double
    void getDataTest()
    {
        QByteArray bytes;
        bytes.append(0x7F);
        bytes.append(0xFF); // 32767
        bytes.append((char)0x00);
        bytes.append((char)0x00); // 0
        bytes.append(0xC0);
        bytes.append((char)0x00); // -16384
        bytes.append(0xA0);
        bytes.append((char)0x00); // -24575

        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);

        Signal signal(bytes, format);

        double* values = signal.getData();

        QVERIFY(compare(values[0], 1.0));
        QVERIFY(compare(values[1], 0.5));
        QVERIFY(compare(values[2], 0.25));
        QVERIFY(compare(values[3], 0.125));
    }

    void setFormatTest()
    {
        QByteArray bytes;
        bytes.append(0x7F);
        bytes.append(0xFF); // 32767
        bytes.append((char)0x00);
        bytes.append((char)0x00); // 0
        bytes.append(0xC0);
        bytes.append((char)0x00); // -16384
        bytes.append(0xA0);
        bytes.append((char)0x00); // -24575

        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);

        Signal signal(bytes, format);

        QAudioFormat newFormat;
        newFormat.setSampleSize(8);
        newFormat.setSampleType(QAudioFormat::UnSignedInt);
        newFormat.setByteOrder(QAudioFormat::LittleEndian);

        signal.setFormat(newFormat);
        QByteArray newBytes = signal.getBytes();

        QCOMPARE((char)newBytes[0], (char)255);
        QCOMPARE((char)newBytes[1], (char)128);
        QCOMPARE((char)newBytes[2], (char)64);
        QCOMPARE((char)newBytes[3], (char)32);
    }

    void sizeTest1()
    {
        double* values = new double[4];
        values[0] = 1.0;
        values[1] = 0.5;
        values[2] = 0.25;
        values[3] = 0.125;

        Signal signal(values, 4);

        QCOMPARE(signal.size(), (unsigned int)4);
    }
    void sizeTest2()
    {
        QByteArray bytes;
        bytes.append(0x7F);
        bytes.append(0xFF); // 32767
        bytes.append((char)0x00);
        bytes.append((char)0x00); // 0
        bytes.append(0xC0);
        bytes.append((char)0x00); // -16384
        bytes.append(0xA0);
        bytes.append((char)0x00); // -24575

        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);

        Signal signal(bytes, format);

        QCOMPARE(signal.size(), (unsigned int)4);
    }
    */

private:
    bool compare(double d1, double d2)
    {
        return (qAbs(d1 - d2) < eps);
    }
    static const double eps = 0.001;
};
