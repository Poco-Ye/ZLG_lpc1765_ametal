/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Phase Locked Loop (PLL) implementation for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "amhw_pll.h"
#include "amhw_clock.h"
#include "amhw_lib_power.h"

/*******************************************************************************
* Local Macro defines
*******************************************************************************/

#define __PLL_N_MAX            (0x100)     /**< \brief The PLL N-divider Max value   */
#define __PLL_P_MAX            (0x20)      /**< \brief The PLL P-divider Max value   */
#define __PLL_M_MAX            (0x8000)    /**< \brief The PLL M-divider Max value   */

#define __PLL_MIN_CCO_FREQ_HZ  (75000000)  /**< \brief min CCO Freq                  */
#define __PLL_MAX_CCO_FREQ_HZ  (150000000) /**< \brief maximum CCO Freq              */

#define __PLL_LOWER_IN_LIMIT   (4000)      /**< \brief Minimum PLL input rate        */
#define __PLL_MIN_IN_SSMODE    (2000000)   /**< \brief Minimum input freq in ss mode */
#define __PLL_MAX_IN_SSMODE    (4000000)   /**< \brief maximum input freq in ss mode */

/** 
 * \brief System PLL control register Bits
 */
#define __PLL_SELR_P                    0
#define __PLL_SELR_M                   (0xFUL  << __PLL_SELR_P)
#define __PLL_SELI_P                    4
#define __PLL_SELI_M                   (0x3FUL << __PLL_SELI_P)
#define __PLL_SELP_P                    10
#define __PLL_SELP_M                   (0x1FUL << __PLL_SELP_P)
#define __PLL_BYPASS_P                  15
#define __PLL_BYPASS                   (1UL << __PLL_BYPASS_P)
#define __PLL_BYPASS_FBDIV2_P           16
#define __PLL_BYPASS_FBDIV2            (1UL << __PLL_BYPASS_FBDIV2_P)
#define __PLL_UPLIMOFF_P                17
#define __PLL_UPLIMOFF                 (1UL << __PLL_UPLIMOFF_P)
#define __PLL_BANDSEL_SSCGREG_N_P       18
#define __PLL_BANDSEL_SSCGREG_N        (1UL << __PLL_BANDSEL_SSCGREG_N_P)
#define __PLL_DIRECTI_P                 19
#define __PLL_DIRECTI                  (1UL << __PLL_DIRECTI_P)
#define __PLL_DIRECTO_P                 20
#define __PLL_DIRECTO                  (1UL << __PLL_DIRECTO_P)

/** 
 * \brief System PLL status register Bits 
 */
#define __PLL_STAT_LOCK_P               0
#define __PLL_STAT_LOCK                (1UL << __PLL_STAT_LOCK_P)

/** 
 * \brief SSCG control[0] register Bits   
 */

/** \brief MDEC is in bits  16 down to 0 */
#define __PLL_SSCG0_MDEC_VAL_P           (0)
#define __PLL_SSCG0_MDEC_VAL_M           (0x1FFFFUL << __PLL_SSCG0_MDEC_VAL_P)

#define __PLL_SSCG0_MDEC_VAL_SET(value)  (((unsigned long) (value)     \
                                            << __PLL_SSCG0_MDEC_VAL_P) \
                                            & __PLL_SSCG0_MDEC_VAL_M)
            
#define __PLL_SSCG0_MREQ_P                17
#define __PLL_SSCG0_MREQ                 (1 << __PLL_SSCG0_MREQ_P)
#define __PLL_SSCG0_SEL_EXT_SSCG_N_P      18
#define __PLL_SSCG0_SEL_EXT_SSCG_N       (1 << __PLL_SSCG0_SEL_EXT_SSCG_N_P)

/** 
 * \brief SSCG control[1] register Bits 
 */

/** \brief Bit[10:0] fractional portion of the feedback divider value */
#define __PLL_SSCG1_MD_FRACT_P             0
#define __PLL_SSCG1_MD_FRACT_M            (0x7FFUL << __PLL_SSCG1_MD_FRACT_P)        
#define __PLL_SSCG1_MD_FRACT_SET(value)   (((unsigned long) (value)    \
                                           << __PLL_SSCG1_MD_FRACT_P) \
                                           & __PLL_SSCG1_MD_FRACT_M)

/** 
 * \brief Bit[18:11] integer portion of the feedback divider value  
 */
#define __PLL_SSCG1_MD_INT_P               11
#define __PLL_SSCG1_MD_INT_M              (0xFFUL << __PLL_SSCG1_MD_INT_P)   
#define __PLL_SSCG1_MD_INT_SET(value)     (((unsigned long) (value)   \
                                            << __PLL_SSCG1_MD_INT_P) \
                                            & __PLL_SSCG1_MD_INT_M)

#define __PLL_SSCG1_MD_REQ_P               19
#define __PLL_SSCG1_MD_REQ                (1 << __PLL_SSCG1_MD_REQ_P)
        
