#include "utils.h"

const qint8 PCM8MaxAmplitude = 128;

float pcmToFloat(qint8 pcm)
{
    return static_cast<float>(pcm / PCM8MaxAmplitude);
}
