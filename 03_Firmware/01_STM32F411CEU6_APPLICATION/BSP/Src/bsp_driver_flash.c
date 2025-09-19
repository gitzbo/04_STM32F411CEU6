/**
 * @file bsp_driver_flash.c
 * @author ZB (2536566200@qq.com)
 * @brief flash驱动
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_driver_flash.h"

bsp_driver_flash_object_t _flash_drv_dev[FLASH_DEV_MAX] = {0};    /**< flash驱动内存池 */

bsp_driver_flash_status_e bsp_driver_flash_register(uint32_t index, bsp_driver_flash_object_t *dev)
{
    if((dev == NULL) || 
        (index >= FLASH_DEV_MAX)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[index].index             = index;
    _flash_drv_dev[index].user_data         = dev->user_data;
    _flash_drv_dev[index].pf_flash_init     = dev->pf_flash_init;
    _flash_drv_dev[index].pf_flash_deinit   = dev->pf_flash_deinit;
    _flash_drv_dev[index].pf_flash_erase    = dev->pf_flash_erase;
    _flash_drv_dev[index].pf_flash_write    = dev->pf_flash_write;
    _flash_drv_dev[index].pf_flash_read     = dev->pf_flash_read;
    
    return FLASH_DRIVER_OK;
}

bsp_driver_flash_status_e bsp_driver_flash_get_object(uint32_t index, bsp_driver_flash_object_t *dev)
{
	if((index > FLASH_DEV_MAX) ||
		(dev == NULL)) {
		return FLASH_DRIVER_ERROR;
	}
	
	*dev = _flash_drv_dev[index];
	
	return FLASH_DRIVER_OK;
}


bsp_driver_flash_status_e bsp_driver_flash_init(const bsp_driver_flash_object_t *dev)
{
    if((dev == NULL) || 
        (dev->index >= FLASH_DEV_MAX) || 
        (_flash_drv_dev[dev->index].pf_flash_init == NULL)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_init(dev);

    return FLASH_DRIVER_OK;
}

bsp_driver_flash_status_e bsp_driver_flash_deinit(const bsp_driver_flash_object_t *dev)
{
    if((dev == NULL) || 
        (dev->index >= FLASH_DEV_MAX) || 
        (_flash_drv_dev[dev->index].pf_flash_deinit == NULL)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_deinit(dev);

    return FLASH_DRIVER_OK;
}


bsp_driver_flash_status_e bsp_driver_flash_erase(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                uint32_t end_addr)
{
    if((dev == NULL) || 
        (dev->index >= FLASH_DEV_MAX) || 
        (_flash_drv_dev[dev->index].pf_flash_erase == NULL)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_erase(dev, start_addr, end_addr);

    return FLASH_DRIVER_OK;
}   

bsp_driver_flash_status_e bsp_driver_flash_write(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                const uint8_t *data, 
                                                uint32_t len)
{
    if((dev == NULL) || 
        (dev->index >= FLASH_DEV_MAX) || 
        (_flash_drv_dev[dev->index].pf_flash_write == NULL)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_write(dev, start_addr, data, len);

    return FLASH_DRIVER_OK;
}

bsp_driver_flash_status_e bsp_driver_flash_read(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                uint8_t *data, 
                                                uint32_t len)
{
    if((dev == NULL) || 
        (dev->index >= FLASH_DEV_MAX) || 
        (_flash_drv_dev[dev->index].pf_flash_read == NULL)) {
        return FLASH_DRIVER_ERROR;
    }

    _flash_drv_dev[dev->index].pf_flash_read(dev, start_addr, data, len);

    return FLASH_DRIVER_OK;
}

bsp_driver_flash_status_e bsp_driver_flash_copy( const bsp_driver_flash_object_t *host,
												 uint32_t host_addr,
												 const bsp_driver_flash_object_t *target,
												 uint32_t target_addr,
												 uint32_t target_len)
{
	if((host == NULL) || 
		(target == NULL) || 
		(target_len == 0) || 
		(_flash_drv_dev[host->index].pf_flash_read == NULL) || 
		(_flash_drv_dev[target->index].pf_flash_write == NULL)) {
		return FLASH_DRIVER_ERROR;
	}
	
	uint8_t data[1] = {0};
	
	for(uint32_t i = 0; i < target_len; i ++) {
		_flash_drv_dev[host->index].pf_flash_read(host, host_addr, data, 1);
		_flash_drv_dev[host->index].pf_flash_write(target, target_addr, data, 1);
	}
	
	return FLASH_DRIVER_OK;
}