#define __PLL_SSCG1_MF_P                   20
#define __PLL_SSCG1_MF_M                  (0x7UL << __PLL_SSCG1_MF_P)             
#define __PLL_SSCG1_MR_P                   23
#define __PLL_SSCG1_MR_M                  (0x7UL << __PLL_SSCG1_MR_P)
#define __PLL_SSCG1_MC_P                   26
#define __PLL_SSCG1_MC_M                  (0x3UL << __PLL_SSCG1_MC_P)

#define __PLL_SSCG1_MOD_PD_SSCGCLK_N_P     28
#define __PLL_SSCG1_MOD_PD_SSCGCLK_N      (1 << __PLL_SSCG1_MOD_PD_SSCGCLK_N_P)
#define __PLL_SSCG1_DITHER_P               29
#define __PLL_SSCG1_DITHER                (1 << __PLL_SSCG1_DITHER_P)

/** 
 * \brief PLL N-divider register Bits.
 */
 
/** \brief NDEC is in bits 9:0 */
#define __PLL_NDEC_VAL_P                  (0)    
#define __PLL_NDEC_VAL_M                  (0x3FFUL << __PLL_NDEC_VAL_P)
#define __PLL_NDEC_VAL_SET(value)         (((unsigned long) (value) \
                                            << __PLL_NDEC_VAL_P)    \
                                            & __PLL_NDEC_VAL_M)
            
#define __PLL_NDEC_NREQ_P                 (10)
#define __PLL_NDEC_NREQ                   (1 << __PLL_NDEC_NREQ_P)

/** 
 * \brief PLL P-divider register Bits.
 */
 
/** \brief PDEC is in bits 6:0 */
#define __PLL_PDEC_VAL_P                  (0)     
#define __PLL_PDEC_VAL_M                  (0x3FFUL << __PLL_PDEC_VAL_P)

#define __PLL_PDEC_VAL_SET(value)         (((unsigned long) (value) \
                                            << __PLL_PDEC_VAL_P)    \
                                            & __PLL_PDEC_VAL_M)

#define ___PLL_PDEC_PREQ_P                (7)
#define __PLL_PDEC_PREQ                   (1 << ___PLL_PDEC_PREQ_P)

/*******************************************************************************
* Local Functions
*******************************************************************************/

/** 
 * \brief Find encoded NDEC value for raw N value, maximum N = __PLL_N_MAX.
 */
static uint32_t __pll_n_encode (uint32_t n)
{
    uint32_t x, i;

    /* Find NDec */
    switch (n) {
    case 0:
        x = 0xFFF;
        break;

    case 1:
        x = 0x302;
        break;

    case 2:
        x = 0x202;
        break;

    default:
        x = 0x080;
        for (i = n; i <= __PLL_N_MAX; i++) {
            x = (((x ^ (x >> 2) ^ (x >> 3) ^ (x >> 4)) & 1) << 7) 
                                           | ((x >> 1) & 0x7F);
        }
        break;
    }

    return x & (__PLL_NDEC_VAL_M >> __PLL_NDEC_VAL_P);
}

/** 
 * \brief Find decoded N value for raw NDEC value.
 */
static uint32_t __pll_n_decode (uint32_t ndec)
{
    uint32_t n, x, i;

    /* Find NDec */
    switch (ndec) {
    case 0xFFF:
        n = 0;
        break;

    case 0x302:
        n = 1;
        break;

    case 0x202:
        n = 2;
        break;

    default:
        x = 0x080;
        n = 0xFFFFFFFF;
        for (i = __PLL_N_MAX; ((i >= 3) && (n == 0xFFFFFFFF)); i--) {
            x = (((x ^ (x >> 2) ^ (x >> 3) ^ (x >> 4)) & 1) << 7) 
                                           | ((x >> 1) & 0x7F);
            if ((x & (__PLL_NDEC_VAL_M >> __PLL_NDEC_VAL_P)) == ndec) {
                
                /* Decoded value of NDEC */
                n = i;
            }
        }
        break;
    }
    
    return n;
}

/** 
 * \brief Find encoded PDEC value for raw P value, maximum P = __PLL_P_MAX.
 */
static uint32_t __pll_p_encode (uint32_t p)
{
    uint32_t x, i;

    /* Find PDec */
    switch (p) {
    case 0:
        x = 0xFF;
        break;

    case 1:
        x = 0x62;
        break;

    case 2:
        x = 0x42;
        break;

    default:
        x = 0x10;
        for (i = p; i <= __PLL_P_MAX; i++) {
            x = (((x ^ (x >> 2)) & 1) << 4) | ((x >> 1) & 0xF);
        }
        break;
    }

    return x & (__PLL_PDEC_VAL_M >> __PLL_PDEC_VAL_P);
}

/** 
 * \brief Find decoded P value for raw PDEC value.
 */
