/**
 * @file adapter_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键适配层
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ADAPTER_KEY_H__
#define __ADAPTER_KEY_H__

#include <stdint.h>

typedef enum {
    ADAPTER_KEY_STATUS_OK = 0,                                                      /**< 运行成功 */
    ADAPTER_KEY_STATUS_ERROR,                                                       /**< 运行错误 */
}adapter_key_status_e;

/**< 按键驱动对象结构体 */
typedef struct adapter_key_object {
    uint32_t index;                                                                  /**< Record the instance index. */
    void *user_data;                                                                 /**< Record the user data       */

    adapter_key_status_e (*pf_key_init)(void);                                       /**< function pointer to device init   */
    adapter_key_status_e (*pf_key_deinit)(void);                                     /**< function pointer to device deinit */
    adapter_key_status_e (*pf_key_scan)(uint8_t *state);                             /**< function pointer to device get    */
    adapter_key_status_e (*pf_key_cb)(void);                                         /**< function pointer to device event  */
    adapter_key_status_e (*pf_key_sleep)(void);                                      /**< function pointer to device sleep  */
    adapter_key_status_e (*pf_key_weakup)(void);                                     /**< function pointer to device weakup */
}adapter_key_object_t;

/**
 * @brief 将具体对象注册到驱动中
 * 
 * @param index 设备索引
 * @param dev 设备对象
 * @return adapter_key_status_e 运行状态
 */
adapter_key_status_e adapter_key_register(uint32_t index, adapter_key_object_t *dev);

/**
 * @brief 获取按键对象
 * 
 * @param index 设备索引
 * @param dev 设备对象
 * @return adapter_key_status_e 运行状态
 */
adapter_key_status_e adapter_key_get_object(uint32_t index, adapter_key_object_t *dev);

/**
 * @brief 初始化按键
 * 
 * @param dev 设备对象
 * @return adapter_key_status_e 运行状态
 */
adapter_key_status_e adapter_key_init(const adapter_key_object_t *dev);

/**
 * @brief 逆初始化按键
 * 
 * @param dev 设备对象
 * @return adapter_key_status_e 运行状态
 */
adapter_key_status_e adapter_key_deinit(const adapter_key_object_t *dev);

/**
 * @brief 按键扫描
 * 扫描所有对象
 * @return adapter_key_status_e 运行状态
 */
adapter_key_status_e adapter_key_scan(const adapter_key_object_t *dev);

#endif

