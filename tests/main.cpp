#include <QtTest>

#include "tests.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if (argc == 0)
    {
        a.quit();
    }
    else
    {
        QString cmd(argv[1]);
        // run unit tests
        if ((cmd == "unit") || (cmd == "-u"))
        {
            unitTests();
            a.quit();
        }
        else if ((cmd == "rec") || (cmd == "-r"))
        {
            recordingTest(a);
        }
        else if ((cmd == "adev") || (cmd == "-d"))
        {
            devicesInfo();
        }
    }

    return a.exec();
}