static uint32_t __pll_p_decode (uint32_t pdec)
{
    uint32_t p, x, i;

    /* Find PDec */
    switch (pdec) {
    case 0xFF:
        p = 0;
        break;

    case 0x62:
        p = 1;
        break;

    case 0x42:
        p = 2;
        break;

    default:
        x = 0x10;
        p = 0xFFFFFFFF;
        for (i = __PLL_P_MAX; ((i >= 3) && (p == 0xFFFFFFFF)); i--) {
            x = (((x ^ (x >> 2)) & 1) << 4) | ((x >> 1) & 0xF);
            if ((x & (__PLL_PDEC_VAL_M >> __PLL_PDEC_VAL_P)) == pdec) {
                
                /* Decoded value of PDEC */
                p = i;
            }
        }
        break;
    }

    return p;
}

/** 
 * \brief Find encoded MDEC value for raw M value, maximum M = __PLL_M_MAX.
 */
static uint32_t __pll_m_encode (uint32_t m)
{
    uint32_t i, x;

    /* Find MDec */
    switch (m) {
    case 0:
        x = 0xFFFFF;
        break;

    case 1:
        x = 0x18003;
        break;

    case 2:
        x = 0x10003;
        break;

    default:
        x = 0x04000;
        for (i = m; i <= __PLL_M_MAX; i++) {
            x = (((x ^ (x >> 1)) & 1) << 14) | ((x >> 1) & 0x3FFF);
        }
        break;
    }

    return x & (__PLL_SSCG0_MDEC_VAL_M >> __PLL_SSCG0_MDEC_VAL_P);
}

/** 
 * \brief Find decoded M value for raw MDEC value.
 */
static uint32_t __pll_decode_m (uint32_t mdec)
{
    uint32_t m, i, x;

    /* Find MDec */
    switch (mdec) {
    case 0xFFFFF:
        m = 0;
        break;

    case 0x18003:
        m = 1;
        break;

    case 0x10003:
        m = 2;
        break;

    default:
        x = 0x04000;
        m = 0xFFFFFFFF;
        for (i = __PLL_M_MAX; ((i >= 3) && (m == 0xFFFFFFFF)); i--) {
            x = (((x ^ (x >> 1)) & 1) << 14) | ((x >> 1) & 0x3FFF);
            if ((x & (__PLL_SSCG0_MDEC_VAL_M 
                   >> __PLL_SSCG0_MDEC_VAL_P)) == mdec) {
            
                /* Decoded value of MDEC */
                m = i;
            }
        }
        break;
    }

    return m;
}

/** 
 * \brief Find SELP, SELI, and SELR values for raw M value, maximum M = __PLL_M_MAX.
 */
static void __pll_sel_find (uint32_t  m, 
                            bool_t    bypass_fb_div2, 
                            uint32_t *p_sel_p, 
                            uint32_t *p_sel_i, 
                            uint32_t *p_sel_r)
{
    /* Bypass divider 2 */
    if (bypass_fb_div2 == TRUE) {
        m = m / 2;
    }

    /* Bandwidth: compute selP from Multiplier */
    if (m < 60) {
        *p_sel_p = (m >> 1) + 1;
    } else {
        *p_sel_p = __PLL_P_MAX - 1;
    }

    /* Bandwidth: compute selI from Multiplier */
    if (m > 16384) {
        *p_sel_i = 1;
    } else if (m > 8192) {
        *p_sel_i = 2;
    } else if (m > 2048) {
        *p_sel_i = 4;
    } else if (m >= 501) {
        *p_sel_i = 8;
    } else if (m >= 60) {
        *p_sel_i = 4 * (1024 / (m + 9));
    } else {
        *p_sel_i = (m & 0x3C) + 4;
    }

    if (*p_sel_i > (__PLL_SELI_M >> __PLL_SELI_P)) {
        *p_sel_i = (__PLL_SELI_M >> __PLL_SELI_P);
    }

    *p_sel_r = 0;
}

/** 
 * \brief Get predivider (N) from PLL NDEC setting.
 */
uint32_t __pll_prediv_find (uint32_t ctrl_reg, uint32_t ndec_reg)
{
    uint32_t prediv = 1;

    /* Direct input is not used? */
    if ((ctrl_reg & __PLL_DIRECTI) == 0) {
        
        /* Decode NDEC value to get (N) pre divider */
        prediv = __pll_n_decode(ndec_reg & 0x3FF);
        if (prediv == 0) {
            prediv = 1;
        }
    }

    /* Adjusted by 1, direct input is used to bypass */
    return prediv;
}

/** 
 * \brief Get postdivider (P) from PLL PDEC setting.
 */
uint32_t __pll_postdiv_find (uint32_t ctrl_reg, uint32_t pdec_reg)
{
    uint32_t postdiv = 1;

    /* Direct input is not used? */
    if ((ctrl_reg & __PLL_DIRECTO) == 0) {
        
        /* Decode PDEC value to get (P) post divider */
        postdiv = 2 * __pll_p_decode(pdec_reg & 0x7F);
        if (postdiv == 0) {
            postdiv = 2;
        }
    }

    /* Adjusted by 1, direct output is used to bypass */
    return postdiv;
}

/** 
 * \brief Get multiplier (M) from PLL MDEC and BYPASS_FBDIV2 settings.
 */
