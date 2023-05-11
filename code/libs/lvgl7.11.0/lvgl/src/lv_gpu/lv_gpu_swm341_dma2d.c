/**
 * @file lv_gpu_swm341_dma2d.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_gpu_swm341_dma2d.h"
#include "../lv_core/lv_disp.h"
#include "../lv_core/lv_refr.h"

#if LV_USE_GPU_SWM341_DMA2D

#include LV_GPU_SWM341_DMA2D_INCLUDE

/*********************
 *      DEFINES
 *********************/

#if LV_COLOR_16_SWAP
    #error "Can't use DMA2D with LV_COLOR_16_SWAP 1"
#endif

#if LV_COLOR_DEPTH == 8
    #error "Can't use DMA2D with LV_COLOR_DEPTH == 8"
#endif

#if LV_COLOR_DEPTH == 16
    #define LV_DMA2D_COLOR_FORMAT LV_DMA2D_RGB565
#elif LV_COLOR_DEPTH == 32
    #define LV_DMA2D_COLOR_FORMAT LV_DMA2D_ARGB8888
#else
    /*Can't use GPU with other formats*/
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void invalidate_cache(void);
static void wait_finish(void);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Turn on the peripheral and set output color mode, this only needs to be done once
 */
void lv_gpu_swm341_dma2d_init(void)
{
    /*Enable DMA2D clock*/
    SYS->CLKEN0 |= (1 << SYS_CLKEN0_DMA2D_Pos);

    DMA2D->CR &= ~DMA2D_CR_WAIT_Msk;
    DMA2D->CR |= (CyclesPerUs << DMA2D_CR_WAIT_Pos);

    DMA2D->IF = 0xFF;
    DMA2D->IE = (0 << DMA2D_IE_DONE_Pos);

    /*set output colour mode*/
    DMA2D->L[DMA2D_LAYER_OUT].PFCCR = (LV_DMA2D_COLOR_FORMAT << DMA2D_PFCCR_CFMT_Pos);
}

/**
 * Fill an area in the buffer with a color
 * @param buf a buffer which should be filled
 * @param buf_w width of the buffer in pixels
 * @param color fill color
 * @param fill_w width to fill in pixels (<= buf_w)
 * @param fill_h height to fill in pixels
 * @note `buf_w - fill_w` is offset to the next line after fill
 */
void lv_gpu_swm341_dma2d_fill(lv_color_t * buf, lv_coord_t buf_w, lv_color_t color, lv_coord_t fill_w, lv_coord_t fill_h)
{
#if 1
    DMA2D->L[DMA2D_LAYER_OUT].COLOR = color.full;

    DMA2D->L[DMA2D_LAYER_OUT].MAR = (uint32_t)buf;
    DMA2D->L[DMA2D_LAYER_OUT].OR = buf_w - fill_w;
    DMA2D->NLR = ((fill_w - 1) << DMA2D_NLR_NPIXEL_Pos) | ((fill_h - 1) << DMA2D_NLR_NLINE_Pos);

    /*start transfer*/
    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (3 << DMA2D_CR_MODE_Pos) |
                 (1 << DMA2D_CR_START_Pos);
    wait_finish();
#else
    for (uint32_t y = 0; y < fill_h; y++)
    {
        for (uint32_t x = 0; x < fill_w; x++)
        {
            buf[y * buf_w + x] = color;
        }
    }
#endif
}

/**
 * Fill an area in the buffer with a color but take into account a mask which describes the opacity of each pixel
 * @param buf a buffer which should be filled using a mask
 * @param buf_w width of the buffer in pixels
 * @param color fill color
 * @param mask 0..255 values describing the opacity of the corresponding pixel. It's width is `fill_w`
 * @param opa overall opacity. 255 in `mask` should mean this opacity.
 * @param fill_w width to fill in pixels (<= buf_w)
 * @param fill_h height to fill in pixels
 * @note `buf_w - fill_w` is offset to the next line after fill
 */
void lv_gpu_swm341_dma2d_fill_mask(lv_color_t * buf, lv_coord_t buf_w, lv_color_t color, const lv_opa_t * mask,
                                  lv_opa_t opa, lv_coord_t fill_w, lv_coord_t fill_h)
{
#if 0

#endif
}

/**
 * Copy a map (typically RGB image) to a buffer
 * @param buf a buffer where map should be copied
 * @param buf_w width of the buffer in pixels
 * @param map an "image" to copy
 * @param map_w width of the map in pixels
 * @param copy_w width of the area to copy in pixels (<= buf_w)
 * @param copy_h height of the area to copy in pixels
 * @note `map_w - fill_w` is offset to the next line after copy
 */
