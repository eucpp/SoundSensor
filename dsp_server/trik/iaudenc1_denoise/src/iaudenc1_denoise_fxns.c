#include <xdc/std.h>

#ifdef __TI_COMPILER_VERSION__ /* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(TRIK_IAUDENC1_DENOISE_control, ".text:algControl")
#pragma CODE_SECTION(TRIK_IAUDENC1_DENOISE_process, ".text:algProcess")
#pragma CODE_SECTION(TRIK_IAUDENC1_DENOISE_initObj, ".text:algInit")
#pragma CODE_SECTION(TRIK_IAUDENC1_DENOISE_free, ".text:algFree")
#pragma CODE_SECTION(TRIK_IAUDENC1_DENOISE_alloc, ".text:algAlloc")
#endif

#include "../trik_iaudenc1_denoise.h"

Int TRIK_IAUDENC1_DENOISE_alloc(const IALG_Params* _algParams,
                                IALG_Fxns** _algFxns,
                                IALG_MemRec _algMemTab[]);

Int TRIK_IAUDENC1_DENOISE_free(IALG_Handle _algHandle,
                               IALG_MemRec _algMemTab[]);

Int TRIK_IAUDENC1_DENOISE_initObj(IALG_Handle _algHandle,
                                  const IALG_MemRec _algMemTab[],
                                  IALG_Handle _algParent,
                                  const IALG_Params* _algParams);

XDAS_Int32 TRIK_IAUDENC1_DENOISE_process(IAUDENC1_Handle _algHandle,
                                         XDM1_BufDesc* _xdmInBufs, XDM_BufDesc* _xdmOutBufs,
                                         TRIK_IAUDENC1_DENOISE_InArgs* _inArgs,
                                         TRIK_IAUDENC1_DENOISE_OutArgs* _outArgs);

XDAS_Int32 TRIK_IAUDENC1_DENOISE_control(IAUDENC1_Handle _algHandle,
                                         IAUDENC1_Cmd _vidCmd,
                                         TRIK_IAUDENC1_DENOISE_DynamicParams* _vidDynParams,
                                         IAUDENC1_Status* _vidStatus);


#define TRIK_IAUDENC1_DENOISE_IALGFXNS \
&TRIK_IAUDENC1_DENOISE_IALG, /* module ID */	\
NULL, /* activate */	\
TRIK_IAUDENC1_DENOISE_alloc, /* alloc */	\
NULL, /* control (NULL => no control ops) */	\
NULL, /* deactivate */	\
TRIK_IAUDENC1_DENOISE_free, /* free */	\
TRIK_IAUDENC1_DENOISE_initObj, /* init */	\
NULL, /* moved */	\
NULL /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
* ======== TRIK_IAUDENC1_DENOISE_FXNS ========
* This structure defines TRIK's implementation of the IAUDENC1 interface
* for the TRIK_IAUDENC1_DENOISE module.
*/
IAUDENC1_Fxns TRIK_IAUDENC1_DENOISE_FXNS = {
    {TRIK_IAUDENC1_DENOISE_IALGFXNS},
    TRIK_IAUDENC1_DENOISE_process,
    TRIK_IAUDENC1_DENOISE_control,
};

/*
* ======== TRIK_IAUDENC1_DENOISE_IALG ========
* This structure defines TRIK's implementation of the IALG interface
* for the TRIK_IAUDENC1_DENOISE module.
*/
#ifdef __TI_COMPILER_VERSION__ /* satisfy XDAIS symbol requirement without any overhead */

# if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)
/* Symbol doesn't have any leading underscores */
asm("TRIK_IAUDENC1_DENOISE_IALG .set TRIK_IAUDENC1_DENOISE_FXNS");
# else // defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)
/* Symbol has a single leading underscore */
asm("_TRIK_IAUDENC1_DENOISE_IALG .set _TRIK_IAUDENC1_DENOISE_FXNS");
# endif // !defined(__TI_ELFABI__) && !defined(__TI_EABI_SUPPORT__)

