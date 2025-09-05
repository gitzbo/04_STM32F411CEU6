/**
 * @file bsp_led.c
 * @author ZB (2536566200@qq.com)
 * @brief LED驱动
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_driver_led.h"

static bsp_driver_led_object_t _led_drv_dev[LED_DEV_MAX];

bsp_driver_led_status_e bsp_driver_led_register(uint32_t index, bsp_driver_led_object_t *dev)
{
    if(dev == NULL) {
        return LED_DRIVER_INVALID_PARAM;
    }

    _led_drv_dev[index].index           = index;
    _led_drv_dev[index].user_data       = dev->user_data;
    _led_drv_dev[index].pf_led_init     = dev->pf_led_init;
    _led_drv_dev[index].pf_led_deinit   = dev->pf_led_deinit;
    _led_drv_dev[index].pf_led_on       = dev->pf_led_on;
    _led_drv_dev[index].pf_led_off      = dev->pf_led_off;
    _led_drv_dev[index].pf_led_sleep    = dev->pf_led_sleep;
    _led_drv_dev[index].pf_led_weakup   = dev->pf_led_weakup;

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_get_object(uint32_t index, bsp_driver_led_object_t *dev)
{
    if((_led_drv_dev[index].pf_led_init == NULL) ||
        (dev == NULL)) {
            return LED_DRIVER_INVALID_PARAM;
    }

    *dev = _led_drv_dev[index];

    return LED_DRIVER_OK;
}


bsp_driver_led_status_e bsp_driver_led_init(const bsp_driver_led_object_t *dev)
{
    if(dev->pf_led_init == NULL) {
        return LED_DRIVER_INVALID_PARAM;
    }
	
    dev->pf_led_init(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_deinit(const bsp_driver_led_object_t *dev)
{
    if(dev->pf_led_init == NULL) {
        return LED_DRIVER_INVALID_PARAM;
    }

    dev->pf_led_deinit(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_on(const bsp_driver_led_object_t *dev)
{
    if((dev->pf_led_on == NULL)) {
        return LED_DRIVER_INVALID_PARAM;
    }

    dev->pf_led_on(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_off(const bsp_driver_led_object_t *dev)
{
    if(dev->pf_led_off == NULL){
        return LED_DRIVER_INVALID_PARAM;
    }

    dev->pf_led_off(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_sleep(const bsp_driver_led_object_t *dev)
{
    if(dev->pf_led_sleep == NULL) {
        return LED_DRIVER_INVALID_PARAM;
    }

    dev->pf_led_sleep(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}

bsp_driver_led_status_e bsp_driver_led_weakup(const bsp_driver_led_object_t *dev)
{
    if(dev->pf_led_weakup == NULL) {
        return LED_DRIVER_INVALID_PARAM;
    }

    dev->pf_led_weakup(&_led_drv_dev[dev->index]);

    return LED_DRIVER_OK;
}


