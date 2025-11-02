/**
 * @file service_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键服务
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "service_key.h"
#include <stddef.h>

#include "bsp_key.h"

#include "adapter_key.h"


service_key_status_e service_key_init(void)
{
    /**< 1.将按键注册到对象中 */
    adapter_key_object_t key_obj = {
        .index 			= 0,
        .user_data 		= NULL,
        .pf_key_init    = (adapter_key_status_e (*)(void))bsp_key_init,
        .pf_key_deinit  = (adapter_key_status_e (*)(void))bsp_key_deinit,                
        .pf_key_sleep   = (adapter_key_status_e (*)(void))bsp_key_sleep,
        .pf_key_weakup  = (adapter_key_status_e (*)(void))bsp_key_weakup,
    };
	adapter_key_register(0, &key_obj);

    /**< 2.将按键注册到Lwbtn中 */

    /**< 3.创建按键扫描线程 */

    return SERVICE_KEY_STATUS_OK;
}










