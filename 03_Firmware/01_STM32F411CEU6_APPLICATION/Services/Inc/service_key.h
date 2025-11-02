/**
 * @file service_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键服务
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __SERVICE_KEY_H__
#define __SERVICE_KEY_H__

#include <stdint.h>

typedef enum {
    SERVICE_KEY_STATUS_OK = 0,
    SERVICE_KEY_STATUS_ERROR,
} service_key_status_e;

/**
 * @brief 按键服务初始化
 * 
 * @return service_key_status_e 运行状态
 */
service_key_status_e service_key_init(void);










#endif

