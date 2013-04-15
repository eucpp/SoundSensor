#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow),
    signal(NULL, 0),
    pattern(NULL, 0)
{
    ui->setupUi(this);

    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    recorder = new SoundRecorder(device);
    analyzer = new SpectrumAnalyzer(10, recorder->getAudioFormat());
    correlator = new Correlator();

    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startRecording()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopRecording()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveRecord()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(openPattern()));
    connect(ui->compareButton, SIGNAL(clicked()), this, SLOT(compareSignals()));

    ui->stopButton->setEnabled(false);
}

TestWindow::~TestWindow()
{
    delete ui;

    delete recorder;
    delete analyzer;
    delete correlator;
}

void TestWindow::startRecording()
{
    recorder->startRecording();
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}
void TestWindow::stopRecording()
{
    recorder->stopRecording();
    signal = recorder->getSignal();
    ui->stopButton->setEnabled(false);
    ui->recordLabel->setText("Sound was recorded successfully");
}
void TestWindow::openPattern()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open pattern wav file", "/home", "(*.wav)");
    WavFile file(filename);
    file.open(QIODevice::ReadOnly);
    pattern = file.readSignal();
    ui->loadLabel->setText("Pattern loaded successfully");
}
void TestWindow::saveRecord()
{
    WavFile file("record.wav");
    file.open(QIODevice::WriteOnly);
    file.writeSignal(signal);

    ui->saveLabel->setText("Record was saved to record.wav");
}
void TestWindow::compareSignals()
{
    Signal correlation = correlator->calcCorrelation(signal, pattern);
    correlation.setFormat(signal.getFormat());
    double max = 0;
    unsigned int maxInd = 0;
    for (int i = 0; i < correlation.size(); i++)
    {
        if (correlation[i] > max)
        {
            max = correlation[i];
            maxInd = i;
        }
    }
    QByteArray match = signal.getBytes().mid(maxInd, pattern.size());
    Signal matchSignal(match, signal.getFormat());

    WavFile file("matchingFragment.wav");
    file.open(QIODevice::WriteOnly);
    file.writeSignal(matchSignal);

    QString text;
    text = "Best match at ";
    text += QString().setNum(maxInd / correlation.getFormat().sampleRate());
    text += " second.";
    text += '\n';
    text += "Matching fragment was saved to matchingFragment.wav";
    ui->compareLabel->setText(text);
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
