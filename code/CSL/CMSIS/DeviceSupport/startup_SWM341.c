#include "main.h"

/*----------------------------------------------------------------------------
  External References
 *----------------------------------------------------------------------------*/
extern uint32_t __INITIAL_SP;
extern uint32_t __STACK_LIMIT;

extern __NO_RETURN void __PROGRAM_START(void);

/*----------------------------------------------------------------------------
  Internal References
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void);
void Default_Handler(void);

/*----------------------------------------------------------------------------
  Exception / Interrupt Handler
 *----------------------------------------------------------------------------*/
/* Exceptions */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SecureFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void UART0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIMR0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIMR1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void WDT_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HALL0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWMBRK_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIMR2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UART3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIMR3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BOD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CORDIC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PWM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HALL3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void I2C1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void ACMP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void XTALSTOP_Handler(void) __attribute__((weak, alias("Default_Handler")));
void FSPI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOB_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPION_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA12_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA13_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOB0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOB1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOB2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOD8_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOC12_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM0_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM2_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM3_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOM4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DIV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void LCD_Handler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOE_Handler(void) __attribute__((weak, alias("Default_Handler")));
void JPEG_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_Handler(void) __attribute__((weak, alias("Default_Handler")));
void USB_Handler(void) __attribute__((weak, alias("Default_Handler")));
void CAN1_Handler(void) __attribute__((weak, alias("Default_Handler")));
void TIMR4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR4_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR5_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR6_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR7_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR8_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR9_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR10_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BTIMR11_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DMA2D_Handler(void) __attribute__((weak, alias("Default_Handler")));
void QEI_Handler(void) __attribute__((weak, alias("Default_Handler")));

/*----------------------------------------------------------------------------
  Exception / Interrupt Vector table
 *----------------------------------------------------------------------------*/

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

extern const VECTOR_TABLE_Type __VECTOR_TABLE[496];
const VECTOR_TABLE_Type __VECTOR_TABLE[496] __VECTOR_TABLE_ATTRIBUTE = {
    (VECTOR_TABLE_Type)(&__INITIAL_SP), /*     Initial Stack Pointer */
    Reset_Handler,                      /*     Reset Handler */
    NMI_Handler,                        /* -14 NMI Handler */
    HardFault_Handler,                  /* -13 Hard Fault Handler */
    MemManage_Handler,                  /* -12 MPU Fault Handler */
    BusFault_Handler,                   /* -11 Bus Fault Handler */
    UsageFault_Handler,                 /* -10 Usage Fault Handler */
    SecureFault_Handler,                /*  -9 Secure Fault Handler */
    0,                                  /*     Reserved */
    0,                                  /*     Reserved */
    0,                                  /*     Reserved */
    SVC_Handler,                        /*  -5 SVCall Handler */
    DebugMon_Handler,                   /*  -4 Debug Monitor Handler */
    0,                                  /*     Reserved */
    PendSV_Handler,                     /*  -2 PendSV Handler */
    SysTick_Handler,                    /*  -1 SysTick Handler */

    /* Interrupts */
    UART0_Handler,
    UART1_Handler,
    TIMR0_Handler,
    TIMR1_Handler,
    DMA_Handler,
    SPI0_Handler,
    PWM0_Handler,
    WDT_Handler,
    UART2_Handler,
    PWM1_Handler,
    ADC0_Handler,
    BTIMR0_Handler,
    HALL0_Handler,
    PWM2_Handler,
    PWMBRK_Handler,
    I2C0_Handler,
    CAN0_Handler,
    SPI1_Handler,
    RTC_Handler,
    PWM3_Handler,
    TIMR2_Handler,
    UART3_Handler,
    TIMR3_Handler,
    ADC1_Handler,
    BOD_Handler,
    CORDIC_Handler,
    BTIMR1_Handler,
    PWM4_Handler,
    HALL3_Handler,
    BTIMR2_Handler,
    I2C1_Handler,
    BTIMR3_Handler,
    ACMP_Handler,
    XTALSTOP_Handler,
    FSPI_Handler,
    GPIOA_Handler,
    GPIOB_Handler,
    GPIOC_Handler,
    GPIOD_Handler,
    GPIOM_Handler,
    GPION_Handler,
    GPIOA0_Handler,
    GPIOA1_Handler,
    GPIOA5_Handler,
    GPIOA6_Handler,
    GPIOA10_Handler,
    GPIOA11_Handler,
    GPIOA12_Handler,
    GPIOA13_Handler,
    GPIOB0_Handler,
    GPIOB1_Handler,
    GPIOB2_Handler,
    GPIOC0_Handler,
    GPIOC1_Handler,
    GPIOC2_Handler,
    GPIOC3_Handler,
    GPIOC4_Handler,
    GPIOD3_Handler,
    GPIOD4_Handler,
    GPIOD5_Handler,
    GPIOD6_Handler,
    GPIOD7_Handler,
    GPIOD8_Handler,
    GPIOC9_Handler,
    GPIOC10_Handler,
    GPIOC11_Handler,
    GPIOC12_Handler,
    GPIOM0_Handler,
    GPIOM1_Handler,
    GPIOM2_Handler,
    GPIOM3_Handler,
    GPIOM4_Handler,
    DIV_Handler,
    LCD_Handler,
    GPIOE_Handler,
    JPEG_Handler,
    SDIO_Handler,
    USB_Handler,
    CAN1_Handler,
    TIMR4_Handler,
    BTIMR4_Handler,
    BTIMR5_Handler,
    BTIMR6_Handler,
    BTIMR7_Handler,
    BTIMR8_Handler,
    BTIMR9_Handler,
    BTIMR10_Handler,
    BTIMR11_Handler,
    DMA2D_Handler,
    QEI_Handler,
};

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif

/*----------------------------------------------------------------------------
  Reset Handler called on controller reset
 *----------------------------------------------------------------------------*/
__NO_RETURN void Reset_Handler(void)
{
    __set_MSPLIM((uint32_t)(&__STACK_LIMIT));

#if defined (__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
  SCB->VTOR = (uint32_t) &(__VECTOR_TABLE[0]);
#endif

#if defined (__FPU_USED) && (__FPU_USED == 1U)
  SCB->CPACR |= ((3U << 10U*2U) |           /* enable CP10 Full Access */
                 (3U << 11U*2U)  );         /* enable CP11 Full Access */
#endif

    SystemInit();      /* CMSIS System Initialization */
    sfc_init();
    sdram_init();
    extern uint32_t _sfc_length;
    extern uint32_t __SDRAM2_BASE;
    extern uint32_t __SFC_BASE;
    memcpy((uint32_t *)(&__SDRAM2_BASE),(void *)(&__SFC_BASE),(uint32_t)((uint32_t *)(&_sfc_length)));

    __PROGRAM_START(); /* Enter PreMain (C library entry point) */
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
#endif

/*----------------------------------------------------------------------------
  Hard Fault Handler
 *----------------------------------------------------------------------------*/
void HardFault_Handler(void)
{
    while (1)
        ;
}

/*----------------------------------------------------------------------------
  Default Handler for Exceptions / Interrupts
 *----------------------------------------------------------------------------*/
void Default_Handler(void)
{
    while (1)
        ;
}

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
#pragma clang diagnostic pop
#endif
