#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../sample.h"

class SampleTest : public QObject
{
    Q_OBJECT
private slots:
    void constructFromUPcm8Test()
    {
        unsigned char ch = 220;
        Sample sample(ch);
        QCOMPARE(sample.toPcm8(), (char)92);
    }
    void constructFromUPcm16Test()
    {
        short sh = 16300;
        Sample sample(sh);
        QCOMPARE(sample.toPcm16(), (short)16300);
    }

    void AssignmentOperatorTest()
    {
        Sample s;
        s = char(127);
        QCOMPARE(s.toDouble(), 1.0);
    }
    void ComparisonOperatorTest()
    {
        Sample s;
        s = 0.2;
        QVERIFY(s.toPcm16() == 6553);
    }
    void toDoubleTest()
    {
        Sample s(0.25);
        QVERIFY(qAbs(s.toDouble() - 0.25) < 0.01);
    }
    void toFloatTest()
    {
        Sample s(0.25);
        QVERIFY(qAbs(s.toFloat() - (float)0.25) < 0.01);
    }
    void toPcm8Test()
    {
        Sample s(-0.5);
        QCOMPARE(s.toPcm8(), (char)-64);
    }
    void toPcm16LittleEndTest()
    {
        Sample s(-0.5);
        QCOMPARE(s.toPcm16(), (short)-16384);
    }
    void toPcm16BigEndTest()
    {
        Sample s(-0.5);
        short pcm = s.toPcm16(Sample::BigEndian);
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0xC0);
        QCOMPARE(bytes[1], (char)0x00);
    }
    void toUPcm8Test()
    {
        Sample s(-0.5);
        QCOMPARE(s.toUPcm8(), (unsigned char)64);
    }
    void toUPcm16LittleEndTest()
    {
        Sample s(-0.5);
        QCOMPARE(s.toUPcm16(), (unsigned short)16384);
    }
    void toUPcm16BigEndTest()
    {
        Sample s(-0.5);
        short pcm = s.toUPcm16(Sample::BigEndian);
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0x40);
        QCOMPARE(bytes[1], (char)0x00);
    }
    void getSampleSizeTest()
    {
        Sample sample((short)100);
        QCOMPARE(sample.getSampleSize(), Sample::PCM8);
    }
    void setSampleSizeTest()
    {
        Sample sample((char) 64);
        sample.setSampleSize(Sample::PCM16);
        QCOMPARE(sample.getSampleSize(), Sample::PCM16);
        QCOMPARE(sample.toPcm16(), (short)16384);
    }
};
