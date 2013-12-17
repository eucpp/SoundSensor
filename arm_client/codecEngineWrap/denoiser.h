#ifndef DENOISER_H
#define DENOISER_H

#include <QObject>

#include <ti/sdo/ce/audio1/audenc1.h>

#include "trikognitionCE.h"

class Denoiser : public QObject
{
	Q_OBJECT
public:
	Denoiser(const TrikognitionCE& ce, QObject *parent = 0);

	void testProcess();
signals:

public slots:
	XDAS_Int32 testProcess();

private:
	size_t memoryAlloc(void* ptr, size_t size);

	AUDENC1_Handle mHandle;
};

#endif // DENOISER_H
