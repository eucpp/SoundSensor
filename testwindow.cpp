#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow)
{
    ui->setupUi(this);

    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    recorder = new SoundRecorder(device);
    analyzer = new SpectrumAnalyzer(10, recorder->getAudioFormat());
    correlator = new Correlator();
    connect(recorder, SIGNAL(frameRecorded(QByteArray)), analyzer, SLOT(calclulateSpectrum(QByteArray)));
    connect(analyzer, SIGNAL(spectrumCalculated(Spectrogram)), this, SLOT(printSpectum(Spectrogram)));


    recorder->startRecording();
    QTimer::singleShot(1000, recorder, SLOT(stopRecording()));
}

TestWindow::~TestWindow()
{
    delete ui;

    delete recorder;
    delete analyzer;
    delete correlator;
}
void TestWindow::printSpectum(Spectrogram spectr)
{
    ofstream file;
    file.open("test.csv");
    for (int i = 0; i < spectr.size(); i++)
    {
        file << spectr[i].frequency << ", ";
        file << spectr[i].amplitude << endl;
    }
    file.close();
}