uint32_t __pll_mmult_find (uint32_t ctrl_reg, uint32_t mdec_reg)
{
    uint32_t mmult = 1;

    /* Decode MDEC value to get (M) multiplier */
    mmult = __pll_decode_m(mdec_reg & 0x1FFFF);

    /* Extra divided by 2 needed? */
    if ((ctrl_reg & __PLL_BYPASS_FBDIV2) == 0) {
        mmult = mmult >> 1;
    }

    if (mmult == 0) {
        mmult = 1;
    }

    return mmult;
}

/** 
 * \brief Get The Greatest common divisor.
 */
static uint32_t __pll_commondiv_find (uint32_t m, uint32_t n)
{
    uint32_t tmp;

    while (n != 0) {
        tmp = n;
        n = m % n;
        m = tmp;
    }

    return m;
}

/**
 * \brief Set PLL output based on desired output rate 
 */

static amhw_pll_stat_t __pll_getpllconfig (uint32_t          fin_hz,    
                                           uint32_t          fout_hz,  
                                           amhw_pll_setup_t *p_setup,    
                                           bool_t            use_fb_div2, 
                                           bool_t            use_ss)     
{
    uint32_t n_div_out_hz;        /* The freq of N-divider output               */
    uint32_t fcco_out_hz;         /* The freq of CCO output                     */  
    uint32_t mult_fcco_div;   
    uint32_t pre_div;             /* pre divider for pll input clock            */
    uint32_t post_div;            /* post divider for CCO output clock          */ 
    uint32_t direct_input;        /* The pre_div(N-divider) is bypassed or not  */
    uint32_t direct_output;       /* The post_div(P divider) is bypassed or not */
    uint32_t sel_r, sel_i, sel_p; /* Bandwidth select R,I,P value               */
    uint32_t multiplier;          /* The multiplier of The PLL                  */
    uint32_t bypass_fb_div2;      /* feedback clock divide by 2 bypassed or not */
    uint32_t bandsel;             /* PLL filter control                         */
    uint32_t uplimoff;            /* spread spectrum/fractional mode            */

    pre_div       = 1;      
    post_div      = 0;     
    direct_output = 1;
    
    if (use_fb_div2) {       /* Using feedback divider for M, so disable bypass */
        bypass_fb_div2 = 0;
        mult_fcco_div  = 2;
    } else {                 /* Not Using feedback divider for M,so enable bypass */     
        bypass_fb_div2 = 1;
        mult_fcco_div  = 1;
    }
    
    /* The maximum output freq is 150MHz */
    if (fout_hz > __PLL_MAX_CCO_FREQ_HZ) {     
        return AMHW_PLL_OUTPUT_TOO_HIGH;                
    }
    if (fout_hz < (__PLL_MIN_CCO_FREQ_HZ / (__PLL_P_MAX << 1))) {
        
        /* The minimum freq is 75 000000Hz / (32 * 2) = 1,171,875Hz  */
        return AMHW_PLL_OUTPUT_TOO_LOW;
    }
    
    if (use_ss == TRUE) {
        if (fin_hz < __PLL_MIN_IN_SSMODE) {
            return AMHW_PLL_INPUT_TOO_LOW;
        }

        pre_div = fin_hz / ((__PLL_MIN_IN_SSMODE + __PLL_MAX_IN_SSMODE) / 2);
        
        if (pre_div > __PLL_N_MAX) {
            return AMHW_PLL_INPUT_TOO_HIGH;
        }
    } else {                              
        if (fin_hz < __PLL_LOWER_IN_LIMIT) { 
            return AMHW_PLL_INPUT_TOO_LOW;
        }
    }

    /*     
     * Find the optimal CCO frequency for the output and input that
     * will keep it inside the PLL CCO range. This may require
     * tweaking the post-divider for the PLL. 
     */
    fcco_out_hz = fout_hz;
    
    while (fcco_out_hz < __PLL_MIN_CCO_FREQ_HZ) {
    
        /* 
         * CCO output is less than minimum CCO range, so the CCO output
         * needs to be bumped up and the post-divider is used to bring
         * the PLL output back down. 
         */
        post_div++;
        if (post_div > __PLL_P_MAX) {
            return AMHW_PLL_OUTSIDE_INTLIMIT;
        }

        /* 
         * Target CCO goes up, PLL output goes down 
         */
        fcco_out_hz   = fout_hz * (post_div * 2);
        direct_output = 0;                   /* direct output disable */
    }

    /* Determine if a pre-divider is needed to get the best frequency */
    if ((fin_hz  > __PLL_LOWER_IN_LIMIT) && 
        (fcco_out_hz >= fin_hz) && 
        (use_ss == FALSE)) {
            
        uint32_t common_div = __pll_commondiv_find(fcco_out_hz, 
                                                  (mult_fcco_div * fin_hz));

        if (common_div > 20000) {
            common_div = (mult_fcco_div * fin_hz) / common_div;
            
            if ((common_div != 0) && (common_div < __PLL_N_MAX)) {
                pre_div = common_div;
            }
        }
    }

    /* Bypass pre-divider hardware if pre-divider is 1 */
    if (pre_div > 1) {
        direct_input = 0;      /* disable direct input */
    } else {
        direct_input = 1;
    }

    /* Determine PLL multiplexing */
    n_div_out_hz = (fin_hz / pre_div);
    multiplier   = (fcco_out_hz / n_div_out_hz) / mult_fcco_div;

    /* Find optimal values for filter */
    if (use_ss == FALSE) {
    
        /* Will bumping up M by 1 get us closer to the desired CCO frequency? */
        if ((n_div_out_hz * ((mult_fcco_div * multiplier * 2) + 1)) 
                                               < (fcco_out_hz * 2)) {
            multiplier++;
        }

        /* Set up filtering */
        __pll_sel_find(multiplier, 
                      (bool_t)bypass_fb_div2, 
                      &sel_p, 
                      &sel_i, 
                      &sel_r);
        bandsel  = 1;
        uplimoff = 0;

        /* 
         * Get encoded value for M (multiplexing) and use manual filter, 
         * disable SS mode 
         */
        p_setup->pllssctrl[0] = 
                 (__PLL_SSCG0_MDEC_VAL_SET(__pll_m_encode(multiplier)) |
                 (1 << __PLL_SSCG0_SEL_EXT_SSCG_N_P));

        /* Power down SSC, not used */
        p_setup->pllssctrl[1] = __PLL_SSCG1_MOD_PD_SSCGCLK_N;
    } else {
        uint64_t fc;

        /* Filtering will be handled by SSC */
        sel_r    = sel_i = sel_p = 0;
        bandsel  = 0;
        uplimoff = 1;

        /* 
         * The PLL multiplier will get very close and slightly under the
         * desired target frequency. A small fractional component can be
         * added to fine tune the frequency upwards to the target.
         */
        fc = ((uint64_t)(fcco_out_hz % (mult_fcco_div * n_div_out_hz)) << 11) / 
                        (mult_fcco_div * n_div_out_hz);

        /* MDEC set by SSC */
        p_setup->pllssctrl[0] = 0;

        /* Set multiplier */
        p_setup->pllssctrl[1] = __PLL_SSCG1_MD_INT_SET(multiplier) |
                                __PLL_SSCG1_MD_FRACT_SET((uint32_t)fc);
    }

    /* Get encoded values for N (prediv) and P (postdiv) */
    p_setup->pllndec = __PLL_NDEC_VAL_SET(__pll_n_encode(pre_div));
    p_setup->pllpdec = __PLL_PDEC_VAL_SET(__pll_p_encode(post_div));

    /* PLL control */
    p_setup->pllctrl = (sel_r << __PLL_SELR_P)    |  /* Filter coefficient          */                    
                       (sel_i << __PLL_SELI_P)    |  /* Filter coefficient          */
                       (sel_p << __PLL_SELP_P)    |  /* Filter coefficient          */
                       ( 0    << __PLL_BYPASS_P)  |  /* PLL bypass mode disabled    */
    (bypass_fb_div2 << __PLL_BYPASS_FBDIV2_P)     |  /* Extra M / 2 divider         */
          (uplimoff << __PLL_UPLIMOFF_P)          |  /* SS/fractional mode disabled */
           (bandsel << __PLL_BANDSEL_SSCGREG_N_P) |  /* bandwidth selection enabled */
     (direct_input  << __PLL_DIRECTI_P)           |  /* Bypass pre-divider          */
     (direct_output << __PLL_DIRECTO_P);             /* Bypass post-divider         */

    return AMHW_PLL_SUCCESS;
}


