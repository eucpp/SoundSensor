#include "tmp.h"
using namespace std;

void experiment(QString word, QString path, QString testname)
{
    const int repeat = 1;
    const int filesNum = 5;

    QFile output(testname);
    output.open(QFile::Append);

    VoiceCommandSensor sensor(
                "/home/evgeniy/projects/SoundSensor/trained_model/hub4wsj_sc_8kadapt",
                "./voiceCommands.lm",
                "./voiceCommands.dic");
    for (int i = 1; i <= filesNum; i++)
    {
        QString filename = path + word + "_" + QString().setNum(i) + ".wav";
        WavFile file(filename);
        file.open(WavFile::ReadOnly);
        Signal signal = file.readSignal();
        for (int j = 0; j < repeat; j++)
        {
            VoiceCommandSensor::Command cmd = sensor.recognizeCommand(signal);
            QString str;

            cout << cmd.command.toLower().toAscii().data() << endl;
            cout << word.toAscii().data() << endl;

            if (cmd.command.toLower() == word)
                str.setNum(1);
            else
                str.setNum(0);
            str += "; ";
            str += QString().setNum(cmd.accuracy);
            str.replace('.', ',');
            str += '\n';
            output.write(str.toAscii().data());
        }
        file.close();
    }

    output.close();
}

void printStatistics()
{
    QString path = "/home/evgeniy/projects/SoundSensor/voice_commands_tests/";
    // файл в который пишутся результаты эксперимента

    QVector<QString> experiments;

    /*
    experiments.push_front("close_noise_tests");
    experiments.push_front("close_noise_tests_44100");
    experiments.push_front("close_tests");
    experiments.push_front("close_tests_44100");
    experiments.push_front("close_noise_gain_tests");
    experiments.push_front("close_gain_tests");
    experiments.push_front("far_tests");
    experiments.push_front("far_noise_tests");
    experiments.push_front("close_noise_tests_16000");
    experiments.push_front("close_tests_16000");
    experiments.push_front("far_tests_16000");
    */

    experiments.push_front("far_noise_tests_16000");

    QVectorIterator<QString> iter(experiments);
    while (iter.hasNext())
    {
        QString test = iter.next();
        experiment("go", path + test + "/", test + ".csv");
        experiment("stop", path + test + "/", test + ".csv");
    }
}

