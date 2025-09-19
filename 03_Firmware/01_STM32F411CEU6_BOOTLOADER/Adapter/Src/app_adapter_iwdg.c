/**
 * @file app_adapter_iwdg.c
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗适配层
 * @version 0.1
 * @date 2025-09-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "app_adapter_iwdg.h"

extern IWDG_HandleTypeDef hiwdg;

static bsp_driver_iwdg_status_e _app_adapter_iwdg_init(const struct bsp_driver_iwdg_object *dev);
static bsp_driver_iwdg_status_e _app_adapter_iwdg_deinit(const struct bsp_driver_iwdg_object *dev);
static bsp_driver_iwdg_status_e _app_adapter_iwdg_feed(const struct bsp_driver_iwdg_object *dev);

app_adapter_iwdg_status_e app_adapter_iwdg_register(void)
{
    bsp_driver_iwdg_object_t iwdg_obj = {
        .index          = 0,
        .user_data      = NULL,
        .pf_iwdg_init   = _app_adapter_iwdg_init,
        .pf_iwdg_deinit = _app_adapter_iwdg_deinit,
        .pf_iwdg_feed   = _app_adapter_iwdg_feed,
    };
    
    bsp_driver_iwdg_register(0, &iwdg_obj);
	
	return IWDG_ADAPTER_OK;
}

static bsp_driver_iwdg_status_e _app_adapter_iwdg_init(const struct bsp_driver_iwdg_object *dev)
{
	if(dev == NULL) {
		return IWDG_DRIVER_ERROR;
	}
	
	hiwdg.Instance 			= IWDG;
	hiwdg.Init.Prescaler 	= IWDG_PRESCALER_32;
	hiwdg.Init.Reload 		= 4000;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
		Error_Handler();
	}

    return IWDG_DRIVER_OK;
}

static bsp_driver_iwdg_status_e _app_adapter_iwdg_deinit(const struct bsp_driver_iwdg_object *dev)
{
	if(dev == NULL) {
		return IWDG_DRIVER_ERROR;
	}
	
	
    return IWDG_DRIVER_OK;
}

static bsp_driver_iwdg_status_e _app_adapter_iwdg_feed(const struct bsp_driver_iwdg_object *dev)
{
	if(dev == NULL) {
		return IWDG_DRIVER_ERROR;
	}
	
	HAL_IWDG_Refresh(&hiwdg);

    return IWDG_DRIVER_OK;
}



