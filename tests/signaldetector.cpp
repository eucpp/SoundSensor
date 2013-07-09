#include "signaldetector.h"

SignalDetector::SignalDetector(const QString& filename):
    recorder()
{
    WavFile file(filename);
    file.open(WavFile::ReadOnly);
    pattern = file.readAll();
    int duration = pattern.time(pattern.size());
    recorder.setFrameLength(duration*2);
    //recorder.setFormat(file.getHeader());

    correlator = new AlglibCorrelator();

    connect(&recorder, SIGNAL(frameRecorded(Signal)), this, SLOT(handleFrame(Signal)));
    connect(&recorder, SIGNAL(recordingStopped(Signal)), this, SLOT(stopDetection()));
}

SignalDetector::~SignalDetector()
{
    delete correlator;
}

void SignalDetector::detect(int ms)
{
    recorder.start();
    timer.singleShot(ms, &recorder, SLOT(stop()));
}

void SignalDetector::handleFrame(Signal frame)
{
    alglib::real_1d_array correlation = correlator->correlation(frame, pattern);
    int max = 0;
    for (int i = 1; i < frame.size(); i++)
        if (correlation[max] < correlation[i])
            max = i;

    if (correlation[max] > coeff)
        std::cout << "1" << std::flush;
    else
        std::cout << "0" << std::flush;
}

void SignalDetector::stopDetection()
{
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}