/*******************************************************************************
* Public function
*******************************************************************************/

/** 
 * \brief Return System PLL input clock rate.
 */
uint32_t amhw_pll_in_clkrate_get (void)
{
    uint32_t clkrate = 0;

    switch ((amhw_pll_clksrc_t)(AMHW_SYSCON->syspllclksel & 0x3)) {
    case AMHW_PLL_CLKSRC_IRC:
        clkrate = amhw_clock_irc_rate_get(); 
        break;

    case AMHW_PLL_CLKSRC_CLKIN:
        clkrate = amhw_clock_clkin_rate_get();
        break;

    case AMHW_PLL_CLKSRC_WDTOSC:
        clkrate = amhw_clock_wdt_rate_get();
        break;

    case AMHW_PLL_CLKSRC_RTC:
        clkrate = amhw_clock_rtc_rate_get();
        break;
    
    default:
        break;
    }

    return clkrate;
}

/** 
 * \brief Return System PLL output clock rate from set up structure.
 */
uint32_t amhw_pll_out_clkrate_fromsetup (amhw_pll_setup_t *p_setup)
{
    uint32_t prediv, postdiv, m_mult, pll_inrate;
    uint64_t workRate;

    pll_inrate = amhw_pll_in_clkrate_get();
    
    if ((p_setup->pllctrl & __PLL_BYPASS_P) == 0) {
        
        /* 
         * PLL is not in bypass mode, get pre-divider, post-divider, 
         * and M divider.
         */
        prediv  = __pll_prediv_find(p_setup->pllctrl, p_setup->pllndec);
        postdiv = __pll_postdiv_find(p_setup->pllctrl, p_setup->pllpdec);

        /* Adjust input clock */
        pll_inrate = pll_inrate / prediv;

        /* If using the SS, use the multiplier */
        if (p_setup->pllssctrl[1] & __PLL_SSCG1_MOD_PD_SSCGCLK_N) {
            
            /* MDEC used for rate */
            m_mult   = __pll_mmult_find(p_setup->pllctrl,
                                        p_setup->pllssctrl[0]);
            workRate = (uint64_t)pll_inrate * (uint64_t)m_mult;
        } else {
            uint64_t fract;

            /* SS multipler used for rate */
            m_mult = (p_setup->pllssctrl[1] 
                    & __PLL_SSCG1_MD_INT_M) 
                   >> __PLL_SSCG1_MD_INT_P;
            workRate = (uint64_t)pll_inrate * (uint64_t)m_mult;

            /* Adjust by fractional */
            fract = (uint64_t)(p_setup->pllssctrl[1] 
                             & __PLL_SSCG1_MD_FRACT_M) 
                             >> __PLL_SSCG1_MD_FRACT_P;
            workRate = workRate + ((pll_inrate * fract) / 0x7FF);
        }

        workRate = workRate / ((uint64_t)postdiv);
    } else {
        
        /* In bypass mode */
        workRate = (uint64_t)pll_inrate;
    }

    return (uint32_t)workRate;
}

