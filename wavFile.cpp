#include "wavFile.h"

WavFile::WavFile(const QString &filename):
    file(filename),
    openmode(NotOpen)
{}

QAudioFormat WavFile::open(OpenModes mode)
{
    QAudioFormat format = SoundRecorder::defaultAudioFormat();
    return open(mode, format);
}

QAudioFormat WavFile::open(OpenModes mode, const QAudioFormat& format)
{
    openmode = mode;
    if (openmode == ReadOnly)
    {
        if (!file.open(QIODevice::ReadOnly))
            throw OpenFileExc();
        // проверяем размер заголовка файла
        if (file.size() > 0 && file.size() < 44)
            throw OpenFileExc();
        seek(0);
        dSize = readDataSize();
        return (header = readHeader());
    }
    else if (openmode == WriteOnly)
    {
        if (!file.open(QIODevice::WriteOnly))
            throw OpenFileExc();
        header = format;
        writeHeader(header);
        seek(0);
        dSize = 0;
        return header;
    }
    else if (openmode == Append)
    {
        if (!file.open(QIODevice::Append))
            throw OpenFileExc();
        seek(0);
        dSize = readDataSize();
        return (header = readHeader());
    }
    else if (openmode == ReadWrite)
    {
        if (!file.open(QIODevice::ReadWrite))
            throw OpenFileExc();
        seek(0);
        dSize = readDataSize();
        return (header = readHeader());
    }
}
void WavFile::close()
{
    file.close();
}

bool WavFile::isOpen() const
{
    return file.isOpen();
}

bool inline WavFile::seek(unsigned int pos)
{
    return file.seek(pos + 44);
}

unsigned int inline WavFile::pos()
{
    unsigned int tmp = file.pos();
    return file.pos() - 44;
}

Signal WavFile::readSignal() throw(ReadDisabledExc)
{
    if (openmode == NotOpen)
        return Signal();
    if (openmode == WriteOnly)
        throw ReadDisabledExc();
    unsigned int soundSize = dataSize();
    QByteArray bytes = file.read(soundSize);
    return Signal(bytes, header);
}
void WavFile::writeSignal(Signal signal) throw(WriteDisabledExc)
{
    if (openmode == NotOpen)
        return;
    if (openmode == ReadOnly)
        throw WriteDisabledExc();

    unsigned int overlay = dSize - pos();
    if (signal.getFormat() == header)
        file.write(signal.getBytes());
    else
    {
        // временный код:
        // преобразуем сигнал к нужному формату
        // to do: запись "на лету", без преобразования
        Signal tmpSignal(signal.getBytes(), signal.getFormat());
        tmpSignal.setFormat(header);
        file.write(tmpSignal.getBytes());
    }
    dSize = signal.getBytes().size() - overlay;
    setDataSize(dSize);
}

unsigned int WavFile::dataSize()
{
    return dSize;
}

QAudioFormat WavFile::readHeader()
{
    qint64 currPos = pos();
    file.seek(0);
    QByteArray headerArrayBytes = file.read(sizeof(Header));
    const char* headerBytes = headerArrayBytes.constData();
    seek(currPos);

    // здесь надо бы ещё добавить проверку корректности заголовка
    // если заголовок некорректный, кидаем исключение, например

    const Header* pHeader = reinterpret_cast<const Header*>(headerBytes);
    QAudioFormat format;
    format.setCodec("audio/pcm");
    format.setSampleRate(pHeader->sampleRate);
    format.setChannels(pHeader->numChannels);
    format.setSampleSize(pHeader->bitsPerSample);
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);


    return format;
}

void WavFile::writeHeader(const QAudioFormat& format)
{
    Header header;
    header.chunkId[0]='R';
    header.chunkId[1]='I';
    header.chunkId[2]='F';
    header.chunkId[3]='F';

    header.chunkSize = 36;

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
    header.sampleRate = format.sampleRate();
    header.byteRate = header.sampleRate * header.numChannels * format.sampleSize() / 8;
    header.blockAlign = header.numChannels * format.sampleSize() / 8;
    header.bitsPerSample = format.sampleSize();

    header.subchunk2Id[0] = 'd';
    header.subchunk2Id[1] = 'a';
    header.subchunk2Id[2] = 't';
    header.subchunk2Id[3] = 'a';

    header.subchunk2Size = 0;

    char* bytes = reinterpret_cast<char*>(&header);
    qint64 currPos = pos();
    file.seek(0);
    file.write(bytes, sizeof(Header));
    seek(currPos);
}

void WavFile::setDataSize(unsigned int size)
{
    qint64 currPos = pos();
    file.seek(40);
    file.write(reinterpret_cast<char*>(&size), 4);
    seek(currPos);
}
unsigned int WavFile::readDataSize()
{
    unsigned int currPos = pos();
    file.seek(40);
    char* charSize = new char[5];
    file.read(charSize, 4);
    charSize[4] = '\0';
    seek(currPos);
    unsigned int* pSize = reinterpret_cast<unsigned int*>(charSize);
    unsigned int size = *pSize;
    delete[] charSize;
    return size;
}
