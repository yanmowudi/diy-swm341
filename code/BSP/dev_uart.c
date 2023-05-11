/**
 * @file dev_uart.c
 * @author lik
 * @brief uart相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SWM341.h"

/**
 * @brief uart初始化
 * 
 */
void uart_init(void)
{
    UART_InitStructure UART_initStruct;

    PORT_Init(PORTM, PIN0, PORTM_PIN0_UART0_RX, 1); //GPIOM.0配置为UART0输入引脚
    PORT_Init(PORTM, PIN1, PORTM_PIN1_UART0_TX, 0); //GPIOM.1配置为UART0输出引脚

    UART_initStruct.Baudrate = 115200;
    UART_initStruct.DataBits = UART_DATA_8BIT;
    UART_initStruct.Parity = UART_PARITY_NONE;
    UART_initStruct.StopBits = UART_STOP_1BIT;
    UART_initStruct.RXThreshold = 3;
    UART_initStruct.RXThresholdIEn = 0;
    UART_initStruct.TXThreshold = 3;
    UART_initStruct.TXThresholdIEn = 0;
    UART_initStruct.TimeoutTime = 10;
    UART_initStruct.TimeoutIEn = 0;
    UART_Init(UART0, &UART_initStruct);
    UART_Open(UART0);
}

#if defined ( __GNUC__ ) && !defined (__clang__) 
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
/**
 * @brief 不使用MicroLIB时避免使用半主机模式
 * 
 */
__asm (".global __use_no_semihosting\n\t");
void _sys_exit(int x)
{
  x = x;
}
/* __use_no_semihosting was requested, but _ttywrch was */
void _ttywrch(int ch)
{
    ch = ch;
}
//struct __FILE
//{
//  int handle;
//};
FILE __stdout;

#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
    UART_WriteByte(UART0, ch);

    while (UART_IsTXBusy(UART0))
        ;

    return ch;
}
