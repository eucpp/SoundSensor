#include "soundRecorder.h"

SoundRecorder::SoundRecorder()
{
    defaultFormatSettings();
    QAudioDeviceInfo device = QAudioDeviceInfo::availableDevices(QAudio::AudioInput).first();
    audioIn = new QAudioInput(device, audioFormat, this);
    audioIn->setNotifyInterval(SoundRecorder::frameLength);
    byteArray = new QByteArray();
    buffer = new QBuffer(byteArray, this);
    currentPos = 0;
}
SoundRecorder::~SoundRecorder()
{
    delete byteArray;
}

void SoundRecorder::startRecording()
{
    buffer->open(QIODevice::ReadWrite);
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
    qint64 pos = buffer->pos();
    buffer->seek(currentPos);
    QByteArray* frameBytes = new QByteArray(buffer->read(pos - currentPos));
    buffer->seek(pos);
    currentPos = pos;
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
