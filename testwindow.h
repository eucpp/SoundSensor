#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include "voiceCommandSensor.h"
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"
#include "correlator.h"
#include "wavFile.h"

using namespace std;

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();
public slots:
    void startRecording();
    void stopRecording();
    void openPattern();
    void saveRecord();
    void openRecordFile();
    void compareSignals();
    void recognizeCommand();
    /**
      * Функция печатает спекр последнего фрейма в файл .csv
      * Можно открыть в офисе и посмотреть на диаграмму спектра :)
      */
    void printSpectum(Spectrogram spectr);
private:
    Ui::TestWindow *ui;
    SoundRecorder* recorder;
    SpectrumAnalyzer* analyzer;
    Correlator* correlator;
    VoiceCommandSensor* commandSensor;

    Signal signal;
    Signal pattern;
};

#endif // TESTWINDOW_H
