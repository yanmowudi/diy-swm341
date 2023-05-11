/**
 * @file dev_rgb.c
 * @author lik
 * @brief rgb相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"

/** rgb显示缓冲区 */
uint16_t *LCD_Buffer = (uint16_t *)SDRAMM_BASE;

/**
 * @brief rgb初始化
 * 
 */
void rgb_init(void)
{
    LCD_InitStructure LCD_initStruct;
    /** 复位LCD模块 */
    GPIO_Init(GPIOD, PIN1, 1, 0, 0, 0);
    GPIO_ClrBit(GPIOD, PIN1);
    swm_delay_ms(1);
    GPIO_SetBit(GPIOD, PIN1);
    /** 点亮背光 */
    GPIO_Init(GPIOB, PIN13, 1, 0, 0, 0);
    GPIO_SetBit(GPIOB, PIN13);

    PORT_Init(PORTB, PIN15, PORTB_PIN15_LCD_B3, 0);
    PORT_Init(PORTA, PIN2, PORTA_PIN2_LCD_B4, 0);
    PORT_Init(PORTA, PIN9, PORTA_PIN9_LCD_B5, 0);
    PORT_Init(PORTA, PIN10, PORTA_PIN10_LCD_B6, 0);
    PORT_Init(PORTA, PIN11, PORTA_PIN11_LCD_B7, 0);

    PORT_Init(PORTA, PIN14, PORTA_PIN14_LCD_G2, 0);
    PORT_Init(PORTA, PIN15, PORTA_PIN15_LCD_G3, 0);
    PORT_Init(PORTC, PIN0, PORTC_PIN0_LCD_G4, 0);
    PORT_Init(PORTC, PIN1, PORTC_PIN1_LCD_G5, 0);
    PORT_Init(PORTC, PIN2, PORTC_PIN2_LCD_G6, 0);
    PORT_Init(PORTC, PIN3, PORTC_PIN3_LCD_G7, 0);

    PORT_Init(PORTC, PIN9, PORTC_PIN9_LCD_R3, 0);
    PORT_Init(PORTC, PIN10, PORTC_PIN10_LCD_R4, 0);
    PORT_Init(PORTC, PIN11, PORTC_PIN11_LCD_R5, 0);
    PORT_Init(PORTC, PIN12, PORTC_PIN12_LCD_R6, 0);
    PORT_Init(PORTC, PIN13, PORTC_PIN13_LCD_R7, 0);

    PORT_Init(PORTB, PIN2, PORTB_PIN2_LCD_VSYNC, 0);
//    PORT_Init(PORTM, PIN8, PORTM_PIN8_LCD_HSYNC, 0);
//    PORT_Init(PORTM, PIN11, PORTM_PIN11_LCD_DEN, 0);
    PORT_Init(PORTB, PIN3, PORTB_PIN3_LCD_HSYNC, 0);
    PORT_Init(PORTB, PIN4, PORTB_PIN4_LCD_DEN, 0);
    PORT_Init(PORTB, PIN5, PORTB_PIN5_LCD_DCLK, 0);

    /** 480*272 */
//    LCD_initStruct.ClkDiv = 15;
//    LCD_initStruct.Format = LCD_FMT_RGB565;
//    LCD_initStruct.HnPixel = 480;
//    LCD_initStruct.VnPixel = 272;
//    LCD_initStruct.Hfp = 5;
//    LCD_initStruct.Hbp = 40;
//    LCD_initStruct.Vfp = 8;
//    LCD_initStruct.Vbp = 8;
//    LCD_initStruct.HsyncWidth = 5;
//    LCD_initStruct.VsyncWidth = 5;
    /** 800*480 */
    LCD_initStruct.ClkDiv = 5;
    LCD_initStruct.Format = LCD_FMT_RGB565;
    LCD_initStruct.HnPixel = 800;
    LCD_initStruct.VnPixel = 480;
    LCD_initStruct.Hfp = 64;
    LCD_initStruct.Hbp = 46;
    LCD_initStruct.Vfp = 22;
    LCD_initStruct.Vbp = 23;
    LCD_initStruct.HsyncWidth = 5;
    LCD_initStruct.VsyncWidth = 5;
    /** 1024*600 */
    // LCD_initStruct.ClkDiv = 3;
    // LCD_initStruct.Format = LCD_FMT_RGB565;
    // LCD_initStruct.HnPixel = 1024;
    // LCD_initStruct.VnPixel = 600;
    // LCD_initStruct.Hfp = 64;
    // LCD_initStruct.Hbp = 140;
    // LCD_initStruct.Vfp = 12;
    // LCD_initStruct.Vbp = 12;
    // LCD_initStruct.HsyncWidth = 20;
    // LCD_initStruct.VsyncWidth = 3;

    LCD_initStruct.DataSource = (uint32_t)LCD_Buffer;
    LCD_initStruct.Background = 0xFFFFFF;
    LCD_initStruct.SampleEdge = LCD_SAMPLE_FALL;
    LCD_initStruct.IntEOTEn = 0;
    LCD_Init(LCD, &LCD_initStruct);
}
