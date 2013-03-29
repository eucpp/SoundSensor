#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <QMainWindow>
#include <QTimer>
#include "soundRecorder.h"
#include "spectrumAnalyzer.h"

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
    /**
      * Функция печатает спекр последнего фрейма в файл .csv
      * Можно открыть в офисе и посмотреть на диаграмму спектра :)
      */
    void printSpectum(Spectrogram spectr);
private:
    Ui::TestWindow *ui;
    SoundRecorder* recorder;
    SpectrumAnalyzer* analyzer;
};

#endif // TESTWINDOW_H
