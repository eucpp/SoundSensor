#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../signal.h"
#include "../soundRecorder.h"

class SignalTest : public QObject
{
    Q_OBJECT
private slots:
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

private:
    bool compare(double d1, double d2)
    {
        return (qAbs(d1 - d2) < eps);
    }
    static const double eps = 0.01;
};
