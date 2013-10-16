#ifndef TESTS_H
#define TESTS_H

#include "arm_client/signal/sampleTest.h"
#include "arm_client/signal/signalTest.h"
#include "arm_client/recording/wavFileTest.h"

#include "dsp_server/denoise/denoiseTest.h"

// run unit tests
void unitTests();

// run recording test
int recordingTest(const QCoreApplication& a);

// print information about audio devices
void devicesInfo();

// denoise test
void denoiseTest(char* signalFileName, char* noiseFileName, char* outputFileName);

#endif // TESTS_H
