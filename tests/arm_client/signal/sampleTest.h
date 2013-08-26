#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "signal/sample.h"

class SampleTest : public QObject
{
    Q_OBJECT
private slots:
    // проверяем создание 8 битного знакового сэмпла из int.
    void AssignmentOperatorTest1()
    {
        QAudioFormat format;
        format.setSampleSize(8);
        format.setSampleType(QAudioFormat::SignedInt);
        Signal signal(4, format);
        signal[1] = 127;
        char* data = signal.data();
        QCOMPARE(data[1], (char)127);
    }
    // проверяем создание 8 битного беззнакового сэмпла из int.
    void AssignmentOperatorTest2()
    {
        QAudioFormat format;
        format.setSampleSize(8);
        format.setSampleType(QAudioFormat::UnSignedInt);
        Signal signal(4, format);
        signal[1] = 250;
        char* data = signal.data();
        QCOMPARE((unsigned char)data[1], (unsigned char)250);
    }
    // проверяем создание 16 битного знакового сэмпла (в big endian) из int.
    void AssignmentOperatorTest3()
    {
        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::BigEndian);
        Signal signal(4, format);
        signal[1] = -32768;
        char* data = signal.data();
        QCOMPARE(data[2], (char)0x80);
        QCOMPARE(data[3], (char)0x00);
    }
    // проверяем создание 16 битного беззнакового сэмпла (в little endian) из int.
    void AssignmentOperatorTest4()
    {
        QAudioFormat format;
        format.setSampleSize(16);
        format.setSampleType(QAudioFormat::UnSignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        Signal signal(4, format);
        signal[1] = 16000;
        char* data = signal.data();
        QCOMPARE(data[2], (char)0x80);
        QCOMPARE(data[3], (char)0x3E);
    }


    /*
    void constructFromPcm8Test()
    {
        char a = 127;
        Sample sample(a);
        QCOMPARE(sample.toPcm8(), a);
        QCOMPARE(sample.getSampleType(), Sample::PCM8);
    }
    void constructFromPcm16Test()
    {
        short a = 32760;
        Sample sample(a);
        QCOMPARE(sample.toPcm16(), (short)32760);
        QCOMPARE(sample.getSampleType(), Sample::PCM16);
    }
    void constructFromUPcm8Test()
    {
        unsigned char ch = 220;
        Sample sample(ch);
        QCOMPARE(sample.toPcm8(), (char)92);
        QCOMPARE(sample.getSampleType(), Sample::PCM8);
    }
    void constructFromUPcm16Test()
    {
        short sh = 16300;
        Sample sample(sh);
        QCOMPARE(sample.toPcm16(), (short)16300);
        QCOMPARE(sample.getSampleType(), Sample::PCM16);
    }
    void constructFromFloatTest()
    {
        float a = 0.5;
        Sample sample(a);
        QCOMPARE(sample.toFloat() , a);
        QCOMPARE(sample.getSampleType(), Sample::Float);
    }
    void AssignmentOperatorTest1()
    {
        Sample s;
        s = char(127);
        QCOMPARE(s.toPcm8(), (char)127);
        QCOMPARE(s.getSampleType(), Sample::PCM8);
    }
    void AssignmentOperatorTest2()
    {
        Sample s((short) 0);
        s = 0.1;
        QCOMPARE(s.toPcm16(), (short)0);
        QCOMPARE(s.getSampleType(), Sample::PCM16);
    }
    void ComparisonOperatorTest1()
    {
        Sample s1((short) 1000);
        Sample s2((short)1000);
        QCOMPARE(s1, s2);
    } 
    void ComparisonOperatorTest2()
    {
        Sample s1 = 0.01;
        Sample s2 = 0.010005;
        QCOMPARE(s1, s2);
    }
    void pcm8ToFloatTest()
    {
        Sample s((char)32);
        QVERIFY(qAbs(s.toFloat() - 0.25) < 0.01);
    }
    void pcm16ToFloatTest()
    {
        Sample s((short)16384);
        QVERIFY(qAbs(s.toFloat() - 0.5) < 0.01);
    }
    void pcm8ToPcm16Test()
    {
        Sample s((short)-16384);
        QCOMPARE(s.toPcm8(), (char)-64);
    }
    void pcm8ToUPcm8Test()
    {
        Sample s((char)-120);
        QCOMPARE(s.toUPcm8(), (unsigned char)8);
    }

    void floatToPcm8Test()
    {
        Sample s((float)-0.5);
        QCOMPARE(s.toPcm8(), (char)-64);
    }
    void floatToPcm16LittleEndTest()
    {
        Sample s((float)-0.5);
        QCOMPARE(s.toPcm16(), (short)-16384);
    }
    void floatToPcm16BigEndTest()
    {
        Sample s((float)-0.5);
        short pcm = s.toPcm16(QAudioFormat::BigEndian);
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0xC0);
        QCOMPARE(bytes[1], (char)0x00);
    }
    void floatToUPcm8Test()
    {
        Sample s((float)-0.5);
        QCOMPARE(s.toUPcm8(), (unsigned char)64);
    }
    void floatToUPcm16LittleEndTest()
    {
        Sample s((float)-0.5);
        QCOMPARE(s.toUPcm16(), (unsigned short)16384);
    }
    void floatToUPcm16BigEndTest()
    {
        Sample s((float)-0.5);
        short pcm = s.toUPcm16(QAudioFormat::BigEndian);
        char* bytes = reinterpret_cast<char*>(&pcm);
        QCOMPARE(bytes[0], (char)0x40);
        QCOMPARE(bytes[1], (char)0x00);
    }
    */

    /*
    void setSampleSizeTest()
    {
        Sample sample1((char) 64);
        sample1.setSampleSize(Sample::PCM16);
        Sample sample2((short) 16384);
        QCOMPARE(sample1.getSampleType(), Sample::PCM16);
        QVERIFY(qAbs(sample1.toDouble() - sample2.toDouble()) < 0.01);
    }
    */
};
