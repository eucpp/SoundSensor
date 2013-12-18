#include <cstring>

#include <QDebug>

#include "denoiser.h"

#define ALIGN_UP(v, a) ((((v)+(a)-1)/(a))*(a))

Denoiser::Denoiser(const trik::CodecEngine& ce, QObject* parent)
{
	qDebug() << "create audenc1";

	mHandle = ce.createAUDENC1();
	if (mHandle == NULL) {
		qDebug() << "AUDENC1 create failed";
		return;
	}

	qDebug() << "set dynamic params";

	AUDENC1_Status status;
	memset((void*)&status, 0 , sizeof(status));
	XDAS_Int32 res = AUDENC1_control(mHandle, XDM_SETPARAMS, NULL, &status);
	if (res != AUDENC1_EOK) {
		qDebug() << "AUDENC1 control failed";
		return;
	}
}

void Denoiser::testProcess()
{
	qDebug() << "memory alloc for inBuf";

	XDM1_SingleBufDesc inBuf;
	memset((void*)&inBuf, 0, sizeof(inBuf));
	inBuf.bufSize = 10;
	size_t size = memoryAlloc(inBuf.buf, inBuf.bufSize);

	memset(inBuf.buf, 0, size);

	XDM1_BufDesc inBufDesc;
	memset((void*)&inBufDesc, 0, sizeof(inBufDesc));
	inBufDesc.numBufs = 1;
	inBufDesc.descs[0] = inBuf;

	IAUDENC1_InArgs inArgs;
	memset((void*)&inArgs, 0, sizeof(inArgs));
	inArgs.size = sizeof(inArgs);
	inArgs.numInSamples = 0;

	qDebug() << "memory alloc for outBuf";

	XDM1_SingleBufDesc outBuf;
	memset((void*)&inBuf, 0, sizeof(outBuf));
	outBuf.bufSize = 10;
	size_t outSize = memoryAlloc(outBuf.buf, outBuf.bufSize);

	memset((void*)inBuf.buf, 0, outSize);

	XDM1_BufDesc outBufDesc;
	memset((void*)&outBufDesc, 0, sizeof(outBufDesc));
	outBufDesc.numBufs = 1;
	outBufDesc.descs[0] = outBuf;

	IAUDENC1_OutArgs outArgs;
	memset((void*)&outArgs, 0, sizeof(outArgs));
	outArgs.size = sizeof(outArgs);
	outArgs.numInSamples = 0;

	qDebug() << "process ";

	XDAS_Int32 res = AUDENC1_process(mHandle, &inBufDesc, &outBufDesc, &inArgs, &outArgs);
	if (res != AUDENC1_EOK) {
		qDebug() << "AUDENC1 process failed";
	}

	XDAS_Int8* buf = outBuf.buf;
	for (int i = 0; i < 10; i++) {
		if (buf[i] != (char)i) {
			qDebug() << 'A' + (char)buf[i];
			qDebug() << "MISMATCH at " << i;
		}
	}
}

size_t Denoiser::memoryAlloc(void* ptr, size_t size)
{
	const size_t bufalign = 128;

	Memory_AllocParams allocParams;
	memset((void*)&allocParams, 0, sizeof(allocParams));
	allocParams.type = Memory_CONTIGPOOL;
	allocParams.flags = Memory_NONCACHED;
	allocParams.align = bufalign;
	allocParams.seg = 0;

	size_t actualSize = ALIGN_UP(size, bufalign);
	ptr = Memory_alloc(actualSize, &allocParams);
	if (ptr == NULL)
	{
		qDebug() << "Memory allocation error.";
	}
}
