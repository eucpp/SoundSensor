#include <QtGui/QApplication>
#include <QTimer>

#include "testwindow.h"
#include "soundRecorder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWindow w;
    w.show();

    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    SoundRecorder recorder(device);
    recorder.startRecording();
    
    QTimer::singleShot(1000, &recorder, SLOT(stopRecording()));

    return a.exec();
}
