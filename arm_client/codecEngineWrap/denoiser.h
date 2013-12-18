#ifndef DENOISER_H
#define DENOISER_H

#include <QObject>

#include "codecEngine.h"

#include <libcodecengine-client/codecengine-client.h>
#include <ti/sdo/ce/audio1/audenc1.h>

class Denoiser : public QObject
{
	Q_OBJECT
public:
	Denoiser(const trik::CodecEngine& ce, QObject *parent = 0);

	void testProcess();
signals:

public slots:

private:
	size_t memoryAlloc(void* ptr, size_t size);

	AUDENC1_Handle mHandle;
};

#endif // DENOISER_H
