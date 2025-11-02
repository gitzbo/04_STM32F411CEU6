/**
 * @file led_adapt.h
 * @author ZB (2536566200@qq.com)
 * @brief LED适配层
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __LED_ADAPTER_H__
#define __LED_ADAPTER_H__

#include <stdint.h>

/* LED驱动状态枚举 */
typedef enum {
    ADAPTER_LED_STATUS_OK = 0,                                                          /**< 驱动正常 */ 
    ADAPTER_LED_STATUS_ERROR,                                                           /**< 驱动错误 */ 
}adapter_led_status_e;


/* LED对象结构体 */
typedef struct adapter_led_object{
    uint32_t index;                                                             /**< Record the instance index. */
    void *user_data;                                                            /**< Record the user data */

    adapter_led_status_e (*pf_led_init)(void);                                  /**< function pointer to device init */ 
    adapter_led_status_e (*pf_led_deinit)(void);                                /**< function pointer to device deinit */
    adapter_led_status_e (*pf_led_on)(void);                                    /**< function pointer to set on */ 
    adapter_led_status_e (*pf_led_off)(void);                                   /**< function pointer to set off */
    adapter_led_status_e (*pf_led_sleep)(void);                                 /**< function pointer to set sleep */
    adapter_led_status_e (*pf_led_weakup)(void);                                /**< function pointer to set weakup */
}adapter_led_object_t;

/**
 * @brief 初始化LED对象
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_led_driver_status_e 运行状态
 */
adapter_led_status_e adapter_led_register(uint32_t index, adapter_led_object_t *dev);

/**
 * @brief 获取目标索引的对象
 * 
 * @param index 索引
 * @param dev 设备对象存放
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_get_object(uint32_t index, adapter_led_object_t *dev);

/**
 * @brief LED初始化
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_init(const adapter_led_object_t *dev);

/**
 * @brief LED逆初始化
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_deinit(const adapter_led_object_t *dev);

/**
 * @brief LED开启
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_on(const adapter_led_object_t *dev);

/**
 * @brief LED关闭
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_off(const adapter_led_object_t *dev);

/**
 * @brief LED进入低功耗模式
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_sleep(const adapter_led_object_t *dev);

/**
 * @brief LED退出低功耗模式
 * 
 * @param dev 设备对象
 * @return adapter_led_status_e 运行状态
 */
adapter_led_status_e adapter_led_weakup(const adapter_led_object_t *dev);



#endif


