#ifndef SIGNALDETECTOR_H
#define SIGNALDETECTOR_H

#include <iostream>
#include <QTimer>
#include "../recording/wavFile.h"
#include "../signal/correlation/correlator.h"
#include "../recording/soundRecorder.h"
#include "../signal/correlation/simpleCorrelator.h"
#include "../signal/correlation/alglibCorrelator.h"

class SignalDetector : public QObject
{
    Q_OBJECT
public:
    SignalDetector(const QString& filename);
    ~SignalDetector();
    void detect(int ms);

private slots:
    void handleFrame(Signal frame);
    void stopDetection();
private:
    Signal pattern;
    SoundRecorder recorder;
    QTimer timer;
    AlglibCorrelator* correlator;

    static const double coeff = 12.0;
};

#endif // SIGNALDETECTOR_H
