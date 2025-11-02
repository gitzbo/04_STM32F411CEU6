/**
 * @file app_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键应用
 * @version 0.1
 * @date 2025-09-26
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_key.h"

static Button _g_button_obj[3] = {0};
static UI_ACTION _g_action_obj = UI_ACTION_NONE;
static void _Callback_Button_Top_Handler(void* btn);
static void _Callback_Button_Mid_Handler(void* btn);
static void _Callback_Button_Down_Handler(void* btn);

app_key_status_e app_key_init(void)
{
	button_init(&_g_button_obj[0], app_adapter_key_get, 0, KEY_TOP_ID);
    button_init(&_g_button_obj[1], app_adapter_key_get, 0, KEY_MID_ID);
    button_init(&_g_button_obj[2], app_adapter_key_get, 0, KEY_DOWN_ID);

	button_attach(&_g_button_obj[0], SINGLE_CLICK, _Callback_Button_Top_Handler);
    button_attach(&_g_button_obj[0], LONG_PRESS_HOLD, _Callback_Button_Top_Handler);
    button_attach(&_g_button_obj[1], SINGLE_CLICK, _Callback_Button_Mid_Handler);
    button_attach(&_g_button_obj[1], LONG_PRESS_HOLD, _Callback_Button_Mid_Handler);
    button_attach(&_g_button_obj[2], SINGLE_CLICK, _Callback_Button_Down_Handler);
    button_attach(&_g_button_obj[2], LONG_PRESS_HOLD, _Callback_Button_Down_Handler);
	
	button_start(&_g_button_obj[0]);
    button_start(&_g_button_obj[1]);
    button_start(&_g_button_obj[2]);
	
    return KEY_APP_OK;
}

static void _Callback_Button_Top_Handler(void* btn)
{
    _g_action_obj = UI_ACTION_UP;
}

static void _Callback_Button_Mid_Handler(void* btn)
{
    _g_action_obj = UI_ACTION_ENTER;
}

static void _Callback_Button_Down_Handler(void* btn)
{
    _g_action_obj = UI_ACTION_DOWN;
}

UI_ACTION ButtonScan(void)
{
    switch (_g_action_obj)
    {
    case UI_ACTION_UP:
        _g_action_obj = UI_ACTION_NONE;
        return UI_ACTION_UP;
	
    case UI_ACTION_DOWN:
        _g_action_obj = UI_ACTION_NONE;
        return UI_ACTION_DOWN;
	
    case UI_ACTION_ENTER:
        _g_action_obj = UI_ACTION_NONE;
        return UI_ACTION_ENTER;
	
    default:
        break;
    }
    return UI_ACTION_NONE;
}


