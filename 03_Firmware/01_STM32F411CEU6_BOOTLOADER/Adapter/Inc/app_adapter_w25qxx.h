/**
 * @file app_adapter_w25qxx.h
 * @author ZB (2536566200@qq.com)
 * @brief w25q64适配层
 * @version 0.1
 * @date 2025-09-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __APP_ADAPTER_W25QXX_H__
#define __APP_ADAPTER_W25QXX_H__

#include <main.h>
#include "bsp_driver_flash.h"

/**< w25qxx运行状态 */
typedef enum {
    W25QXX_ADAPTER_OK = 0,        /**< 运行成功 */
    W25QXX_ADAPTER_ERROR,         /**< 运行错误 */
}app_adapter_w25qxx_status_e;

/**
 * @brief 注册w25q64设备到驱动层
 * 
 * @return app_adapter_w25qxx_status_e 运行状态
 */
app_adapter_w25qxx_status_e app_adapter_w25qxx_register(void);







#endif





