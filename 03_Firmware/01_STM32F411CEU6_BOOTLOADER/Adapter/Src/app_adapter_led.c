/**
 * @file app_led_adapt.c
 * @author ZB (2536566200@qq.com)
 * @brief led适配层
 * @version 0.1
 * @date 2025-09-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_adapter_led.h"

#include "main.h"

static void _app_adapter_blue_led_init(bsp_driver_led_object_t *dev);
static void _app_adapter_blue_led_deinit(bsp_driver_led_object_t *dev);
static void _app_adapter_blue_led_on(bsp_driver_led_object_t *dev);
static void _app_adapter_blue_led_off(bsp_driver_led_object_t *dev);
static void _app_adapter_blue_led_sleep(bsp_driver_led_object_t *dev);
static void _app_adapter_blue_led_weakup(bsp_driver_led_object_t *dev);

app_adapter_led_status_e app_adapter_led_register(void)
{
    bsp_driver_led_object_t _blue_led = {
        .index 			= 0,
        .user_data 		= NULL,
        .pf_led_init 	= _app_adapter_blue_led_init,
        .pf_led_deinit 	= _app_adapter_blue_led_deinit,
        .pf_led_on 		= _app_adapter_blue_led_on,
        .pf_led_off 	= _app_adapter_blue_led_off,
        .pf_led_sleep 	= _app_adapter_blue_led_sleep,
        .pf_led_weakup 	= _app_adapter_blue_led_weakup,
    };

    bsp_driver_led_register(_blue_led.index, &_blue_led);

    return APP_ADAPTER_LED_OK;
}


static void _app_adapter_blue_led_init(bsp_driver_led_object_t *dev)
{
    if(dev == NULL) {
        return ;
    }

    __HAL_RCC_GPIOC_CLK_ENABLE();

    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_SET);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_BLUE_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_BLUE_1_GPIO_Port, &GPIO_InitStruct);

    return ;
}

static void _app_adapter_blue_led_deinit(bsp_driver_led_object_t *dev)
{
	if(dev == NULL) {
		return ;
	}
	
    return ;
}

static void _app_adapter_blue_led_on(bsp_driver_led_object_t *dev)
{
    if(dev == NULL) {
		return ;
	}

    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_RESET);

    return ;
}


static void _app_adapter_blue_led_off(bsp_driver_led_object_t *dev)
{
    if(dev == NULL) {
		return ;
	}

    HAL_GPIO_WritePin(LED_BLUE_1_GPIO_Port, LED_BLUE_1_Pin, GPIO_PIN_SET);

    return ;
}

static void _app_adapter_blue_led_sleep(bsp_driver_led_object_t *dev)
{
	if(dev == NULL) {
		return ;
	}

	return ;
}

static void _app_adapter_blue_led_weakup(bsp_driver_led_object_t *dev)
{
	if(dev == NULL) {
		return ;
	}
	
	return ;
}





