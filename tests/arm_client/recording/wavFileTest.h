#pragma once

#include <iostream>
#include <QObject>
#include <QtTest/QtTest>

#include "recording/wavFile.h"


class WavFileTest : public QObject
{
    Q_OBJECT
private slots:
    void init()
    {
        header = new QAudioFormat();
        header->setCodec("audio/pcm");
        header->setSampleRate(16000);
        header->setSampleSize(16);
        header->setChannels(1);
        header->setSampleType(QAudioFormat::SignedInt);
        file = new WavFile("wavFileTest.wav");
        file->open(WavFile::WriteOnly, *header);
        signal = new Signal(4, *header);
        (*signal)[0] = 32767;
        (*signal)[1] = 16384;
        (*signal)[2] = -256;
        (*signal)[3] = -32768;
    }
    void cleanup()
    {
        file->close();
        delete file;
        delete header;
    }

    // тестируем запись/чтение заголовка wav файла
    void readWriteHeaderTest()
    {
        file->close();
        file->open(WavFile::ReadOnly);
        QAudioFormat readFormat = file->getHeader();
        QCOMPARE(readFormat, *header);
    }
    // тестируем кол-во записанных байт
    void readWriteSignalTest1()
    {
        int samplesWritten = file->write(*signal);
        QCOMPARE(samplesWritten, 4);
    }

    // тестируем запись/чтение сигнала в файл
    void readWriteSignalTest2()
    {
        file->write(*signal);
        file->close();
        file->open(WavFile::ReadOnly);
        Signal readSignal = file->readAll();

        QCOMPARE(readSignal, *signal);
    }
    // тестируем запись чтение части сигнала
    void readWriteSignalTest3()
    {
        file->write(*signal, 3);
        file->close();
        file->open(WavFile::ReadOnly);
        Signal readSignal(file->read(2));
        QCOMPARE(readSignal, signal->subSignal(0, 2));
    }
    void sizeTest()
    {
        file->write(*signal);
        QCOMPARE(file->size(), 4);
    }
    void seekPosTest()
    {
        file->write(*signal);
        file->close();
        file->open(WavFile::ReadOnly);
        file->seek(1);
        QCOMPARE(file->pos(), 1);
        Signal signal(file->read(1));
        QCOMPARE(signal[0].toInt(), 16384);
    }
    // проверяем запись "с наложением" данных.
    void writeTest()
    {
        file->write(*signal);
        file->seek(1);
        file->write(*signal);
        QCOMPARE(file->size(), 5);
    }
    // проверяем добавление в существующий файл.
    void appendTest()
    {
        file->write(*signal);
        file->close();
        file->open(WavFile::Append);
        Signal signal2(2, *header);
        signal2[0] = 0.8;
        signal2[1] = 0.4;
        file->write(signal2);
        QCOMPARE(file->size(), 6);
    }
    // проверяем, сгенерируется ли исключение при попытке открыть некорректный wav файл.
    void UncorrectFileTest()
    {
        try
        {
            QFile badFile("testUncorrectWavFile.txt");
            badFile.open(QIODevice::WriteOnly);
            for (int i = 0; i < 20; i++)
                badFile.write("Lorem ipsum dolar sit amet ");
            badFile.close();
            file->setFileName("testUncorrectWavFile.txt");
            file->open(WavFile::ReadOnly);
            QFAIL("Exception expected");
        }
        catch (WavFile::OpenFileExc)
        {
        }
    }
private:
    WavFile* file;
    QAudioFormat* header;
    Signal* signal;
};
