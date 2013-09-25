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

}


