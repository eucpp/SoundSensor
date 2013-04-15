#include "wavFile.h"

WavFile::WavFile(QString filename):
    QFile(filename)
{}

QAudioFormat WavFile::readHeader()
{
    qint64 currPos = pos();
    seek(0);
    char* headerBytes = read(sizeof(Header)).data();
    seek(currPos);

    // здесь надо бы ещё добавить проверку корректности заголовка
    // если заголовок некорректный, кидаем исключение, например

    Header* header = reinterpret_cast<Header*>(headerBytes);
    QAudioFormat format;
    // пока просто пишем pcm
    // to do: запись формата из хедера
    format.setCodec("audio/pcm");
    format.setSampleRate(header->sampleRate);
    format.setChannels(header->numChannels);
    format.setSampleSize(header->bitsPerSample);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    return format;
}

void WavFile::writeHeader(QAudioFormat format, unsigned int dataSize)
{
    if (openMode() != QIODevice::WriteOnly || size() != 0)
        return;

    Header header;
    header.chunkId[0]='R';
    header.chunkId[1]='I';
    header.chunkId[2]='F';
    header.chunkId[3]='F';

    header.chunkSize = 36 + dataSize;

    header.format[0] = 'W';
    header.format[1] = 'A';
    header.format[2] = 'V';
    header.format[3] = 'E';

    header.subchunk1Id[0] = 'f';
    header.subchunk1Id[1] = 'm';
    header.subchunk1Id[2] = 't';
    header.subchunk1Id[3] = ' ';

    header.subchunk1Size = 16;
    // пока пишем pcm
    // to do: запись кодека из QAudioFormat
    header.audioFormat = 1;
    header.numChannels = format.channels();
    header.sampleRate = format.frequency();
    header.byteRate = header.sampleRate * header.numChannels * format.sampleSize() / 8;
    header.blockAlign = header.numChannels * format.sampleSize() / 8;
    header.bitsPerSample = format.sampleSize();

    header.subchunk2Id[0] = 'd';
    header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';

    header.subchunk2Size = dataSize;

    char* bytes = reinterpret_cast<char*>(&header);
    seek(0);
    write(bytes, sizeof(Header));
}

Signal WavFile::readSignal()
{
    QAudioFormat format = readHeader();
    unsigned int soundSize = dataSize();
    seek(44);
    QByteArray bytes = read(soundSize);
    return Signal(bytes, format);
}
void WavFile::writeSignal(Signal signal)
{
    seek(0);
    writeHeader(signal.getFormat(), signal.size());
    seek(44);
    write(signal.getBytes());
}

unsigned int WavFile::dataSize()
{
    qint64 currPos = pos();
    seek(40);
    char* charSize = new char[5];
    read(charSize, 4);
    charSize[4] = '\0';
    seek(currPos);
    unsigned int* pSize = reinterpret_cast<unsigned int*>(charSize);
    unsigned int size = *pSize;
    delete charSize;
    return size;
}
