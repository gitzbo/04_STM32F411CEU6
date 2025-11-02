/**
 * @file adapter_flash.c
 * @author ZB (2536566200@qq.com)
 * @brief flash适配层
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_flash.h"
#include <stddef.h>
#include "platform_config.h"

#ifndef FLASH_DEV_MAX
#define FLASH_DEV_MAX       1                             				                        /**< FLASH设备最大数量 */
#endif

adapter_flash_object_t _flash_drv_dev[FLASH_DEV_MAX] = {0};

adapter_flash_status_e adapter_flash_register(uint32_t index, adapter_flash_object_t *dev)
{
    if((dev == NULL) || (index >= FLASH_DEV_MAX)) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    _flash_drv_dev[index].index             = index;
    _flash_drv_dev[index].user_data         = dev->user_data;
    _flash_drv_dev[index].pf_flash_init     = dev->pf_flash_init;
    _flash_drv_dev[index].pf_flash_deinit   = dev->pf_flash_deinit;
    _flash_drv_dev[index].pf_flash_erase    = dev->pf_flash_erase;
    _flash_drv_dev[index].pf_flash_write    = dev->pf_flash_write;
    _flash_drv_dev[index].pf_flash_read     = dev->pf_flash_read;
    
    return ADAPTER_FLASH_STATUS_OK;
}

adapter_flash_status_e adapter_flash_get_object(uint32_t index, adapter_flash_object_t *dev)
{
	if((index > FLASH_DEV_MAX) ||
		(dev == NULL)) {
		return ADAPTER_FLASH_STATUS_ERROR;
	}
	
	*dev = _flash_drv_dev[index];
	
	return ADAPTER_FLASH_STATUS_OK;
}


adapter_flash_status_e adapter_flash_init(const adapter_flash_object_t *dev)
{
    if(dev->pf_flash_init == NULL) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    dev->pf_flash_init();

    return ADAPTER_FLASH_STATUS_OK;
}

adapter_flash_status_e adapter_flash_deinit(const adapter_flash_object_t *dev)
{
    if(dev->pf_flash_deinit == NULL) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    dev->pf_flash_deinit();

    return ADAPTER_FLASH_STATUS_OK;
}


adapter_flash_status_e adapter_flash_erase(const adapter_flash_object_t *dev, 
                                           uint32_t start_addr, 
                                           uint32_t end_addr)
{
    if(dev->pf_flash_erase == NULL) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    dev->pf_flash_erase(start_addr, end_addr);

    return ADAPTER_FLASH_STATUS_OK;
}   

adapter_flash_status_e adapter_flash_write(const adapter_flash_object_t *dev, 
                                           uint32_t start_addr, 
                                           const uint8_t *data, 
                                           uint32_t len)
{
    if(dev->pf_flash_write == NULL) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    dev->pf_flash_write(start_addr, data, len);

    return ADAPTER_FLASH_STATUS_OK;
}

adapter_flash_status_e adapter_flash_read(const adapter_flash_object_t *dev, 
                                          uint32_t start_addr, 
                                          uint8_t *data, 
                                          uint32_t len)
{
    if(dev->pf_flash_read == NULL) {
        return ADAPTER_FLASH_STATUS_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_read(start_addr, data, len);

    return ADAPTER_FLASH_STATUS_OK;
}

adapter_flash_status_e adapter_flash_copy(const adapter_flash_object_t *host,
										  uint32_t host_addr,
										  const adapter_flash_object_t *target,
										  uint32_t target_addr,
										  uint32_t target_len)
{
	if((host == NULL) || (target == NULL) || (target_len == 0) || 
	   (_flash_drv_dev[host->index].pf_flash_read == NULL) || 
	   (_flash_drv_dev[target->index].pf_flash_write == NULL)) {
		return ADAPTER_FLASH_STATUS_ERROR;
	}
	
	uint8_t data[1] = {0};
	
	for(uint32_t i = 0; i < target_len; i ++) {
		_flash_drv_dev[host->index].pf_flash_read(host_addr, data, 1);
		_flash_drv_dev[host->index].pf_flash_write(target_addr, data, 1);
	}
	
	return ADAPTER_FLASH_STATUS_OK;
}






