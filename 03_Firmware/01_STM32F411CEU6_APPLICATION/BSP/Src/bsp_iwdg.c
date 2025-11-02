/**
 * @file bsp_iwdg.c
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗驱动
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_iwdg.h"
#include "main.h"

extern IWDG_HandleTypeDef hiwdg;

bsp_iwdg_status_e bsp_iwdg_init(void)
{
	hiwdg.Instance 			= IWDG;
	hiwdg.Init.Prescaler 	= IWDG_PRESCALER_32;
	hiwdg.Init.Reload 		= 4095;
	if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
		Error_Handler();
	}

    return BSP_IWDG_STATUS_OK;
}

bsp_iwdg_status_e bsp_iwdg_deinit(void)
{
    return BSP_IWDG_STATUS_OK;
}

bsp_iwdg_status_e bsp_iwdg_feed(void)
{
	HAL_IWDG_Refresh(&hiwdg);

    return BSP_IWDG_STATUS_OK;
}

bsp_iwdg_status_e bsp_iwdg_restart(void)
{
	HAL_NVIC_SystemReset();

	return BSP_IWDG_STATUS_OK;
}