/** 
 * \brief Return System PLL output clock rate.
 */
uint32_t amhw_pll_out_clkrate_get (void)
{
    amhw_pll_setup_t setup;
 
    setup.pllctrl = AMHW_SYSCON->syspllctrl;
    setup.pllndec = AMHW_SYSCON->syspllndec;
    setup.pllpdec = AMHW_SYSCON->syspllpdec;
    
    setup.pllssctrl[0] = AMHW_SYSCON->syspllssctrl0;
    setup.pllssctrl[1] = AMHW_SYSCON->syspllssctrl1;

    return amhw_pll_out_clkrate_fromsetup(&setup);
}

/** 
 * \brief Set PLL output based on the passed PLL set up data.
 */
amhw_pll_stat_t amhw_pll_setup_plldata (amhw_pll_config_t *p_config, 
                                        amhw_pll_setup_t  *p_setup)
{
    uint32_t inrate;
    
    bool_t use_ss = (bool_t)((p_config->flags & 
                              AMHW_PLL_CONFIG_FLAG_FORCENOFRACT) == 0);
    
    amhw_pll_stat_t pllstat;

    if ((p_config->flags & AMHW_PLL_CONFIG_FLAG_USEINRATE) != 0) {     
        inrate = p_config->input_rate;
    } else {
        inrate = amhw_pll_in_clkrate_get();                          
    }

    /* PLL flag options */
    pllstat = __pll_getpllconfig(inrate, 
                                 p_config->desired_rate, 
                                 p_setup,
                                 FALSE, 
                                 use_ss);
    
    if ((use_ss) && (pllstat == AMHW_PLL_SUCCESS)) {
        
        /* If using SS mode, then some tweaks are made to the generated set up */
        p_setup->pllssctrl[1] |= (uint32_t)p_config->ss_mf | 
                                 (uint32_t)p_config->ss_mr |
                                 (uint32_t)p_config->ss_mc;
        
        if (p_config->mf_dither) {
            p_setup->pllssctrl[1] |= __PLL_SSCG1_DITHER;
        }
    }

    return pllstat;
}

/** 
 * \brief Enables and disables PLL bypass mode.
 */
void amhw_pll_bypass_set (bool_t bypass)
{
    if (bypass) {
        AMHW_SYSCON->syspllctrl |=  __PLL_BYPASS_P;
    } else {
        AMHW_SYSCON->syspllctrl &= ~__PLL_BYPASS_P;
    }
}
 
/** 
 * \brief Set PLL output from PLL setup structure.
 */
