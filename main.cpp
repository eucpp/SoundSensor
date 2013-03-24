#include <QtGui/QApplication>
#include <QTimer>

#include "testwindow.h"
#include "soundRecorder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow w;
    w.show();

    SoundRecorder recorder;
    recorder.record();
    
    QTimer::singleShot(9000, &recorder, SLOT(testplay()));
    //recorder.testplay();

    return a.exec();
}
