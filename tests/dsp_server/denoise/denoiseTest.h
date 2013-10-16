#pragma once

#include <QString>
#include <QDebug>

#include "recording/wavFile.h"

#define TEST

#include "trik/iaudenc1_denoise/include/internal/denoise.h"

/*
class DenoiseTest : public QObject
{
    Q_OBJECT
private slots:
    void denoise_test();
};
*/

void denoise_test(const QString& signalWithNoiseFileName, const QString& noiseFileName, const QString& outputFileName);
