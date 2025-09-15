/**
 * @file bsp_driver_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键驱动
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_DRIVER_KEY_H__
#define __BSP_DRIVER_KEY_H__

#include <stdint.h>
#include <stddef.h>

#define KEY_DEV_MAX                 1                                               /**< 按键设备最大数量 */
#define KEY_DEV_DEBUNCE_TIME        10                                              /**< 按键消抖时间单位：ms */
#define KEY_DEV_LONG_TIME           1000                                            /**< 按键长按时间单位：ms */
#define KEY_DEV_DOUBLE_TIME         800                                             /**< 按键双击间隔时间单位：ms */


/**< 按键驱动运行枚举 */
typedef enum {
    KEY_DRIVER_OK = 0,                                                              /**< 运行成功 */
    KEY_DRIVER_ERROR,                                                               /**< 运行错误 */
}bsp_driver_key_status_e;

/**< 按键事件 */
typedef enum {
    KEY_DRIVER_NO_EVENT = 0,                                                        /**< 无事件 */
    KEY_DRIVER_PRESS_EVENT,                                                         /**< 按键按下事件 */
    KEY_DRIVER_RELEASE_EVENT,                                                       /**< 按键释放事件 */
    KEY_DRIVER_SHORT_PRESS_EVENT,                                                   /**< 按键短按事件 */
    KEY_DRIVER_LONG_PRESS_EVENT,                                                    /**< 按键长按事件 */
    KEY_DRIVER_DOUBLE_SHORT_PRESS_EVENT,                                            /**< 按键双击事件 */
    KEY_DRIVER_CONTINUE_PRESS_EVENT,                                                /**< 按键连续按下事件 */
}bsp_driver_key_event_status_e; 

/**< 按键时钟状态结构体 */
typedef struct {    
    uint32_t key_state : 4;                                                         /**< 按键当前状态 */
    uint32_t key_last_state : 4;                                                    /**< 上一次按键状态，用于判断多击 */
    uint32_t key_trigger_state : 2;                                                 /**< 按键触发电平 */
    uint32_t key_last_level : 2;                                                    /**< 按键当前电平 */

    uint32_t time_count;                                                            /**< 计时 */
    uint32_t debounce_time;                                                         /**< 消抖时间 */
    uint32_t long_time;                                                             /**< 长按时间 */
    uint32_t last_short_press_time;                                                 /**< 上一次短按时间 */ 
}bsp_driver_key_timer_status_t;

/**< 按键驱动对象结构体 */
typedef struct bsp_driver_key_object {
    uint32_t index;                                                                 /**< Record the instance index. */
    void *user_data;                                                                /**< Record the user data       */
    bsp_driver_key_timer_status_t key_state;                                        /**< Record the key state       */

    void (*pf_key_init)(const struct bsp_driver_key_object *dev);                   /**< function pointer to device init   */
    void (*pf_key_deinit)(const struct bsp_driver_key_object *dev);                 /**< function pointer to device deinit */
    void (*pf_key_scan)(const struct bsp_driver_key_object *dev, uint8_t *state);   /**< function pointer to device get    */
    void (*pf_key_cb)(const struct bsp_driver_key_object *dev);                     /**< function pointer to device event  */
    void (*pf_key_sleep)(const struct bsp_driver_key_object *dev);                  /**< function pointer to device sleep  */
    void (*pf_key_weakup)(const struct bsp_driver_key_object *dev);                 /**< function pointer to device weakup */
    void (*pf_get_systime)(uint32_t *ms);                                           /**< function pointer get system time  */
}bsp_driver_key_object_t;

/**
 * @brief 将具体对象注册到驱动中
 * 
 * @param index 设备索引
 * @param dev 设备对象
 * @return bsp_driver_key_status_e 运行状态
 */
bsp_driver_key_status_e bsp_driver_key_register(uint32_t index, bsp_driver_key_object_t *dev);

/**
 * @brief 获取按键对象
 * 
 * @param index 设备索引
 * @param dev 设备对象
 * @return bsp_driver_key_status_e 运行状态
 */
bsp_driver_key_status_e bsp_driver_key_get_object(uint32_t index, bsp_driver_key_object_t *dev);

/**
 * @brief 初始化按键
 * 
 * @param dev 设备对象
 * @return bsp_driver_key_status_e 运行状态
 */
bsp_driver_key_status_e bsp_driver_key_init(const bsp_driver_key_object_t *dev);

/**
 * @brief 逆初始化按键
 * 
 * @param dev 设备对象
 * @return bsp_driver_key_status_e 运行状态
 */
bsp_driver_key_status_e bsp_driver_key_deinit(const bsp_driver_key_object_t *dev);

/**
 * @brief 按键扫描
 * 扫描所有对象
 * @return bsp_driver_key_status_e 运行状态
 */
bsp_driver_key_status_e bsp_driver_key_scan(void);


#endif




