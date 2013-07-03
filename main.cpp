#include "buildParam.h"

#include <QtGui/QApplication>
#include <QTimer>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioDeviceInfo>
#else
    #include <QtMultimedia/QAudioDeviceInfo>
#endif

#include <iostream>

#include "soundRecorder.h"
#include "tests/sampleTest.h"
#include "tests/signalTest.h"
#include "tests/wavFileTest.h"
#include "tests/recordtest.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SampleTest sampleTest;
    QTest::qExec(&sampleTest);
    SignalTest signalTest;
    QTest::qExec(&signalTest);
    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);

    cout << "Default device: " << QAudioDeviceInfo::defaultInputDevice().deviceName().toStdString() << endl;
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    QListIterator<QAudioDeviceInfo> itr(devices);
    int i = 0;
    while (itr.hasNext())
    {
        QAudioDeviceInfo device = itr.next();
        cout << "Device #" << i++ << ": " << device.deviceName().toStdString() << "; isNull() = " << device.isNull() << endl;
    }
    cout << endl;


    RecordTest recordTest;
    recordTest.record(10 * 1000);

    return a.exec();
}
