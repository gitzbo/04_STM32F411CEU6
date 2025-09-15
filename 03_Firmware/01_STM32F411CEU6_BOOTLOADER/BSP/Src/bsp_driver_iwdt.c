/**
 * @file bsp_driver_iwdt.c
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗驱动
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_driver_iwdt.h"

bsp_driver_iwdt_object_t _iwdt_drv_dev[IWDT_DEV_MAX] = {0};    /**< 独立看门狗驱动内存池 */

bsp_driver_iwdt_status_e bsp_driver_iwdt_register(uint32_t index, bsp_driver_iwdt_object_t *dev)
{
    if((dev == NULL) || 
        (index >= IWDT_DEV_MAX)) {
        return IWDT_DRIVER_ERROR;
    }

    _iwdt_drv_dev[index].index = index;
    _iwdt_drv_dev[index].user_data = dev->user_data;
    _iwdt_drv_dev[index].pf_iwdt_init = dev->pf_iwdt_init;
    _iwdt_drv_dev[index].pf_iwdt_deinit = dev->pf_iwdt_deinit;
    _iwdt_drv_dev[index].pf_iwdt_feed = dev->pf_iwdt_feed;

    return IWDT_DRIVER_OK;
}

bsp_driver_iwdt_status_e bsp_driver_iwdt_init(const bsp_driver_iwdt_object_t *dev)
{
    if((dev == NULL) || 
        (dev->index >= IWDT_DEV_MAX) || 
        (_iwdt_drv_dev[dev->index].pf_iwdt_init == NULL)) {
        return IWDT_DRIVER_ERROR;
    }

    _iwdt_drv_dev[dev->index].pf_iwdt_init(dev);

    return IWDT_DRIVER_OK;
}

bsp_driver_iwdt_status_e bsp_driver_iwdt_deinit(const bsp_driver_iwdt_object_t *dev)
{
    if((dev == NULL) || 
        (dev->index >= IWDT_DEV_MAX) || 
        (_iwdt_drv_dev[dev->index].pf_iwdt_deinit == NULL)) {
        return IWDT_DRIVER_ERROR;
    }

    _iwdt_drv_dev[dev->index].pf_iwdt_deinit(dev);

    return IWDT_DRIVER_OK;
}

bsp_driver_iwdt_status_e bsp_driver_iwdt_feed(const bsp_driver_iwdt_object_t *dev)
{
    if((dev == NULL) || 
        (dev->index >= IWDT_DEV_MAX) || 
        (_iwdt_drv_dev[dev->index].pf_iwdt_feed == NULL)) {
        return IWDT_DRIVER_ERROR;
    }

    _iwdt_drv_dev[dev->index].pf_iwdt_feed(dev);

    return IWDT_DRIVER_OK;
}










