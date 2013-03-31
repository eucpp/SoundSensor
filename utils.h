#pragma once

#include <QObject>

float pcmToFloat(int pcm);
double pcmToDouble(int pcm);

double* byteArrayToDouble(QByteArray byteArray);
