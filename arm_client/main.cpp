

#include <QtGui/QApplication>
#include <QTimer>

#ifdef DESKTOP
    #include <QtMultimediaKit/QAudioDeviceInfo>
#else
    #include <QtMultimedia/QAudioDeviceInfo>
#endif

#include <cstdlib>
#include <cstring>
#include <iostream>

//#include "fixed_point/fixed_func.h"
#include "recording/soundRecorder.h"
#include "recording/wavFile.h"
//#include "voiceCommandSensor.h"
//#include "tests/sampleTest.h"
//#include "tests/signalTest.h"
//#include "tests/wavFileTest.h"
//#include "tests/recordtest.h"
//#include "tests/signaldetector.h"
//#include "tests/correlatorTest.h"
//#include "tests/correlatorsTimeTest.h"
//#include "tests/fourierTransformTest.h"
//#include "signal/correlation/alglibCorrelator.h"
//#include "signal/correlation/simpleCorrelator.h"
//#include "motorFilterTest.h"

#include "tests.h"

using std::cout;
using std::endl;

void tests()
{
    /*
    SampleTest sampleTest;
    QTest::qExec(&sampleTest);

    SignalTest signalTest;
    QTest::qExec(&signalTest);

    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);


    FourierTransformTest ftTest;
    QTest::qExec(&ftTest);

    CorrelatorTest correlatorTest;
    QTest::qExec(&correlatorTest);

    CorrelatorsTimeTest corrTTest;
    QTest::qExec(&corrTTest);
    */
}

/*
int detectSignal(const QCoreApplication& app, char* argv[])
{
    SignalDetector detector(argv[2]);
    detector.detect(20 * 1000);

    return app.exec();
}
*/

/*
void corr(char* argv[])
{
    WavFile signalFile(argv[2]);
    signalFile.open(WavFile::ReadOnly);
    Signal signal = signalFile.readAll();
    WavFile patternFile(argv[3]);
    patternFile.open(WavFile::ReadOnly);
    Signal pattern = patternFile.readAll();

    std::cout << signal.size() << std::endl;

    if (signal.getFormat() != pattern.getFormat())
    {
        cout << "Format of signal and pattern are not the same!" << endl;
        exit(EXIT_FAILURE);
    }

    QScopedArrayPointer<RealNum> corr(new RealNum[signal.size() + pattern.size() - 1]);
    FFTCorrelator().correlation(signal, pattern, corr.data());
    int max = 0;
    for (int i = 1; i < signal.size() + pattern.size() - 1; i++)
        if (corr[max] < corr[i])
            max = i;

    cout << "Correlation maximum at pos: " << max << "; Time pos in signal: " << signal.time(max)
         << "; Value: " << realNumToFloat(corr[max]) << endl;

    //delete[] correlation;
    exit(EXIT_SUCCESS);
}
*/

void voiceCommand(char* argv[])
{
    /*
    try
    {

        VoiceCommandSensor cmdSensor("sphinx_data/msu_ru_nsh.cd_cont_1000_8gau_16000_adapt/",
                                     "sphinx_data/robot.gram", "sphinx_data/adapt.dic");

        WavFile file(argv[2]);
        file.open(WavFile::ReadOnly);
        Signal signal = file.readAll();

        std::cout << "/--------------------------------------------------------------------------------------/" << std::endl;
        std::cout << "START RECOGNITION" << std::endl;

        clock_t time1 = clock();
        VoiceCommandSensor::Command cmd = cmdSensor.recognize(signal);
        clock_t time2 = clock();
        std::cout << "Recognition time: " << (time2 - time1) / (CLOCKS_PER_SEC / 1000) << std::endl;

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
    */
}

int rec(const QCoreApplication& app)
{
    /*
    QAudioDeviceInfo defDev = QAudioDeviceInfo::defaultInputDevice();
    cout << "Default device: " << defDev.deviceName().toStdString() << "; isNull() = " << defDev.isNull() << endl;

    RecordTest recordTest(QAudioDeviceInfo::defaultInputDevice());
    recordTest.record(10 * 1000);
    */

    return app.exec();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	dspTest();

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
