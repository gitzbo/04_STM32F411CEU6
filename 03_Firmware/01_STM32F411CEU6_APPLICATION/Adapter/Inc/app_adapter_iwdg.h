/**
 * @file app_adapter_iwdg.h
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗适配层
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_ADAPTER_iwdg_H__
#define __APP_ADAPTER_iwdg_H__

#include "main.h"

#include "bsp_driver_iwdg.h"

typedef enum {
    IWDG_ADAPTER_OK = 0,             // 正常
    IWDG_ADAPTER_ERROR,              // 异常
}app_adapter_iwdg_status_e;

/**
 * @brief 看门狗注册函数
 * 
 * @return app_adapter_iwdg_status_e 运行状态
 */
app_adapter_iwdg_status_e app_adapter_iwdg_register(void);






#endif