amhw_pll_stat_t amhw_pll_setup_prec (amhw_pll_setup_t *p_setup)
{
    /* Power off PLL during setup changes */
    amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);

    /* Write PLL setup data */
    AMHW_SYSCON->syspllctrl    = p_setup->pllctrl;
    AMHW_SYSCON->syspllndec    = p_setup->pllndec;
    AMHW_SYSCON->syspllndec    = p_setup->pllndec  | __PLL_NDEC_NREQ;             
    AMHW_SYSCON->syspllpdec    = p_setup->pllpdec;
    AMHW_SYSCON->syspllpdec    = p_setup->pllpdec  | __PLL_PDEC_PREQ;               
    
    AMHW_SYSCON->syspllssctrl0 = p_setup->pllssctrl[0];
    AMHW_SYSCON->syspllssctrl0 = p_setup->pllssctrl[0] | __PLL_SSCG0_MREQ;      
    AMHW_SYSCON->syspllssctrl1 = p_setup->pllssctrl[1];
    AMHW_SYSCON->syspllssctrl1 = p_setup->pllssctrl[1] | __PLL_SSCG1_MD_REQ;     

    /* Flags for lock or power on */
    if (((p_setup->flags & (AMHW_PLL_SETUP_FLAG_POWERUP )) != 0) ||
        ((p_setup->flags & (AMHW_PLL_SETUP_FLAG_WAITLOCK)) != 0)) {
        amhw_syscon_powerup(AMHW_SYSCON_PD_SYS_PLL);
    }
       
    if ((p_setup->flags & AMHW_PLL_SETUP_FLAG_WAITLOCK) != 0) {
        while (amhw_pll_locked_chk() == FALSE) {}
    }

    /* System voltage adjustment, occurs prior to setting main system clock */
    if ((p_setup->flags & AMHW_PLL_SETUPFLAG_ADGVOLT) != 0) {
        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, 
                               amhw_pll_out_clkrate_fromsetup(p_setup));      
    }
    
    return AMHW_PLL_SUCCESS;
}

/** 
 * \brief Set System PLL clock based on the input frequency and multiplier.
 */
void amhw_pll_setup_multiby (uint32_t multiply_by, uint32_t input_freq)
{
    uint32_t cco_freq = input_freq * multiply_by;
    uint32_t pdec     = 1;
    uint32_t selr;
    uint32_t seli;
    uint32_t selp;
    uint32_t mdec, ndec;

    uint32_t directo = __PLL_DIRECTO;

    while (cco_freq < 75000000) {
        
        /* double value in each iteration */
        multiply_by <<= 1;

        /* correspondingly double pdec to cancel effect of double msel */
        pdec <<= 1;    
        
        cco_freq = input_freq * multiply_by;
    }
    
    selr = 0;
    seli = (multiply_by & 0x3c) + 4;
    selp = (multiply_by >> 1) + 1;

    if (pdec > 1) {
        directo = 0;           /* use post divider             */
        pdec    = pdec / 2;    /* Account for minus 1 encoding */
        
        /* Translate P value */
        pdec = (pdec == 1)  ? 0x62 :          /* 1  * 2 */
               (pdec == 2)  ? 0x42 :          /* 2  * 2 */
               (pdec == 4)  ? 0x02 :          /* 4  * 2 */
               (pdec == 8)  ? 0x0b :          /* 8  * 2 */
               (pdec == 16) ? 0x11 :          /* 16 * 2 */
               (pdec == 32) ? 0x08 : 0x08;    /* 32 * 2 */
    }

    /* Only support values of 2 to 16 (to keep driver simple) */
    mdec = 0x7fff >> (16 - (multiply_by - 1));
    
    /* pre divide by 2 (hardcoded) */
    ndec = 0x202;                  

    AMHW_SYSCON->syspllctrl =  __PLL_BANDSEL_SSCGREG_N | 
                               directo                 | 
                               (selr << __PLL_SELR_P)  |
                               (seli << __PLL_SELI_P)  | 
                               (selp << __PLL_SELP_P);
    
    /* set Pdec value and assert preq */
    AMHW_SYSCON->syspllpdec    = pdec | (1 << 7);       
    
    /* set Pdec value and assert preq */
    AMHW_SYSCON->syspllndec    = ndec | (1 << 10);    
    
    /* select non sscg MDEC value, assert mreq and select mdec value */
    AMHW_SYSCON->syspllssctrl0 = (1 << 18) | (1 << 17) | mdec;    
}

/** 
 * \brief Configure the PLL for common use.
 */