#else // __TI_COMPILER_VERSION__

/*
* We duplicate the structure here to allow this code to be compiled and
* run using non-TI toolchains at the expense of unnecessary data space
* consumed by the definition below.
*/
IALG_Fxns TRIK_IAUDENC1_DENOISE_IALG = {
    TRIK_IAUDENC1_DENOISE_IALGFXNS
};
#endif // !__TI_COMPILER_VERSION__

static const char s_version[] = "1.00.00.00";


static XDAS_Int32 setupDynamicParams(TrikDenoiseHandle* _handle,
                                                 const TRIK_IAUDENC1_DENOISE_DynamicParams* _dynamicParams)
{
    static const TRIK_IAUDENC1_DENOISE_DynamicParams default_dyn_params = {
        {
            sizeof(TRIK_IAUDENC1_DENOISE_DynamicParams),    //size
            16 * 16000,                                     //bitRate
            16000,                                          //sampleRate
            IAUDIO_1_0,                                     //channelMode
            XDAS_FALSE,                                     //lfeFlag
            IAUDIO_DUALMONO_LR,                             //dualMonoMode
            IAUDIO_CBR,                                  	//inputBitsPerSample
        }
    };

    if (_dynamicParams == NULL) {
        dyn_params = default_dyn_params;
    }
    else {
        dyn_params = *_dynamicParams;
    }
    _handle->m_dynamicParams = dyn_params;

    return IALG_EOK;
}

/*
* ======== TRIK_IAUDENC1_DENOISE_alloc ========
* Return a table of memory descriptors that describe the memory needed
* to construct our object.
*/
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int TRIK_IAUDENC1_DENOISE_alloc(
    const IALG_Params*	_algParams,
    IALG_Fxns**	_algFxns,
    IALG_MemRec	_algMemTab[])
{
    /* Request memory for my object, ignoring algParams */
    _algMemTab[0].size	= sizeof(TrikDenoiseHandle);
    _algMemTab[0].alignment	= 0;
    _algMemTab[0].space	= IALG_EXTERNAL;
    _algMemTab[0].attrs	= IALG_PERSIST;

    /* Return the number of records in the memTab */
    return 1;
}


/*
* ======== TRIK_IAUDENC1_DENOISE_free ========
* Return a table of memory pointers that should be freed. Note
* that this should include *all* memory requested in the
* alloc operation above.
*/
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int TRIK_IAUDENC1_DENOISE_free(
    IALG_Handle	_algHandle,
    IALG_MemRec	_algMemTab[])
{
    TrikDenoiseHandle* handle = (TrikDenoiseHandle*)_algHandle;

    /* Returned data must match one returned in alloc */
    _algMemTab[0].base	= handle;
    _algMemTab[0].size	= sizeof(TrikCvHandle);
    _algMemTab[0].alignment	= 0;
    _algMemTab[0].space	= IALG_EXTERNAL;
    _algMemTab[0].attrs	= IALG_PERSIST;

    /* Return the number of records in the memTab */
    return 1;
}


