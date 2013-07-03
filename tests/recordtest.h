#ifndef RECORDTEST_H
#define RECORDTEST_H

#include <iostream>
#include <QObject>
#include <QTimer>
#include "../soundRecorder.h"
#include "../wavFile.h"

class RecordTest : public QObject
{
    Q_OBJECT
public:
    RecordTest();
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