amhw_pll_stat_t amhw_pll_config (amhw_pll_clksrc_t clksrc, 
                                 uint32_t          desiredrate, 
                                 bool_t            usepllprecise)
{
    amhw_pll_config_t pll_config;
    amhw_pll_setup_t  pll_setup;
    amhw_pll_stat_t   pll_stat;
    volatile uint32_t j;
       
    /* Before configure the PLL, power down the PLL */
    amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
    
    if (clksrc == AMHW_PLL_CLKSRC_RTC) {
        
        /* 
         * Turn on the RTC 32K Oscillator if it needs to be used as a source
         * for the PLL. 
         */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
    } else if (clksrc == AMHW_PLL_CLKSRC_WDTOSC) {
        
        /* Enable the power to the WDT Oscillator */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
    } 
    
    amhw_pll_clksrc_set(clksrc);   
    
    if ((clksrc == AMHW_PLL_CLKSRC_RTC) || (clksrc == AMHW_PLL_CLKSRC_WDTOSC)) {
    
        /*
         * When switching clock sources for the PLL, both the current and 
         * new source must be enabled and requires a small sync time. 
         */
        for (j = 0; j < 0x10000; j++) {}
    }
    
    pll_config.desired_rate = desiredrate;    
    pll_config.input_rate   = 0;             /* Automatic get the freq */ 
   
    if (usepllprecise == TRUE) {
        pll_config.flags     = 0;       
                             
        pll_config.ss_mf     = AMHW_PLL_SS_MF_64;
        pll_config.ss_mr     = AMHW_PLL_SS_MR_K3;
        pll_config.ss_mc     = AMHW_PLL_SS_MC_RECC;
        pll_config.mf_dither = FALSE;
    
    } else {
        pll_config.flags  = AMHW_PLL_CONFIG_FLAG_FORCENOFRACT;
    }
    
    /* Filling PLL setup data according to the configure structure data */
    pll_stat = amhw_pll_setup_plldata(&pll_config, &pll_setup);
    
    if (pll_stat != AMHW_PLL_SUCCESS) {
        return pll_stat;                /* PLL setup data failed     */
    } 
    
    if ((clksrc == AMHW_PLL_CLKSRC_RTC) || (clksrc == AMHW_PLL_CLKSRC_WDTOSC)) {
        
        /* 
         * Disable PLL wait lock flag when using RTC or WDTOSC, since
         * it will never lock 
         */
        pll_setup.flags = AMHW_PLL_SETUP_FLAG_POWERUP | AMHW_PLL_SETUPFLAG_ADGVOLT;
    } else {
         if (usepllprecise == TRUE) {  
             
             /* Don't wait for PLL lock when using SS, it might not lock */
             pll_setup.flags = AMHW_PLL_SETUP_FLAG_POWERUP 
                             | AMHW_PLL_SETUPFLAG_ADGVOLT;
         } else { 
             pll_setup.flags = AMHW_PLL_SETUP_FLAG_POWERUP  | 
                               AMHW_PLL_SETUP_FLAG_WAITLOCK | 
                               AMHW_PLL_SETUPFLAG_ADGVOLT;
         }
    }
    
    pll_stat = amhw_pll_setup_prec(&pll_setup);        /* PLL setup data failed */
    
    if (pll_stat != AMHW_PLL_SUCCESS) {
        return pll_stat;
    }

    /* Setup FLASH access speed */
    amhw_syscon_setupflashclocks(desiredrate);

    if (usepllprecise == TRUE) {
        
        /* 
         * Since PLL lock may not happen when using SS mode, force a small
         * delay here to let it stabilize. 
         */
        for (j = 0; j < 0x8000; j++) {}
    } else {
        if ((clksrc == AMHW_PLL_CLKSRC_RTC) || 
            (clksrc == AMHW_PLL_CLKSRC_WDTOSC)) {
            
            /* Small delay for PLL lock when using RTC or WDTOSC */
            for (j = 0; j < 0x8000; j++) {}
        }        
    }
    
    return AMHW_PLL_SUCCESS;
}

/** 
 * \brief Set System PLL clock based on the input frequency and multiplier.
 */
void Chip_Clock_SetupSystemPLL (uint32_t multiply_by, uint32_t input_freq)
{
    uint32_t cco_freq = input_freq * multiply_by;
    uint32_t pdec     = 1;
    uint32_t selr;
    uint32_t seli;
    uint32_t selp;
    uint32_t mdec, ndec;

    uint32_t directo = __PLL_DIRECTO;

    while (cco_freq < 75000000) {
        
        /* double value in each iteration */
        multiply_by <<= 1;

        /* correspondingly double pdec to cancel effect of double msel */
        pdec <<= 1;    
        
        cco_freq = input_freq * multiply_by;
    }
    
    selr = 0;
    seli = (multiply_by & 0x3c) + 4;
    selp = (multiply_by >> 1) + 1;

    if (pdec > 1) {
        directo = 0;        /* use post divider             */
        pdec = pdec / 2;    /* Account for minus 1 encoding */
        
        /* Translate P value */
        pdec = (pdec == 1)  ? 0x62 :          /* 1  * 2 */
               (pdec == 2)  ? 0x42 :          /* 2  * 2 */
               (pdec == 4)  ? 0x02 :          /* 4  * 2 */
               (pdec == 8)  ? 0x0b :          /* 8  * 2 */
               (pdec == 16) ? 0x11 :          /* 16 * 2 */
               (pdec == 32) ? 0x08 : 0x08;    /* 32 * 2 */
    }

    /* Only support values of 2 to 16 (to keep driver simple) */
    mdec = 0x7fff >> (16 - (multiply_by - 1));
    
    /* pre divide by 2 (hardcoded) */
    ndec = 0x202;                  

    AMHW_SYSCON->syspllctrl =  __PLL_BANDSEL_SSCGREG_N | 
                               directo                 | 
                               (selr << __PLL_SELR_P)  |
                               (seli << __PLL_SELI_P)  | 
                               (selp << __PLL_SELP_P);
    
    /* set Pdec value and assert preq */
    AMHW_SYSCON->syspllpdec    = pdec | (1 << 7);       
    
    /* set Pdec value and assert preq */
    AMHW_SYSCON->syspllndec    = ndec | (1 << 10);    
    
    /* select non sscg MDEC value, assert mreq and select mdec value */
    AMHW_SYSCON->syspllssctrl0 = (1 << 18) | (1 << 17) | mdec;    
}

/* end of file */
