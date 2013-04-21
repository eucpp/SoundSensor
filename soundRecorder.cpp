#include "soundRecorder.h"

SoundRecorder::SoundRecorder()
{
    init(QAudioDeviceInfo::defaultInputDevice(), SoundRecorder::defaultAudioFormat());
}
SoundRecorder::SoundRecorder(QAudioDeviceInfo device)
{
    init(device, SoundRecorder::defaultAudioFormat());
}
SoundRecorder::SoundRecorder(QAudioFormat format)
{
    init(QAudioDeviceInfo::defaultInputDevice(), format);
}
SoundRecorder::SoundRecorder(QAudioDeviceInfo device, QAudioFormat format)
{
    init(device, format);
}

SoundRecorder::~SoundRecorder()
{
    delete byteArray;
}

Signal SoundRecorder::getSignal()
{
    if (audioIn->state() == QAudio::ActiveState)
        return Signal(QByteArray::fromRawData(byteArray->constData(), buffer->pos()), getAudioFormat());
    return Signal(*byteArray, getAudioFormat());
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
    emit recordingStopped(getSignal());
}

void SoundRecorder::recordFrame()
{
    qint64 bytesInFrame = buffer->pos() - currentFramePos;
    Signal signal(QByteArray::fromRawData(byteArray->constData() + currentFramePos, bytesInFrame),
                  getAudioFormat());
    currentFramePos += bytesInFrame;
    emit frameRecorded(signal);
}

QAudioFormat SoundRecorder::getAudioFormat() const
{
    return audioFormat;
}

QAudioDeviceInfo SoundRecorder::getAudioDevice() const
{
    return audioDevice;
}

void SoundRecorder::setFrameLength(int length)
{
    audioIn->setNotifyInterval(length);
}

int SoundRecorder::getFrameLength() const
{
    return audioIn->notifyInterval();
}

void SoundRecorder::init(QAudioDeviceInfo device, QAudioFormat format)
{
    audioDevice = device;
    audioFormat = format;
    currentFramePos = 0;
    audioIn = new QAudioInput(device, audioFormat, this);
    audioIn->setNotifyInterval(SoundRecorder::defaultFrameLength);
    byteArray = new QByteArray();
    buffer = new QBuffer(byteArray, this);
}

QAudioFormat SoundRecorder::defaultAudioFormat()
{
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannels(1);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);
    return format;
}
