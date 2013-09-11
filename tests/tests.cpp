#include "tests.h"
#include "arm_client/recording/recordtest.h"

using namespace std;

void unitTests()
{
    cout << "RUN UNIT TESTS" << endl;

    SampleTest sampleTest;
    QTest::qExec(&sampleTest);

    SignalTest signalTest;
    QTest::qExec(&signalTest);

    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);

    /*
    FourierTransformTest ftTest;
    QTest::qExec(&ftTest);

    CorrelatorTest correlatorTest;
    QTest::qExec(&correlatorTest);

    CorrelatorsTimeTest corrTTest;
    QTest::qExec(&corrTTest);
    */
}

int recordingTest(const QCoreApplication& a)
{
    static const int duration = 10;

    cout << "RUN TEST RECORDING, DEFAULT AUDIO DEVICE, DURATION = " << duration << " SEC" << endl;
    cout << "Record will saved to testRecord.wav" << endl;

    RecordTest r(QAudioDeviceInfo::defaultInputDevice());
    r.record(10 * 1000);

    return a.exec();
}

void devicesInfo()
{
    cout << "AUDIO DEVICES" << endl;

    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QListIterator<QAudioDeviceInfo> itr(devices);
    int i = 0;
    while (itr.hasNext())
    {
        QAudioDeviceInfo device = itr.next();
        cout << "Device #" << i++ << ": " << device.deviceName().toStdString() <<
                "; isNull() = " << device.isNull() << endl;
    }
}
