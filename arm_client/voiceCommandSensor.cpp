#include "voiceCommandSensor.h"

VoiceCommandSensor::VoiceCommandSensor(QString pathToHmm, QString pathToLm, QString pathToDict)
    throw(PocketSphinxInitExc)
{
    config = cmd_ln_init(NULL, ps_args(), TRUE,
                         "-hmm", pathToHmm.toAscii().data(),
                         "-jsgf", pathToLm.toAscii().data(),
                         "-dict", pathToDict.toAscii().data(),

                         //"-dither", "1",
                         NULL);
    if (config == NULL)
        throw PocketSphinxInitExc();
    recognizer = ps_init(config);
    if (recognizer == NULL)
        throw PocketSphinxInitExc();
}

VoiceCommandSensor::~VoiceCommandSensor()
{
    ps_free(recognizer);
}

VoiceCommandSensor::Command VoiceCommandSensor::recognize(Signal signal)
{
    const char* uttid;
    int uttReturn = ps_start_utt(recognizer, NULL);
    if (uttReturn < 0)
        throw PocketSphinxInitExc();

    if ((signal.sampleSize() != 2) || (signal.getFormat().sampleType() != QAudioFormat::SignedInt))
    {
        throw IncorrectSignalFormat();
    }

    QScopedArrayPointer<short> samples(reinterpret_cast<short*>(signal.data()));
    int decodeReturn = ps_process_raw(recognizer, samples.data(),
                                  signal.size(), false, false);

    if (decodeReturn < 0)
        throw PocketSphinxRecognizeExc();

    uttReturn = ps_end_utt(recognizer);
    if (uttReturn < 0)
        throw PocketSphinxRecognizeExc();

    Command cmd;
    int score;
    const char* hyp = ps_get_hyp(recognizer, &score, &uttid);
    if (hyp == NULL)
    {
        cmd.command = QString();
        cmd.accuracy = 0;
    }
    else
    {
        cmd.command = hyp;
        cmd.accuracy = static_cast<double>(MAX_INT16 + ps_get_prob(recognizer, &uttid)) / MAX_INT16;
    }

    emit commandRecognized(cmd);
    return cmd;
}