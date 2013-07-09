#include "buildParam.h"

#include <QtGui/QApplication>
#include <QTimer>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioDeviceInfo>
#else
    #include <QtMultimedia/QAudioDeviceInfo>
#endif

#include <cstdlib>
#include <iostream>

#include "soundRecorder.h"
#include "voiceCommandSensor.h"
#include "tests/sampleTest.h"
#include "tests/signalTest.h"
#include "tests/wavFileTest.h"
#include "tests/recordtest.h"
#include "tests/signaldetector.h"
#include "tests/correlatorTest.h"
#include "alglibCorrelator.h"
#include "simpleCorrelator.h"

using std::cout;
using std::endl;

void tests()
{
    SampleTest sampleTest;
    QTest::qExec(&sampleTest);
    SignalTest signalTest;
    QTest::qExec(&signalTest);
    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);
    CorrelatorTest correlatorTest;
    QTest::qExec(&correlatorTest);
}

int detectSignal(const QCoreApplication& app, char* argv[])
{
    SignalDetector detector(argv[2]);
    detector.detect(20 * 1000);

    return app.exec();
}

void corr(char* argv[])
{
    WavFile signalFile(argv[2]);
    signalFile.open(WavFile::ReadOnly);
    Signal signal = signalFile.readAll();
    WavFile patternFile(argv[3]);
    patternFile.open(WavFile::ReadOnly);
    Signal pattern = patternFile.readAll();

    if (signal.getFormat() != pattern.getFormat())
    {
        cout << "Format of signal and pattern are not the same!" << endl;
        exit(EXIT_FAILURE);
    }


    alglib::real_1d_array correlation = AlglibCorrelator().correlation(signal, pattern);
    int max = 0;
    for (int i = 1; i < signal.size(); i++)
        if (correlation[max] < correlation[i])
            max = i;

    cout << "Correlation maximum at pos: " << max << "; Time pos in signal: " << signal.time(max)
         << "; Value: " << correlation[max] << endl;

    //delete[] correlation;
    exit(EXIT_SUCCESS);
}

void voiceCommand(char* argv[])
{
    try
    {
        VoiceCommandSensor cmdSensor("../voxforge-ru-0.2/model_parameters/msu_ru_nsh.cd_cont_1000_8gau_16000",
                                     "../voxforge-ru-0.2/etc/msu_ru_nsh.lm.dmp", "../voxforge-ru-0.2/etc/msu_ru_nsh.dic");
        WavFile file(argv[1]);
        Signal signal = file.readAll();
        VoiceCommandSensor::Command cmd = cmdSensor.recognize(signal);

        cout << "Command: " << cmd.command.toStdString() << "; Accuracy: " << cmd.accuracy << endl;
        exit(EXIT_SUCCESS);
    }
    catch (WavFile::OpenFileExc)
    {
        cout << "Error when opening file" << endl;
        exit(EXIT_FAILURE);
    }
    catch (VoiceCommandSensor::PocketSphinxInitExc)
    {
        cout << "Error when initialize pocketsphinx" << endl;
        exit(EXIT_FAILURE);
    }
    catch (VoiceCommandSensor::PocketSphinxRecognizeExc)
    {
        cout << "Recognize error" << endl;
        exit(EXIT_FAILURE);
    }
}

int rec(const QCoreApplication& app)
{
    QAudioDeviceInfo defDev = QAudioDeviceInfo::defaultInputDevice();
    cout << "Default device: " << defDev.deviceName().toStdString() << "; isNull() = " << defDev.isNull() << endl;

    RecordTest recordTest(QAudioDeviceInfo::defaultInputDevice());
    recordTest.record(10 * 1000);

    return app.exec();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString cmd(argv[1]);
    if (cmd == "tests")
        tests();
    else if (cmd == "detect")
        detectSignal(a, argv);
    else if (cmd == "corr")
        corr(argv);
    else if (cmd == "cmd")
        voiceCommand(argv);
    else if (cmd == "rec")
        rec(a);


    //return app.exec();

    return a.exec();
}


/*
CorrelatorTest correlatorTest;
QTest::qExec(&correlatorTest);
*/

/*
QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
QListIterator<QAudioDeviceInfo> itr(devices);
int i = 0;
while (itr.hasNext())
{
    QAudioDeviceInfo device = itr.next();
    cout << "Device #" << i++ << ": " << device.deviceName().toStdString() << "; isNull() = " << device.isNull() << endl;
    RecordTest recordTest(device);
    recordTest.record(3 * 1000);
}
*/
