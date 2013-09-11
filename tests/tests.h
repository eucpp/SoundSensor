#ifndef TESTS_H
#define TESTS_H

#include "arm_client/signal/sampleTest.h"
#include "arm_client/signal/signalTest.h"
#include "arm_client/recording/wavFileTest.h"

// run unit tests
void unitTests();

// run recording test
int recordingTest(const QCoreApplication& a);

// print information about audio devices
void devicesInfo();

#endif // TESTS_H
