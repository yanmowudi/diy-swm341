/**
 * @file dev_sfc.h
 * @author lik
 * @brief sfc相关配置函数
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __DEV_SFC_H__
#define __DEV_SFC_H__

void sfc_init(void);
void sfc_memcpy(void * __restrict s1, const void * __restrict s2, size_t n);
#endif //__DEV_SFC_H__
