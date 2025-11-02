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

#include "bsp_led.h"
#include "main.h"

bsp_led_status_e bsp_blue_led_init(void)
{
    __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_SET);

    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin   = LED_BLUE_1_Pin,
        .Mode  = GPIO_MODE_OUTPUT_PP,
        .Pull  = GPIO_PULLUP,
        .Speed = GPIO_SPEED_FREQ_LOW,
    };
    HAL_GPIO_Init(LED_BLUE_1_GPIO_Port, &GPIO_InitStruct);

    return BSP_LED_STATUS_OK;
}

bsp_led_status_e bsp_blue_led_deinit(void)
{
    return BSP_LED_STATUS_OK;
}

bsp_led_status_e bsp_blue_led_on(void)
{
    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_RESET);

    return BSP_LED_STATUS_OK;
}


bsp_led_status_e bsp_blue_led_off(void)
{
    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_SET);

    return BSP_LED_STATUS_OK;
}

bsp_led_status_e bsp_blue_led_sleep(void)
{
	return BSP_LED_STATUS_OK;
}

bsp_led_status_e bsp_blue_led_weakup(void)
{
	return BSP_LED_STATUS_OK;
}


