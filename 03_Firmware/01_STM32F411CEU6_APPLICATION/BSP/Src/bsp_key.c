/**
 * @file bsp_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键驱动
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_key.h"
#include "main.h"

bsp_key_status_e bsp_key_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
	    .Pin  = KEY_1_Pin | KEY_2_Pin | KEY_3_Pin | KEY_4_Pin,
	    .Mode = GPIO_MODE_INPUT,
	    .Pull = GPIO_NOPULL,
    };
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    return BSP_KEY_STATUS_OK;
}

bsp_key_status_e bsp_key_deinit(void)
{
    HAL_GPIO_DeInit(GPIOA, KEY_1_Pin | KEY_2_Pin | KEY_3_Pin | KEY_4_Pin);

    return BSP_KEY_STATUS_OK;
}

bsp_key_status_e bsp_key_sleep(void)
{
    return BSP_KEY_STATUS_OK;
}

bsp_key_status_e bsp_key_weakup(void)
{
    return BSP_KEY_STATUS_OK;
}

bsp_key_status_e bsp_key_get(bsp_key_id_e id, uint8_t *state)
{
    if(state == NULL) {
        return BSP_KEY_STATUS_ERROR;  
    }

    switch (id) {
    case KEY_TOP_ID: {
        *state = HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin);
    }
    case KEY_MID_ID: {
        *state = HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin);
    }
    case KEY_DOWN_ID: {
        *state = HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin);
    }
    default: {
        return BSP_KEY_STATUS_ERROR;
    }
    }

    return BSP_KEY_STATUS_OK;
}





