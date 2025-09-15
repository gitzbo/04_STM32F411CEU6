/**
 * @file app_adapter_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键适配层
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_adapter_key.h"

#include "main.h"

/**< 用户按键驱动 */
static void _app_adapter_key_user_init(const bsp_driver_key_object_t *dev);
static void _app_adapter_key_user_deinit(const bsp_driver_key_object_t *dev);
static void _app_adapter_key_user_scan(const bsp_driver_key_object_t *dev, uint8_t *state);
static void _app_adapter_key_user_sleep(const bsp_driver_key_object_t *dev);
static void _app_adapter_key_user_weakup(const bsp_driver_key_object_t *dev);
static void _app_adapter_get_systick(uint32_t *ms);

app_adapter_key_status_e app_adapter_key_register(void (*user_key_cb)(const bsp_driver_key_object_t *dev))
{
    bsp_driver_key_object_t _user_key = {
        .index 			= 0,
        .user_data 		= NULL,
        .pf_key_init    = _app_adapter_key_user_init,
        .pf_key_deinit  = _app_adapter_key_user_deinit,
        .pf_key_scan    = _app_adapter_key_user_scan,
        .pf_key_sleep   = _app_adapter_key_user_sleep,
        .pf_key_weakup  = _app_adapter_key_user_weakup,
        .pf_get_systime = _app_adapter_get_systick,
        .pf_key_cb      = user_key_cb,
    };
	
	bsp_driver_key_register(0, &_user_key);

    return APP_ADAPTER_KEY_OK;
}


static void _app_adapter_key_user_init(const bsp_driver_key_object_t *dev)
{
    if(dev == NULL) {
        return ;
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = KEY_USER_1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY_USER_1_GPIO_Port, &GPIO_InitStruct);
}

static void _app_adapter_key_user_deinit(const bsp_driver_key_object_t *dev)
{
    if(dev == NULL) {
        return ;
    }

    HAL_GPIO_DeInit(KEY_USER_1_GPIO_Port, KEY_USER_1_Pin);
}

static void _app_adapter_key_user_scan(const bsp_driver_key_object_t *dev, uint8_t *state)
{
    /* 1.判断对象是否正常 */
    if(dev == NULL) {
        return ;
    }

    /* 2.读取按键状态是否满足设备状态 */
    if( HAL_GPIO_ReadPin(KEY_USER_1_GPIO_Port, KEY_USER_1_Pin) == GPIO_PIN_RESET) {
        *state = 1;
    }
    else {
        *state = 0;
    }
}

static void _app_adapter_key_user_sleep(const bsp_driver_key_object_t *dev)
{
    if(dev == NULL) {
        return ;
    }

}

static void _app_adapter_key_user_weakup(const bsp_driver_key_object_t *dev)
{
    if(dev == NULL) {
        return ;
    }

}

static void _app_adapter_get_systick(uint32_t *ms)
{
	*ms = HAL_GetTick();
}








