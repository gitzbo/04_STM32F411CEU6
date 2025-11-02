/**
 * @file platform_init.h
 * @author ZB (2536566200@qq.com)
 * @brief platform初始化
 * @version 0.1
 * @date 2025-10-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_PLATFORM_INIT_H__
#define __APP_PLATFORM_INIT_H__

#include "app_service_flash.h"
#include "app_service_key.h"
#include "app_service_uart.h"
#include "app_service_upgread.h"
#include "app_service_wdt.h"

typedef enum {
    PLATFORM_STATUS_OK = 0,
    PLATFORM_STATUS_ERROR,
}platform_status_e;

/**
 * @brief 平台外设初始化
 * 
 * @return app_platform_status_e 运行状态
 */
platform_status_e platform_board_init(void);

/**
 * @brief 平台应用初始化
 * 
 * @return app_platform_status_e 运行状态
 */
platform_status_e platform_app_init(void);




#endif


