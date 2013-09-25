/*!
 *  ======== IAUDENC1_DENOISE ========
 *  IAUDENC1_DENOISE codec specification
 *
 *  This file specifies information necessary to integrate with the Codec
 *  Engine.
 *
 */
metaonly module IAUDENC1_DENOISE inherits ti.sdo.ce.audio1.IAUDENC1
{
    /*!
     *  ======== ialgFxns ========
     *  name of this algorithm's xDAIS alg fxn table
     */
    override readonly config String ialgFxns = "TRIK_IAUDENC1_DENOISE_FXNS";

}
