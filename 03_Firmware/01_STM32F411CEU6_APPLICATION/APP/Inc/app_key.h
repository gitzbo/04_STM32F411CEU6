/**
 * @file app_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键应用
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_KEY_H__
#define __APP_KEY_H__

#include "main.h"

typedef enum {
    KEY_APP_OK = 0,
    KEY_APP_ERROR,
}app_key_status_e;

/**
 * @brief 按键初始化
 * 
 * @return app_key_status_e 运行状态
 */
app_key_status_e app_key_init(void);









#endif

