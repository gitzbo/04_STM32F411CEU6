/**
 * @file adapter_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键适配层
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_key.h"
#include <stddef.h>
#include "platform_config.h"

#ifndef KEY_DEV_MAX
#define KEY_DEV_MAX                 1                    /**< 按键设备最大数量 */
#endif

adapter_key_object_t _key_drv_dev[KEY_DEV_MAX] = {0};    /**< 按键驱动 */

adapter_key_status_e adapter_key_register(uint32_t index, adapter_key_object_t *dev)
{
    if((dev == NULL) || (index >= KEY_DEV_MAX)) {
        return ADAPTER_KEY_STATUS_ERROR;
    }

    _key_drv_dev[index].index           = index;                           
    _key_drv_dev[index].pf_key_init     = dev->pf_key_init;                
    _key_drv_dev[index].pf_key_deinit   = dev->pf_key_deinit;              
    _key_drv_dev[index].pf_key_scan     = dev->pf_key_scan;                
    _key_drv_dev[index].pf_key_sleep    = dev->pf_key_sleep;
    _key_drv_dev[index].pf_key_weakup   = dev->pf_key_weakup;
	_key_drv_dev[index].pf_key_cb		= dev->pf_key_cb;

    return ADAPTER_KEY_STATUS_OK;
}

adapter_key_status_e adapter_key_get_object(uint32_t index, adapter_key_object_t *dev)
{
	if((index >= KEY_DEV_MAX) || (dev == NULL)){
		return ADAPTER_KEY_STATUS_ERROR;	
	}

	dev = &_key_drv_dev[index];
	
	return ADAPTER_KEY_STATUS_OK;
}

adapter_key_status_e adapter_key_init(const adapter_key_object_t *dev)
{
    if((dev == NULL) || (dev->pf_key_init == NULL)) {
        return ADAPTER_KEY_STATUS_ERROR;
    }

    dev->pf_key_init();

    return ADAPTER_KEY_STATUS_OK;
}

adapter_key_status_e adapter_key_deinit(const adapter_key_object_t *dev)
{
    if((dev == NULL) || (dev->pf_key_deinit == NULL)) {
        return ADAPTER_KEY_STATUS_ERROR;
    }

    dev->pf_key_deinit();

    return ADAPTER_KEY_STATUS_OK;
}

adapter_key_status_e adapter_key_scan(const adapter_key_object_t *dev)
{
	if(dev == NULL) {
		return ADAPTER_KEY_STATUS_ERROR;
	}
	
    uint8_t state = 0;

    return ADAPTER_KEY_STATUS_OK;
}






