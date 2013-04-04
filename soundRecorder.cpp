#include "soundRecorder.h"

SoundRecorder::SoundRecorder(QAudioDeviceInfo& device):
    audioDevice(device),
    currentFramePos(0)
{
    defaultFormatSettings();
    audioIn = new QAudioInput(device, audioFormat, this);
    audioIn->setNotifyInterval(SoundRecorder::frameLength);
    byteArray = new QByteArray();
    buffer = new QBuffer(byteArray, this);
}

SoundRecorder::~SoundRecorder()
{
    delete byteArray;
}

// метод возвращает сигнал записанный за всё время работы
// поидее, надо проверять, продолжается ли запись в данный момент,
// и возвращать только доступную область массива байт, если запись идёт.
// пока возвращает полностью все байты (предполагается, что запись остановлена)
Signal SoundRecorder::getSignal()
{
    return Signal(*byteArray, getAudioFormat());
}

QAudioFormat SoundRecorder::getAudioFormat() const
{
    return audioFormat;
}

void SoundRecorder::startRecording()
{
    buffer->open(QIODevice::WriteOnly);
    connect(audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
    audioIn->start(buffer);
}

void SoundRecorder::stopRecording()
{
    audioIn->stop();
}

void SoundRecorder::recordFrame()
{
    qint64 expectedBytesInFrame = SoundRecorder::frameLength
            * audioFormat.frequency() / 1000 * audioFormat.channelCount() * audioFormat.sampleSize() / 8;
    qint64 actualBytesInFrame = buffer->pos() - currentFramePos;
    qint64 bytesInFrame = qMin(expectedBytesInFrame, actualBytesInFrame);

    Signal signal(QByteArray::fromRawData(byteArray->constData() + currentFramePos, bytesInFrame),
                  getAudioFormat());
    currentFramePos += bytesInFrame;
    emit frameRecorded(signal);
}

void SoundRecorder::defaultFormatSettings()
{
    audioFormat.setSampleRate(8000);
    audioFormat.setChannels(1);
    audioFormat.setSampleSize(8);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
}
