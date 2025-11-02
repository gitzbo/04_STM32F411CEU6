/**
 * @file led_adapt.c
 * @author ZB (2536566200@qq.com)
 * @brief led适配层
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_led.h"
#include <stddef.h>
#include "platform_config.h"

#ifndef LED_DEV_MAX
#define LED_DEV_MAX     1   /**< max led device support */
#endif

static adapter_led_object_t _led_drv_dev[LED_DEV_MAX];

adapter_led_status_e adapter_led_register(uint32_t index, adapter_led_object_t *dev)
{
    if(dev == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    _led_drv_dev[index].index           = index;
    _led_drv_dev[index].user_data       = dev->user_data;
    _led_drv_dev[index].pf_led_init     = dev->pf_led_init;
    _led_drv_dev[index].pf_led_deinit   = dev->pf_led_deinit;
    _led_drv_dev[index].pf_led_on       = dev->pf_led_on;
    _led_drv_dev[index].pf_led_off      = dev->pf_led_off;
    _led_drv_dev[index].pf_led_sleep    = dev->pf_led_sleep;
    _led_drv_dev[index].pf_led_weakup   = dev->pf_led_weakup;

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_get_object(uint32_t index, adapter_led_object_t *dev)
{
    if((_led_drv_dev[index].pf_led_init == NULL) ||
        (dev == NULL)) {
            return ADAPTER_LED_STATUS_ERROR;
    }

    *dev = _led_drv_dev[index];

    return ADAPTER_LED_STATUS_OK;
}


adapter_led_status_e adapter_led_init(const adapter_led_object_t *dev)
{
    if(dev->pf_led_init == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }
	
    dev->pf_led_init();

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_deinit(const adapter_led_object_t *dev)
{
    if(dev->pf_led_init == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    dev->pf_led_deinit();

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_on(const adapter_led_object_t *dev)
{
    if((dev->pf_led_on == NULL)) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    dev->pf_led_on();

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_off(const adapter_led_object_t *dev)
{
    if(dev->pf_led_off == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    dev->pf_led_off();

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_sleep(const adapter_led_object_t *dev)
{
    if(dev->pf_led_sleep == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    dev->pf_led_sleep();

    return ADAPTER_LED_STATUS_OK;
}

adapter_led_status_e adapter_led_weakup(const adapter_led_object_t *dev)
{
    if(dev->pf_led_weakup == NULL) {
        return ADAPTER_LED_STATUS_ERROR;
    }

    dev->pf_led_weakup();

    return ADAPTER_LED_STATUS_OK;
}


