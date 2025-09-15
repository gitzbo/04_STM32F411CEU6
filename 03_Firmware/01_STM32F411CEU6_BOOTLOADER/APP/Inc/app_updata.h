/**
 * @file app_updata.h
 * @author ZB (2536566200@qq.com)
 * @brief 升级应用
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_UPDATA_H__
#define __APP_UPDATA_H__

#include <stdint.h>

#include "main.h"

#define APP1_START_ADDR  0x08008000     /**< APP1开始地址 */
#define APP2_START_ADDR  0x08040000     /**< APP2开始地址 */

typedef void (*pfunction)(void);        /**< 函数指针 */

/**
 * @brief 跳转到应用程序
 * 
 */
void app_updata_jump_app(void);

/**
 * @brief 使用crc32算法计算应用的crc32值
 * 
 * @param addr 地址
 * @param size 大小
 * @return uint32_t crc32值
 */
uint32_t app_updata_crc32(uint32_t addr, uint32_t size);


#endif

