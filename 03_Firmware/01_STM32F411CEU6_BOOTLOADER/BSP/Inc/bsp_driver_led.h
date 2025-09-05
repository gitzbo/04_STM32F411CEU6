/**
 * @file bsp_led.h
 * @author ZB (2536566200@qq.com)
 * @brief led驱动
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#include <stddef.h>
#include <stdint.h>

#define LED_DEV_MAX     1                                               /**< max led device support */

/* GPIO对象 */
typedef struct bsp_driver_led_object{
    uint32_t index;                                                     /**< Record the instance index. */
    void *user_data;                                                    /**< Record the user data */

    void (* pf_led_init)(struct bsp_driver_led_object *dev);            /**< function pointer to device init */ 
    void (* pf_led_deinit)(struct bsp_driver_led_object *dev);          /**< function pointer to device deinit */
    void (* pf_led_on)(struct bsp_driver_led_object *dev);              /**< function pointer to set on */ 
    void (* pf_led_off)(struct bsp_driver_led_object *dev);             /**< function pointer to set off */
    void (* pf_led_sleep)(struct bsp_driver_led_object *dev);           /**< function pointer to set sleep */
    void (* pf_led_weakup)(struct bsp_driver_led_object *dev);          /**< function pointer to set weakup */

}bsp_driver_led_object_t;

/* LED驱动状态 */
typedef enum {
    LED_DRIVER_OK = 0,                                                  /**< 驱动正常 */ 
    LED_DRIVER_ERROR,                                                   /**< 驱动错误 */ 
    LED_DRIVER_INVALID_PARAM,                                           /**< 参数异常 */ 
}bsp_driver_led_status_e;

/**
 * @brief led初始化对象
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_led_driver_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_register(uint32_t index, bsp_driver_led_object_t *dev);

/**
 * @brief 获取目标索引的对象
 * 
 * @param index 索引
 * @param dev 设备对象存放
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_get_object(uint32_t index, bsp_driver_led_object_t *dev);

/**
 * @brief LED初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_init(const bsp_driver_led_object_t *dev);

/**
 * @brief LED逆初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_deinit(const bsp_driver_led_object_t *dev);

/**
 * @brief LED开启
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_on(const bsp_driver_led_object_t *dev);

/**
 * @brief LED关闭
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_off(const bsp_driver_led_object_t *dev);

/**
 * @brief LED进入低功耗模式
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_sleep(const bsp_driver_led_object_t *dev);

/**
 * @brief LED退出低功耗模式
 * 
 * @param dev 设备对象
 * @return bsp_driver_led_status_e 运行状态
 */
bsp_driver_led_status_e bsp_driver_led_weakup(const bsp_driver_led_object_t *dev);



#endif



