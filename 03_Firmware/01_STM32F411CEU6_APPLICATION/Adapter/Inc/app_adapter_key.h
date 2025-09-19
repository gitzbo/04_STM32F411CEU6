/**
 * @file app_adapter_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键适配层
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_ADAPTER_KEY_H__
#define __APP_ADAPTER_KEY_H__

#include "bsp_driver_key.h"

/**> 函数状态 */
typedef enum {
    APP_ADAPTER_KEY_OK = 0,             // 正常
    APP_ADAPTER_KEY_ERROR,              // 异常
}app_adapter_key_status_e;

/**
 * @brief 注册按键驱动
 * 
 * @param user_key_cb 用户按键回调函数
 * @return app_adapter_key_status_e 运行状态
 */
app_adapter_key_status_e app_adapter_key_register(void (*user_key_cb)(const bsp_driver_key_object_t *dev));




#endif

