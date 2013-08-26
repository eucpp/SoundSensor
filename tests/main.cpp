#include <QtTest>

#include "arm_client/signal/sampleTest.h"
#include "arm_client/signal/signalTest.h"
#include "arm_client/recording/wavFileTest.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SampleTest sampleTest;
    QTest::qExec(&sampleTest);

    SignalTest signalTest;
    QTest::qExec(&signalTest);

    WavFileTest wavFileTest;
    QTest::qExec(&wavFileTest);

    /*
    FourierTransformTest ftTest;
    QTest::qExec(&ftTest);

    CorrelatorTest correlatorTest;
    QTest::qExec(&correlatorTest);

    CorrelatorsTimeTest corrTTest;
    QTest::qExec(&corrTTest);
    */

    return a.exec();
}
