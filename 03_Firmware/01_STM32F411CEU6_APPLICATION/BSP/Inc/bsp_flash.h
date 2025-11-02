/**
 * @file bsp_flash.h
 * @author ZB (2536566200@qq.com)
 * @brief flash驱动
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#include <stdint.h>

#define FLASH_START_ADDRESS          0x08004000                 /**< 内部应用flash起始地址 */
#define FLASH_END_ADDRESS            0x08080000                 /**< 内部应用flash结束地址 */

#define FLASH_SECTOR0_ADDR           0x08004000                 /**< 内部flash扇区大小:16K */
#define FLASH_SECTOR1_ADDR           0x08008000                 /**< 内部flash扇区大小:16K */
#define FLASH_SECTOR2_ADDR           0x0800C000                 /**< 内部flash扇区大小:16K */
#define FLASH_SECTOR3_ADDR           0x08010000                 /**< 内部flash扇区大小:16K */
#define FLASH_SECTOR4_ADDR           0x08020000                 /**< 内部flash扇区大小:64K */
#define FLASH_SECTOR5_ADDR           0x08040000                 /**< 内部flash扇区大小:128K */
#define FLASH_SECTOR6_ADDR           0x08060000                 /**< 内部flash扇区大小:128K */
#define FLASH_SECTOR7_ADDR           0x08080000                 /**< 内部flash扇区大小:128K */

/**< 适配运行状态 */
typedef enum {
    BSP_FLASH_STATUS_OK = 0,        /**< 运行成功 */
    BSP_FLASH_STATUS_ERROR,         /**< 运行错误 */
}bsp_flash_status_e;

/**
 * @brief flash初始化
 * 
 */
bsp_flash_status_e bsp_int_flash_init(void);


/**
 * @brief flash逆初始化
 * 
 */
bsp_flash_status_e bsp_int_flash_deinit(void);

/**
 * @brief flash清除
 * 
 * @param start_addr 起始地址 
 * @param len 长度
 */
bsp_flash_status_e bsp_int_flash_erase(uint32_t start_addr, uint32_t len);

/**
 * @brief flash写入
 * 
 * @param start_addr 起始地址
 * @param data 数据
 * @param len 长度
 */
bsp_flash_status_e bsp_int_flash_write(uint32_t start_addr, const uint8_t *data, uint32_t len);

/**
 * @brief flash读取
 * 
 * @param start_addr 起始地址
 * @param data 数据
 * @param len 长度
 */
bsp_flash_status_e bsp_int_flash_read(uint32_t start_addr, uint8_t *data, uint32_t len);



#endif


