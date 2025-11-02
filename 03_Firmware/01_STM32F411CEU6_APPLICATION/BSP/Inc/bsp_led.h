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

#include <stdint.h>

typedef enum {
    BSP_LED_STATUS_OK = 0,           // 适配层正常
    BSP_LED_STATUS_ERROR,            // 适配层错误
}bsp_led_status_e;

/**
 * @brief 初始化LED
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_init(void);

/**
 * @brief 逆初始化LED
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_deinit(void);

/**
 * @brief LED开启
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_on(void);

/**
 * @brief LED关闭
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_off(void);

/**
 * @brief LED休眠
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_sleep(void);

/**
 * @brief LED唤醒
 * 
 * @return bsp_led_status_e 运行状态
 */
bsp_led_status_e bsp_blue_led_weakup(void);


#endif



