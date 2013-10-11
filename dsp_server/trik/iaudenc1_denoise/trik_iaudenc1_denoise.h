#ifndef TRIK_IAUDENC1_DENOISE_H
#define TRIK_IAUDENC1_DENOISE_H

#include <xdc/std.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iaudenc1.h>

#include "include/internal/denoise.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


/*
* ======== TRIK_IAUDENC1_DENOISE ========
* Our implementation of the IAUDENC1 interface for the reducing noise in the audio signal
*/
extern IAUDENC1_Fxns TRIK_IAUDENC1_DENOISE_FXNS;
extern IALG_Fxns TRIK_IAUDENC1_DENOISE_IALG;


typedef struct TRIK_IAUDENC1_DENOISE_Params {
    IAUDENC1_Params	base;

} TRIK_IAUDENC1_DENOISE_Params;

typedef struct TRIK_IAUDENC1_DENOISE_DynamicParams {
    IAUDENC1_DynamicParams	base;

} TRIK_IAUDENC1_DENOISE_DynamicParams;


typedef struct TRIK_IAUDENC1_DENOISE_InArgs {
    IAUDENC1_InArgs	base;

} TRIK_IAUDENC1_DENOISE_InArgs;

typedef struct TRIK_IAUDENC1_DENOISE_OutArgs {
    IAUDENC1_OutArgs	base;

} TRIK_IAUDENC1_DENOISE_OutArgs;


typedef struct TrikDenoiseHandle {
    IALG_Obj	m_alg;	/* MUST be first field of all XDAIS algs */

    TRIK_IAUDENC1_DENOISE_Params	m_params;
    TRIK_IAUDENC1_DENOISE_DynamicParams	m_dynamicParams;
} TrikDenoiseHandle;


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // TRIK_IAUDENC1_DENOISE_H
