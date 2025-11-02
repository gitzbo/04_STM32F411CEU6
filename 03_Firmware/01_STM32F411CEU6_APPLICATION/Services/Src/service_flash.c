/**
 * @file service_flash.c
 * @author ZB (2536566200@qq.com)
 * @brief flash服务
 * @version 0.1
 * @date 2025-10-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "service_flash.h"
#include <stddef.h>
#include "adapter_flash.h"
#include "bsp_flash.h"
#include "bsp_w25qxx.h"

service_flash_status_e service_flash_init(void)
{
    /**< 1.注册内部flash对象 */
    adapter_flash_object_t int_flash_obj = {
        .index             = 0,
        .user_data         = NULL,
        .pf_flash_init     = bsp_int_flash_init,
        .pf_flash_deinit   = bsp_int_flash_deinit,
        .pf_flash_erase    = bsp_int_flash_erase,
        .pf_flash_write    = bsp_int_flash_write,
        .pf_flash_read     = bsp_int_flash_read,
    };
    adapter_flash_register(int_flash_obj.index, &int_flash_obj);

    /**< 2.注册外部flash对象 */
    adapter_flash_object_t ext_flash_obj = {
        .index             = 1,
        .user_data         = NULL,
        .pf_flash_init     = bsp_w25qxx_init,
        .pf_flash_deinit   = bsp_w25qxx_deinit,
        .pf_flash_erase    = bsp_w25qxx_erase,
        .pf_flash_write    = bsp_w25qxx_write,
        .pf_flash_read     = bsp_w25qxx_read,
    };
    adapter_flash_register(ext_flash_obj.index, &ext_flash_obj);

    return SERVICE_FLASH_STATUS_OK;
}

service_flash_status_e service_flash_write_version_info(server_updata_info_t *info)
{
    if(info == NULL) {
        return SERVICE_FLASH_STATUS_ERROR;
    }
    
    adapter_flash_object_t dev;
    if(ADAPTER_FLASH_STATUS_OK != adapter_flash_get_object(0, &dev)) {
        return SERVICE_FLASH_STATUS_ERROR;
    }

    adapter_flash_write(&dev, (SERVER_APP1_START_ADDR + SERVER_VER_OFFSET), (uint8_t *)info, sizeof(server_updata_info_t));

    return SERVICE_FLASH_STATUS_OK;
}

service_flash_status_e service_flash_read_version_info(server_updata_info_t *info)
{
    if(info == NULL) {
        return SERVICE_FLASH_STATUS_ERROR;
    }
    
    adapter_flash_object_t dev;
    if(ADAPTER_FLASH_STATUS_OK != adapter_flash_get_object(0, &dev)) {
        return SERVICE_FLASH_STATUS_ERROR;
    }

    adapter_flash_read(&dev, (SERVER_APP1_START_ADDR + SERVER_VER_OFFSET), (uint8_t *)info, sizeof(server_updata_info_t));

    return SERVICE_FLASH_STATUS_OK;
}



