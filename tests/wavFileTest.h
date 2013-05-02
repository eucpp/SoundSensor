#pragma once

#include <QObject>
#include <QtTest/QtTest>
#include "../wavFile.h"
#include "../soundRecorder.h"

class WavFileTest : public QObject
{
    Q_OBJECT
private slots:
    void init()
    {
        file = new WavFile(QString("test.wav"));
        file->open(WavFile::WriteOnly);
    }
    void cleanup()
    {
        if (file->isOpen())
            file->close();
        delete file;
    }
    void seekTest()
    {
        QVERIFY(file->seek(10));
    }
    void posTest()
    {
        QCOMPARE(file->pos(), (unsigned int)0);
        file->seek(10);
        QCOMPARE(file->pos(), (unsigned int)10);
    }
    void dataSizeTest()
    {
        file->close();
        file->open(WavFile::ReadOnly);
        QCOMPARE(file->dataSize(), (unsigned int)0);
    }
    void writeSignalTest()
    {
        QByteArray bytes;
        bytes[0] = 127;
        bytes[1] = 64;
        bytes[2] = 0;
        bytes[3] = -64;
        Signal signal(bytes, SoundRecorder::defaultAudioFormat());
        file->writeSignal(signal);
        file->close();
        file->open(WavFile::ReadOnly);
        QCOMPARE(file->dataSize(), (unsigned int)4);
    }
    void readSignalTest()
    {
        QByteArray bytes;
        bytes[0] = 127;
        bytes[1] = 64;
        bytes[2] = 0;
        bytes[3] = -64;
        Signal signal(bytes, SoundRecorder::defaultAudioFormat());
        file->writeSignal(signal);
        file->close();

        file->open(WavFile::ReadOnly);
        Signal readSignal = file->readSignal();
        QByteArray readBytes = readSignal.getBytes();
        QCOMPARE(char(readBytes[0]), char(127));
        QCOMPARE(char(readBytes[1]), char(64));
        QCOMPARE(char(readBytes[2]), char(0));
        QCOMPARE(char(readBytes[3]), char(-64));
    }

private:
    WavFile* file;
};
