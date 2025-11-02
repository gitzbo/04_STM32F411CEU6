/**
 * @file adapter_flash.h
 * @author ZB (2536566200@qq.com)
 * @brief flash适配层
 * @version 0.1
 * @date 2025-09-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ADAPTER_FLASH_H__
#define __ADAPTER_FLASH_H__

#include <stdint.h>

/**< flash驱动文件 */
typedef enum {
    ADAPTER_FLASH_STATUS_OK = 0,                                                                                  /**< 运行成功 */
    ADAPTER_FLASH_STATUS_ERROR,                                                                                   /**< 运行错误 */
}adapter_flash_status_e;

/**< flash结构体对象 */
typedef struct adapter_flash_object {
    uint32_t index;                                                                                               /**< Record the instance index. */
    void *user_data;                                                                                              /**< Record the user data       */

    adapter_flash_status_e (*pf_flash_init)(void);                                                                /**< function pointer to device init   */
    adapter_flash_status_e (*pf_flash_deinit)(void);                                                              /**< function pointer to device deinit */
    adapter_flash_status_e (*pf_flash_erase)(uint32_t start_addr, uint32_t len);                                  /**< function pointer to device erase   */
    adapter_flash_status_e (*pf_flash_write)(uint32_t start_addr, const uint8_t *data, uint32_t len);             /**< function pointer to device write   */
    adapter_flash_status_e (*pf_flash_read)(uint32_t start_addr, uint8_t *data, uint32_t len);                    /**< function pointer to device read   */
} adapter_flash_object_t;

/**
 * @brief 将flash设备注册到驱动中
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_register(uint32_t index, adapter_flash_object_t *dev);

/**
 * @brief 获取flash对象
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_get_object(uint32_t index, adapter_flash_object_t *dev);

/**
 * @brief flash初始化
 * 
 * @param dev 设备对象
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_init(const adapter_flash_object_t *dev);

/**
 * @brief flash去初始化
 * 
 * @param dev 设备对象
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_deinit(const adapter_flash_object_t *dev);

/**
 * @brief flash擦除
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param len 擦除长度
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_erase(const adapter_flash_object_t *dev, 
                                           uint32_t start_addr, 
                                           uint32_t len);

/**
 * @brief flash写入
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待写入数据地址
 * @param len 数据长度
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_write(const adapter_flash_object_t *dev, 
                                           uint32_t start_addr, 
                                           const uint8_t *data,
                                           uint32_t len);

/**
 * @brief flash读取
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待存入数据地址
 * @param len 数据长度
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_read(const adapter_flash_object_t *dev, 
                                          uint32_t start_addr, 
                                          uint8_t *data,
                                          uint32_t len);

/**
 * @brief flash拷贝函数
 * 
 * @param host 待拷贝设备
 * @param host_addr 待拷贝地址
 * @param target 目标设备
 * @param target_addr 目标地址
 * @param target_len 目标长度
 * @return adapter_flash_status_e 运行状态
 */
adapter_flash_status_e adapter_flash_copy(const adapter_flash_object_t *host,
										  uint32_t host_addr,
										  const adapter_flash_object_t *target,
										  uint32_t target_addr,
										  uint32_t target_len);


#endif