void lv_gpu_swm341_dma2d_copy(lv_color_t * buf, lv_coord_t buf_w, const lv_color_t * map, lv_coord_t map_w,
                             lv_coord_t copy_w, lv_coord_t copy_h)
{
#if 1
        /*copy output colour mode, this register controls both input and output colour format*/
        DMA2D->L[DMA2D_LAYER_FG].MAR = (uint32_t)map;
        DMA2D->L[DMA2D_LAYER_FG].OR = map_w - copy_w;
        DMA2D->L[DMA2D_LAYER_FG].PFCCR = (LV_DMA2D_COLOR_FORMAT << DMA2D_PFCCR_CFMT_Pos);

        DMA2D->L[DMA2D_LAYER_OUT].MAR = (uint32_t)buf;
        DMA2D->L[DMA2D_LAYER_OUT].OR = buf_w - copy_w;

        DMA2D->NLR = ((copy_w - 1) << DMA2D_NLR_NPIXEL_Pos) | ((copy_h - 1) << DMA2D_NLR_NLINE_Pos);

        /*start transfer*/
        DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
        DMA2D->CR |= (0 << DMA2D_CR_MODE_Pos) |
                     (1 << DMA2D_CR_START_Pos);
        wait_finish();
#else
        lv_color_t temp_buf[1024];
        for (uint32_t y = 0; y < copy_h; y++)
        {
            memcpy(temp_buf, &map[y * map_w], copy_w * sizeof(lv_color_t));
            memcpy(&buf[y * buf_w], temp_buf, copy_w * sizeof(lv_color_t));
        }
#endif
}

/**
 * Blend a map (e.g. ARGB image or RGB image with opacity) to a buffer
 * @param buf a buffer where `map` should be copied
 * @param buf_w width of the buffer in pixels
 * @param map an "image" to copy
 * @param opa opacity of `map`
 * @param map_w width of the map in pixels
 * @param copy_w width of the area to copy in pixels (<= buf_w)
 * @param copy_h height of the area to copy in pixels
 * @note `map_w - fill_w` is offset to the next line after copy
 */
void lv_gpu_swm341_dma2d_blend(lv_color_t * buf, lv_coord_t buf_w, const lv_color_t * map, lv_opa_t opa,
                              lv_coord_t map_w, lv_coord_t copy_w, lv_coord_t copy_h)
{
    DMA2D->L[DMA2D_LAYER_FG].MAR = (uint32_t)map;
    DMA2D->L[DMA2D_LAYER_FG].OR = map_w - copy_w;
    DMA2D->L[DMA2D_LAYER_FG].PFCCR = (LV_DMA2D_COLOR_FORMAT << DMA2D_PFCCR_CFMT_Pos)
                                        /*alpha mode 2, replace with foreground * alpha value*/
                                        | (2 << DMA2D_PFCCR_AMODE_Pos)
                                        /*alpha value*/
                                        | (opa << DMA2D_PFCCR_ALPHA_Pos);

    DMA2D->L[DMA2D_LAYER_BG].MAR = (uint32_t)buf;
    DMA2D->L[DMA2D_LAYER_BG].OR = buf_w - copy_w;
    DMA2D->L[DMA2D_LAYER_BG].PFCCR = (LV_DMA2D_COLOR_FORMAT << DMA2D_PFCCR_CFMT_Pos);

    DMA2D->L[DMA2D_LAYER_OUT].MAR = (uint32_t)buf;
    DMA2D->L[DMA2D_LAYER_OUT].OR = buf_w - copy_w;

    DMA2D->NLR = ((copy_w - 1) << DMA2D_NLR_NPIXEL_Pos) | ((copy_h - 1) << DMA2D_NLR_NLINE_Pos);

    /*start transfer*/
    DMA2D->CR &= ~DMA2D_CR_MODE_Msk;
    DMA2D->CR |= (2 << DMA2D_CR_MODE_Pos) |
                    (1 << DMA2D_CR_START_Pos);
    wait_finish();
}

void lv_gpu_swm341_dma2d_wait_cb(lv_disp_drv_t * drv)
{
    if(drv && drv->wait_cb) {
        while(DMA2D->CR & DMA2D_CR_START_Msk) {
            drv->wait_cb(drv);
        }
    }
    else {
        while(DMA2D->CR & DMA2D_CR_START_Msk);
    }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void wait_finish(void)
{
    lv_disp_t * disp = _lv_refr_get_disp_refreshing();
    if(disp->driver.gpu_wait_cb) return;

    while(DMA2D->CR & DMA2D_CR_START_Msk) {
        if(disp->driver.wait_cb) disp->driver.wait_cb(&disp->driver);
    }
}

#endif
