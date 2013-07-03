#include <QtGui/QApplication>
#include <QTimer>
#include <iostream>

#include "testwindow.h"
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"
#include "tests/sampleTest.h"
#include "tests/signalTest.h"
#include "tests/wavFileTest.h"
#include "tests/recordtest.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SampleTest sampleTest;
    QTest::qExec(&sampleTest);
    SignalTest signalTest;
    QTest::qExec(&signalTest);
    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);

    RecordTest recordTest;
    recordTest.record(10 * 1000);

    return a.exec();
}
