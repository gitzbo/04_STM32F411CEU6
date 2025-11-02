/**
 * @file adapter_iwdg.c
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗适配层
 * @version 0.1
 * @date 2025-09-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "adapter_iwdg.h"
#include <stddef.h>
#include "platform_config.h"

#ifndef IWDG_DEV_MAX
#define IWDG_DEV_MAX    1  /**< 独立看门狗设备最大数量 */ 
#endif

adapter_iwdg_object_t _iwdg_drv_dev[IWDG_DEV_MAX] = {0};

adapter_iwdg_status_e adapter_iwdg_register(uint32_t index, adapter_iwdg_object_t *dev)
{
    if((dev == NULL) || (index >= IWDG_DEV_MAX)) {
        return IWDG_DRIVER_ERROR;
    }

    _iwdg_drv_dev[index].index          = index;
    _iwdg_drv_dev[index].user_data      = dev->user_data;
    _iwdg_drv_dev[index].pf_iwdg_init   = dev->pf_iwdg_init;
    _iwdg_drv_dev[index].pf_iwdg_deinit = dev->pf_iwdg_deinit;
    _iwdg_drv_dev[index].pf_iwdg_feed   = dev->pf_iwdg_feed;

    return IWDG_DRIVER_OK;
}

adapter_iwdg_status_e adapter_iwdg_get_object(uint32_t index, adapter_iwdg_object_t *dev)
{
    if((index >= IWDG_DEV_MAX) || (dev == NULL)){
		return IWDG_DRIVER_ERROR;	
	}

    *dev = _iwdg_drv_dev[index];

    return IWDG_DRIVER_OK;
}

adapter_iwdg_status_e adapter_iwdg_init(const adapter_iwdg_object_t *dev)
{
    if((dev->pf_iwdg_init == NULL)) {
        return IWDG_DRIVER_ERROR;
    }

    dev->pf_iwdg_init();

    return IWDG_DRIVER_OK;
}

adapter_iwdg_status_e adapter_iwdg_deinit(const adapter_iwdg_object_t *dev)
{
    if((dev->pf_iwdg_deinit == NULL)) {
        return IWDG_DRIVER_ERROR;
    }

    dev->pf_iwdg_deinit();

    return IWDG_DRIVER_OK;
}

adapter_iwdg_status_e adapter_iwdg_feed(const adapter_iwdg_object_t *dev)
{
    if((dev->pf_iwdg_feed == NULL)) {
        return IWDG_DRIVER_ERROR;
    }

    dev->pf_iwdg_feed();

    return IWDG_DRIVER_OK;
}



