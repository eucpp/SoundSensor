#include "../include/internal/denoise.h"


void test_fillOutBuff(XDM1_BufDesc* outBuff)
{
    outBuff->numBufs = 1;

    XDM_SETACCESSMODE_READ(outBuff->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBuff->descs[0].accessMask);

    outBuff->descs[0].bufSize = 10;
    for (int i = 0; i < outBuff->descs[0].bufSize; i++) {
        outBuff->descs[0].buf[i] = 0;
    }

    return;
}
