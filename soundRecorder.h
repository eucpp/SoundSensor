#pragma once

#include <iostream>
#include <QObject>
#include <QtMultimediaKit/QAudioInput>
#include <QtMultimediaKit/QAudioFormat>
#include <QAudioOutput>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>

using namespace std;

class SoundRecorder : public QObject
{
    Q_OBJECT
public:
    SoundRecorder();
    ~SoundRecorder();
    void record();
public slots:
    void stop();
    void testplay();
private slots:
    void testBytesWritten(qint64 size);
    void testDataReady();
private:
    void defaultFormatSettings();
    QAudioInput* audioIn;
    QAudioFormat* audioFormat;
    QByteArray* byteArray;
    QBuffer* buffer;
};

