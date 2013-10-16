#include "denoiseTest.h"

#include <math.h>
#include <limits.h>

void denoise_test(const QString& signalWithNoiseFileName, const QString& noiseFileName, const QString& outputFileName)
{
    WavFile signalFile(signalWithNoiseFileName);
    signalFile.open(WavFile::ReadOnly);
    WavFile noiseFile(noiseFileName);
    noiseFile.open(WavFile::ReadOnly);

    if (signalFile.getHeader() != noiseFile.getHeader())
    {
        qDebug() << "Signal and noise files have the different headers!";
        return;
    }

    WavFile outputFile(outputFileName);
    outputFile.open(WavFile::WriteOnly, signalFile.getHeader());

    const int frameSize = 1024;
    int minSize = qMin(signalFile.size(), noiseFile.size());
    int frameNum = minSize / frameSize;

    float adaptation_rate = pow(10, -2);
    float error = pow(10, -3);

    float* signal_with_noise = new float[frameSize];
    float* noise = new float[frameSize];
    float* signal = new float[frameSize];
    float* filter = new float[frameSize];
    memset(signal, 0, frameSize * sizeof(float));
    memset(filter, 0, frameSize * sizeof(float));

    for (int i = 0; i < frameNum; i++)
    {
        qDebug() << "Frame #" << i;

        Signal signalFrame = signalFile.read(frameSize);
        Signal noiseFrame = noiseFile.read(frameSize);

        for (int j = 0; j < frameSize; j++)
        {
            signal_with_noise[j] = static_cast<float>(signalFrame[j].toInt()) * pow(2, -15);
            noise[j] = static_cast<float>(noiseFrame[j].toInt()) * pow(2, -15);
        }
        float final_err = denoise(signal_with_noise, noise, filter, signal, frameSize, error, adaptation_rate);

        qDebug() << "Adapt error: " << final_err;

        Signal outputFrame(frameSize, signalFile.getHeader());
        for (int j = 0; j < frameSize; j++)
        {
            try
            {
                outputFrame[j] = static_cast<int>(signal[j] * pow(2, 15));
            }
            catch (Sample::OutOfRangeValue exc)
            {
                int tmp = static_cast<int>(signal[j] * pow(2, 15));
                if (tmp > 0)
                {
                    outputFrame[j] = 32767;
                }
                else
                {
                    outputFrame[j] = -32768;
                }
            }
        }
        outputFile.write(outputFrame);
    }

    delete[] signal_with_noise;
    delete[] noise;
    delete[] signal;
    delete[] filter;
}
