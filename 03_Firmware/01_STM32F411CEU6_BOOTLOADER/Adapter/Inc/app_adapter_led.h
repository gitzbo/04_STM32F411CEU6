/**
 * @file app_led_adapt.h
 * @author ZB (2536566200@qq.com)
 * @brief LED适配层
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __APP_LED_ADAPTER_H__
#define __APP_LED_ADAPTER_H__

#include "bsp_driver_led.h"

/* LED适配层操作 */
typedef enum {
    APP_ADAPTER_LED_OK = 0,           // 适配层正常
    APP_ADAPTER_LED_ERROR,            // 适配层错误
    APP_ADAPTER_LED_INVALID_PARAM,    // 参数异常
}app_adapter_led_status_e;

/**
 * @brief 注册led对象
 * 
 * @return app_led_adapt_status_e 运行状态
 */
app_adapter_led_status_e app_adapter_led_register(void);























#endif


