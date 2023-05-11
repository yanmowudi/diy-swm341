/**
 * @file dev_gt9x.h
 * @author lik
 * @brief gt9x相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __DEV_GT9X_H__
#define __DEV_GT9X_H__

/** 触摸状态 */
enum
{
    TP_STATE_RELEASED = 0,
    TP_STATE_PRESSED
};

/** 触摸信息结构体 */
typedef struct
{
    uint16_t x;     /*!< 当前x坐标 */
    uint16_t y;     /*!< 当前y坐标 */
    uint8_t status; /*!< 触摸状态 */
} tp_dev_t;

extern tp_dev_t tp_dev;

void tp_init(void);

#endif //__DEV_GT9X_H__
