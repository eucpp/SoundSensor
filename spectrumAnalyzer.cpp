#include "spectrumAnalyzer.h"

SpectrumAnalyzer::SpectrumAnalyzer(int dataSizeExp, QAudioFormat audioFormat):
    format(audioFormat)
{
    analyzedDataSize = static_cast<int>(pow(2, dataSizeExp));
    fourierTransformer = new QFourierTransformer(analyzedDataSize);
}

SpectrumAnalyzer::~SpectrumAnalyzer()
{
    delete fourierTransformer;
}

void SpectrumAnalyzer::calclulateSpectrum(QByteArray byteArray)
{
    // проверяем, совпадает ли размер массива с размером обрабатываемого фрейма
    // сравнение не учитывает формат (подразумевается, что sample size = 8 bit)
    // to do: норм. сравнение, учитывающее формат
    if (byteArray.size() < analyzedDataSize)
    {
        qint64 oldSize = byteArray.size();
        byteArray.resize(analyzedDataSize);
        for (int i = oldSize; i < analyzedDataSize; i++)
            byteArray[i] = 0;
    }

    float* input = new float[analyzedDataSize];
    for (int i = 0; i < analyzedDataSize; i++)
        // фиксированное преобразование (подразумевается, что sample size = 8 bit)
        // to do: норм. преобразование, учитывающее формат
        input[i] = pcmToFloat(static_cast<qint8>(byteArray[i]));
    float* output = new float[analyzedDataSize];
    fourierTransformer->forwardTransform(input, output);

    Spectrogram spectr(analyzedDataSize/2);
    for (int i = 0; i < analyzedDataSize/2; i++)
    {
        spectr[i].frequency = qreal((i * format.frequency()) / analyzedDataSize);
        qreal re = output[i];
        qreal im = 0.0;
        if (i != 0 && i != analyzedDataSize/2)
            im = output[analyzedDataSize/2 + i];
        spectr[i].amplitude = sqrt(re*re + im*im);
    }
    emit spectrumCalculated(spectr);
}
