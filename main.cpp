#include <QtGui/QApplication>
#include <QTimer>
#include <iostream>

#include "testwindow.h"
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow w;
    w.show();

    return a.exec();
}
