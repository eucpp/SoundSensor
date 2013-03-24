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
    recorder.startRecording();
    
    QTimer::singleShot(1000, &recorder, SLOT(stopRecording()));

    return a.exec();
}
