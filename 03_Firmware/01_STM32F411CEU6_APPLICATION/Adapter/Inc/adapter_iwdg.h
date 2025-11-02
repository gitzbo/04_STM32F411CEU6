/**
 * @file adapter_iwdg.h
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗适配层
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ADAPTER_iwdg_H__
#define __ADAPTER_iwdg_H__

#include <stdint.h>

/**< 运行状态 */
typedef enum {
    IWDG_DRIVER_OK = 0,                                                              /**< 运行成功 */
    IWDG_DRIVER_ERROR,                                                               /**< 运行错误 */
}adapter_iwdg_status_e;

/**< 看门狗结构体对象 */
typedef struct adapter_iwdg_object {
    uint32_t index;                                                                  /**< Record the instance index. */
    void *user_data;                                                                 /**< Record the user data       */

    adapter_iwdg_status_e (*pf_iwdg_init)(void);                                     /**< function pointer to device init   */
    adapter_iwdg_status_e (*pf_iwdg_deinit)(void);                                   /**< function pointer to device deinit */
    adapter_iwdg_status_e (*pf_iwdg_feed)(void);                                     /**< function pointer to device refresh*/ 
} adapter_iwdg_object_t;

/**
 * @brief 将独立看门狗设备注册到驱动中
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_iwdg_status_e 运行状态
 */
adapter_iwdg_status_e adapter_iwdg_register(uint32_t index, adapter_iwdg_object_t *dev);

/**
 * @brief 获取看门狗对象
 * 
 * @param index 设备索引
 * @param dev 设备对象
 * @return adapter_iwdg_status_e 运行状态
 */
adapter_iwdg_status_e adapter_iwdg_get_object(uint32_t index, adapter_iwdg_object_t *dev);

/**
 * @brief 独立看门狗初始化
 * 
 * @param dev 设备对象
 * @return adapter_iwdg_status_e 运行状态
 */
adapter_iwdg_status_e adapter_iwdg_init(const adapter_iwdg_object_t *dev);

/**
 * @brief 独立看门狗去初始化
 * 
 * @param dev 设备对象
 * @return adapter_iwdg_status_e 运行状态
 */
adapter_iwdg_status_e adapter_iwdg_deinit(const adapter_iwdg_object_t *dev);

/**
 * @brief 独立看门狗喂狗
 * 
 * @param dev 设备对象
 * @return adapter_iwdg_status_e 运行状态
 */
adapter_iwdg_status_e adapter_iwdg_feed(const adapter_iwdg_object_t *dev);

#endif


