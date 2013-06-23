#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow),
    signal(NULL, 0),
    pattern(NULL, 0)
{
    ui->setupUi(this);

    QAudioFormat f = SoundRecorder::defaultAudioFormat();
    f.setSampleSize(16);
    f.setSampleRate(16000);
    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    recorder = new SoundRecorder(device, f);
    analyzer = new SpectrumAnalyzer(10, recorder->getAudioFormat());
    correlator = new Correlator();

    commandSensor = new VoiceCommandSensor(
                "/home/evgeniy/projects/SoundSensor/trained_model/hub4wsj_sc_8kadapt",
                "./voiceCommands.lm",
                "./voiceCommands.dic");


    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startRecording()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopRecording()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveRecord()));
    connect(ui->openFileButton, SIGNAL(clicked()), this, SLOT(openRecordFile()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(openPattern()));
    connect(ui->compareButton, SIGNAL(clicked()), this, SLOT(compareSignals()));
    connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(recognizeCommand()));

    ui->stopButton->setEnabled(false);
}

TestWindow::~TestWindow()
{
    delete ui;

    delete recorder;
    delete analyzer;
    delete correlator;
    delete commandSensor;
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
    ui->startButton->setEnabled(true);
}
void TestWindow::openPattern()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open pattern wav file", "/home", "(*.wav)");
    WavFile file(filename);
    file.open(WavFile::ReadOnly);
    pattern = file.readSignal();
    ui->loadLabel->setText("Pattern was loaded successfully");
}
void TestWindow::saveRecord()
{
    WavFile file("record.wav");
    file.open(WavFile::WriteOnly, signal.getFormat());
    file.writeSignal(signal);

    ui->saveLabel->setText("Record was saved to record.wav");
}
void TestWindow::openRecordFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open wav file with record",
                                                    "/home/evgeniy/projects/SoundSensor/voice_commands_tests",
                                                    "(*.wav)");
    WavFile file(filename);
    file.open(WavFile::ReadOnly);
    signal = file.readSignal();
    ui->openFileLabel->setText("Record was opened successfully");
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
    file.open(WavFile::WriteOnly);
    file.writeSignal(matchSignal);

    QString text;
    text = "Best match at ";
    text += QString().setNum(maxInd / correlation.getFormat().sampleRate());
    text += " second.";
    text += '\n';
    text += "Matching fragment was saved to matchingFragment.wav";
    ui->compareLabel->setText(text);
}

void TestWindow::recognizeCommand()
{
    VoiceCommandSensor::Command cmd = commandSensor->recognizeCommand(signal);
    QString text;
    text += "Command: ";
    text += cmd.command + '\n';
    text += "Accuracy: ";
    text += QString().setNum(cmd.accuracy) + '\n';
    text += "Uttid: ";
    text += cmd.uttid + '\n';
    ui->commandLabel->setText(text);
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
