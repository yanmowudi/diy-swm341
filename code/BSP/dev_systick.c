/**
 * @file dev_systick.c
 * @author lik
 * @brief systick相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "SWM341.h"

/** Timer ticks */
static __IO uint32_t systick = 0;

/**
 * @brief systick初始化
 * 
 * @return true 
 * @return false 
 */
bool systick_init(void)
{
    /** SystemFrequency / 1000   1ms中断一次 */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /** Capture error */
        return false;
    }
    return true;
}

/**
 * @brief systick加一
 * 
 */
void swm_inctick(void)
{
    systick++;
}

/**
 * @brief 获取systick
 * 
 * @return uint32_t systick
 */
uint32_t swm_gettick(void)
{
    return systick;
}

/**
 * @brief 毫秒级延时
 * 
 * @param ms 毫秒数
 */
void swm_delay_ms(uint32_t ms)
{
    uint32_t tickstart = 0;
    tickstart = swm_gettick();
    while ((swm_gettick() - tickstart) < ms)
    {
        ;
    }
}

/**
 * @brief 微秒级延时
 * 
 * @param us 微秒数
 * @note 该函数延时不能超过1ms
 */
void swm_delay_us(uint32_t us)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;

    /** 获得延时经过的 tick 数 */
    ticks = us * reload / 1000;
    /** 获得当前时间 */
    told = SysTick->VAL;
    while (1)
    {
        /** 循环获得当前时间，直到达到指定的时间后退出循环 */
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
            if (tcnt >= ticks)
            {
                break;
            }
        }
    }
}

__WEAK void SysTick_Handler_cb(void)
{
}