/*
* ======== TRIK_IAUDENC1_DENOISE_initObj ========
* Initialize the memory allocated on our behalf (including our object).
*/
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int TRIK_IAUDENC1_DENOISE_initObj(
    IALG_Handle	_algHandle,
    const IALG_MemRec	_algMemTab[],
    IALG_Handle	_algParent,
    const IALG_Params*	_algParams)
{
    TrikDenoiseHandle* handle = (TrikDenoiseHandle*)_algHandle;
    XDAS_Int32 res;

    static const TRIK_IAUDENC1_DENOISE_Params default_params = {
        {                                           // base
            sizeof(TRIK_IAUDENC1_DENOISE_Params),   // size
            16000,                                  //sampleRate
            16 * 16000,                             //bitRate
            IAUDIO_1_0,                             //channelMode
            XDM_LE_16,                              //dataEndianness
            IAUDIO_CBR,                             //encMode
            IAUDIO_BLOCK,                           //inputFormat
            16,                                  	//inputBitsPerSample
            16 * 16000,                          	//maxBitRate
            IAUDIO_DUALMONO_LR,                  	//dualMonoMode
            XDAS_FALSE,                          	//crcFlag
            XDAS_FALSE,                          	//ancFlag
            XDAS_FALSE                           	//lfeFlag
        }
    };

    TRIK_IAUDENC1_DENOISE_Params params = (TRIK_IAUDENC1_DENOISE_Params*)_algParams;
    if (params == NULL) {
        params = &default_params;
    }
    handle->m_params = params;

    XDAS_Int32 res = setupDynamicParams(handle, NULL);
    if (res != IALG_EOK) {
        return res;
    }

    return IALG_EOK;
}



/*
* ======== TRIK_IAUDENC1_DENOISE_process ========
*/
XDAS_Int32 TRIK_IAUDENC1_DENOISE_process(
    IAUDENC1_Handle	_algHandle,
    XDM1_BufDesc*	_xdmInBufs,
    XDM_BufDesc*	_xdmOutBufs,
    TRIK_IAUDENC1_DENOISE_InArgs*	_vidInArgs,
    TRIK_IAUDENC1_DENOISE_OutArgs*	_vidOutArgs)
{
    test_fillOutBuff(_xdmOutBufs);

    return 	IAUDENC1_EOK;
}


/*
* ======== TRIK_IAUDENC1_DENOISE_control ========
*/
XDAS_Int32 TRIK_IAUDENC1_DENOISE_control(
    IAUDENC1_Handle	_algHandle,
    IAUDENC1_Cmd	_vidCmd,
    TRIK_IAUDENC1_DENOISE_DynamicParams*	_vidDynParams,
    IAUDENC1_Status*	_vidStatus)
{
    TrikDenoiseHandle* handle = (TrikDenoiseHandle*)_algHandle;
    XDAS_Int32 retVal = IAUDENC1_EFAIL;

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(_vidStatus->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(_vidStatus->data.accessMask);

    switch (_vidCmd)
    {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            _vidStatus->extendedError = 0;

            _vidStatus->bufInfo.minNumInBufs = 1;
            _vidStatus->bufInfo.minNumOutBufs = 1;
            _vidStatus->bufInfo.minInBufSize[0] = 0;
            _vidStatus->bufInfo.minOutBufSize[0] = 0;

            XDM_SETACCESSMODE_WRITE(_vidStatus->data.accessMask);
            retVal = IAUDENC1_EOK;
            break;

        case XDM_SETPARAMS:
            if (_vidDynParams->base.size == sizeof(TRIK_IAUDENC1_DENOISE_DynamicParams))
                retVal = setupDynamicParams(handle, (TRIK_IAUDENC1_DENOISE_DynamicParams*)_vidDynParams);
            else
                retVal = IAUDENC1_EUNSUPPORTED;
            break;

        case XDM_RESET:
        case XDM_SETDEFAULT:
            retVal = setupDynamicParams(handle, NULL);
            break;

        case XDM_FLUSH:
            retVal = IAUDENC1_EOK;
            break;

        case XDM_GETVERSION:
            if (_vidStatus->data.buf != NULL && _vidStatus->data.bufSize >= strlen(s_version)+1)
            {
                memcpy(_vidStatus->data.buf, s_version, strlen(s_version)+1);
                XDM_SETACCESSMODE_WRITE(_vidStatus->data.accessMask);
                retVal = IAUDENC1_EOK;
            }
            else
                retVal = IAUDENC1_EFAIL;
            break;

        default:
            /* unsupported cmd */
            retVal = IAUDENC1_EFAIL;
            break;
    }

    return retVal;
}
