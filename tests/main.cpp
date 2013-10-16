#include <QtTest>

#include <iostream>

#include "tests.h"

using namespace std;

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
        else if ((cmd == "denoise") || (cmd == "-n"))
        {
            if (argc < 5)
            {
                cout << "Too few arguments!" << endl;
                a.quit();
            }
            denoiseTest(argv[2], argv[3], argv[4]);
        }

        a.quit();
    }

    return a.exec();
}
