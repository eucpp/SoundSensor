#include "recordtest.h"

RecordTest::RecordTest():
    frameCounter(0)
{
    //connect(&timer, SIGNAL(timeout()), &recorder, SLOT(stop()));
    connect(&recorder, SIGNAL(frameRecorded(Signal)), this, SLOT(frameHandler(Signal)));
    connect(&recorder, SIGNAL(recordingStopped(Signal)), this, SLOT(stop(Signal)));
}

void RecordTest::record(int ms)
{
    recorder.start();
    timer.singleShot(ms, &recorder, SLOT(stop()));
    std::cout << "Recording started. Time = " << ms << "ms. Frame length = " << recorder.getFrameLength() << "ms" << std::endl;
}

void RecordTest::frameHandler(Signal frame)
{
    std::cout << "Frame #" << frameCounter++ << "; Samples num = " << frame.size() << std::endl;
}

void RecordTest::stop(Signal signal)
{
    try
    {
        std::cout << "Recording stopped." << std::endl;
        WavFile file("testRecord.wav");
        file.open(WavFile::WriteOnly, signal.getFormat());
        int n = file.write(signal);
        file.close();
        std::cout << "Record was saved to testRecord.wav. Saved " << n << " samples." << std::endl;
    }
    catch (...)
    {
        std::cout << "Some exception!" << endl;
    }
}
