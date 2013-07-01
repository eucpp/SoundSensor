#include <QtGui/QApplication>
#include <QTimer>
#include <iostream>

#include "testwindow.h"
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"
#include "tests/sampleTest.h"
#include "tests/signalTest.h"
#include "tests/wavFileTest.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow w;
    w.show();

    SampleTest sampleTest;
    QTest::qExec(&sampleTest);
    SignalTest signalTest;
    QTest::qExec(&signalTest);

    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);


    //printStatistics();

    return a.exec();
}
