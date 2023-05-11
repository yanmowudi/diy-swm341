/**
 * @file dev_systick.h
 * @author lik
 * @brief systick相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __DEV_SYSTICK_H__
#define __DEV_SYSTICK_H__

int32_t systick_init(void);
void swm_inctick(void);
uint32_t swm_gettick(void);
void swm_delay_ms(uint32_t ms);
void swm_delay_us(uint32_t us);

#endif //__DEV_SYSTICK_H__
