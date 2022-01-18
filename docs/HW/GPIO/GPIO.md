# 通用I/O GPIO

!!! 注意

    如果无特殊需求，请使用GPIO_Atomic族函数

## 下面给出一种错误情况

```c title="gpio_error.c" linenums="1" hl_lines="10 17"
int main(void)
{
    SystemInit();

    GPIO_Init(GPIOA, PIN10, 1, 0, 0, 0); //输出
    GPIO_Init(GPIOA, PIN11, 1, 0, 0, 0); //输出

    TIMR_Init(TIMR4, TIMR_MODE_TIMER, CyclesPerUs, 10000, 1);  //每10ms触发一次中断
    TIMR_Start(TIMR4);

    while(1==1)
    {
        GPIO_ClrBit(GPIOA, PIN10);
        // GPIO_AtomicClrBit(GPIOA, PIN10);
    }
}

void TIMR4_Handler(void)
{
    TIMR_INTClr(TIMR4);
    GPIO_InvBit(GPIOA, PIN11);
    // GPIO_AtomicInvBit(GPIOA, PIN11);
}
```

![gpio_error](../../images/GPIO/gpio_error.png)

```c title="gpio_correct.c" linenums="1" hl_lines="11 18"
int main(void)
{
    SystemInit();

    GPIO_Init(GPIOA, PIN10, 1, 0, 0, 0); //输出
    GPIO_Init(GPIOA, PIN11, 1, 0, 0, 0); //输出

    TIMR_Init(TIMR4, TIMR_MODE_TIMER, CyclesPerUs, 10000, 1);  //每10ms触发一次中断
    TIMR_Start(TIMR4);

    while(1==1)
    {
        // GPIO_ClrBit(GPIOA, PIN10);
        GPIO_AtomicClrBit(GPIOA, PIN10);
    }
}

void TIMR4_Handler(void)
{
    TIMR_INTClr(TIMR4);
    // GPIO_InvBit(GPIOA, PIN11);
    GPIO_AtomicInvBit(GPIOA, PIN11);
}
```

![gpio_correct](../../images/GPIO/gpio_correct.png)