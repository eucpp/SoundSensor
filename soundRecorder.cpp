#include "soundRecorder.h"

SoundRecorder::SoundRecorder()
{
    defaultFormatSettings();
    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    audioIn = new QAudioInput(device, audioFormat, this);
    audioIn->setNotifyInterval(SoundRecorder::frameLength);
    byteArray = new QByteArray();
    buffer = new QBuffer(byteArray, this);
    currentFramePos = 0;
}
SoundRecorder::~SoundRecorder()
{
    delete byteArray;
}

void SoundRecorder::startRecording()
{
    buffer->open(QIODevice::WriteOnly);
    connect(audioIn, SIGNAL(notify()), this, SLOT(recordFrame()));
    audioIn->start(buffer);
}
void SoundRecorder::stopRecording()
{
    cout << "total: " << buffer->size() << " bytes were recorded" << endl;
    audioIn->stop();
}

void SoundRecorder::recordFrame()
{
    // to do:
    // вычислять кол-во байтов, которое должно содержаться в фрейме (время * част.дискр * др.параметры формата)
    // и кол-во реально записанных байтов,
    // передавать минимальное из этих значений
    qint64 bytesInFrame = buffer->pos() - currentFramePos;
    QByteArray frameBytes = QByteArray::fromRawData(byteArray->constData() + currentFramePos, bytesInFrame);
    currentFramePos += bytesInFrame;
    emit frameRecorded(frameBytes);
}

void SoundRecorder::defaultFormatSettings()
{
    audioFormat.setFrequency(8000);
    audioFormat.setChannels(1);
    audioFormat.setSampleSize(8);
    audioFormat.setCodec("audio/pcm");
    audioFormat.setByteOrder(QAudioFormat::LittleEndian);
    audioFormat.setSampleType(QAudioFormat::SignedInt);
}
