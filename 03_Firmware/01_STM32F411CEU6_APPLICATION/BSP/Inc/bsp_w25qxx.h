/**
 * @file bsp_w25qxx.h
 * @author ZB (2536566200@qq.com)
 * @brief w25qxx驱动
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BSP_W25QXX_H__
#define __BSP_W25QXX_H__

#include <stdint.h>

/**< w25qxx运行状态 */
typedef enum {
    BSP_W25QXX_STATUS_OK = 0,        /**< 运行成功 */
    BSP_W25QXX_STATUS_ERROR,         /**< 运行错误 */
}bsp_w25qxx_status_e;

/**
 * @brief 注册w25q64设备到驱动层
 * 
 * @return bsp_w25qxx_status_e 运行状态
 */
bsp_w25qxx_status_e app_adapter_w25qxx_register(void);

/**
 * @brief w25qxx初始化
 * 
 * @param dev 设备对象
 */
bsp_w25qxx_status_e bsp_w25qxx_init(void);

/**
 * @brief w25qxx逆初始化
 * 
 * @param dev 设备对象
 * @return bsp_w25qxx_status_e 运行状态
 */
bsp_w25qxx_status_e bsp_w25qxx_deinit(void);

/**
 * @brief w25qxx擦除
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param len 数据长度
 * @return bsp_w25qxx_status_e 运行状态 
 */
bsp_w25qxx_status_e bsp_w25qxx_erase(uint32_t start_addr, uint32_t len);

/**
 * @brief w25qxx写入
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待写入数据地址
 * @param len 数据长度
 * @return bsp_w25qxx_status_e 运行状态
 */
bsp_w25qxx_status_e bsp_w25qxx_write(uint32_t start_addr, const uint8_t *data, uint32_t len);

/**
 * @brief w25qxx读取
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待读取数据地址
 * @param len 数据长度
 * @return bsp_w25qxx_status_e 运行状态
 */
bsp_w25qxx_status_e bsp_w25qxx_read(uint32_t start_addr, uint8_t *data, uint32_t len);


#endif

