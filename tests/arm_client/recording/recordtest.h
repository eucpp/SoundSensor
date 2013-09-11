#ifndef RECORDTEST_H
#define RECORDTEST_H

#include <iostream>
#include <QObject>
#include <QTimer>

#include "recording/soundRecorder.h"
#include "recording/wavFile.h"

class SoundRecorder;

class RecordTest : public QObject
{
    Q_OBJECT
public:
    RecordTest(const QAudioDeviceInfo& device);
    void record(int ms);
private slots:
    void frameHandler(Signal frame);
    void stop(Signal signal);
private:
    SoundRecorder recorder;
    QTimer timer;
    int frameCounter;
};

#endif // RECORDTEST_H
