#include <QtGui/QApplication>
#include <QTimer>
#include <iostream>

#include "testwindow.h"
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"
#include "tests/signalTest.h"
#include "tests/wavFileTest.h"

#include "tmp.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow w;
    w.show();

    SignalTest signalTest;
    QTest::qExec(&signalTest);
    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);

    //printStatistics();

    return a.exec();
}
