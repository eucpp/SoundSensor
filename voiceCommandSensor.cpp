#include "voiceCommandSensor.h"

VoiceCommandSensor::VoiceCommandSensor(QString pathToHmm, QString pathToLm, QString pathToDict)
    throw(PocketSphinxInitExc)
{
    config = cmd_ln_init(NULL, ps_args(), TRUE,
                         "-hmm", pathToHmm.toAscii().data(),
                         "-lm", pathToLm.toAscii().data(),
                         "-dict", pathToDict.toAscii().data(),
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

VoiceCommandSensor::Command VoiceCommandSensor::recognizeCommand(Signal signal)
{
    char const *uttid;
    int uttReturn = ps_start_utt(recognizer, uttid);
    if (uttReturn < 0)
        throw PocketSphinxInitExc();

    int decodeReturn = ps_process_raw(recognizer, signal.get16bitSamples(),
                                  signal.size() * 2, false, false);
    if (decodeReturn < 0)
        throw PocketSphinxRecognizeExc();

    uttReturn = ps_end_utt(recognizer);
    if (uttReturn < 0)
        throw PocketSphinxRecognizeExc();

    Command cmd;
    int score;
    // если ничего не распознанно, возвращать пустую строку и
    // точность = 0
    cmd.command = ps_get_hyp(recognizer, &score, &uttid);
    if (cmd.command == NULL)
        throw PocketSphinxRecognizeExc();
    cmd.accuracy = - static_cast<double>(ps_get_prob(recognizer, &uttid)) / MAX_INT16;

    emit commandRecognized(cmd);
    return cmd;
}
