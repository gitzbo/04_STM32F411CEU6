/**
 * @file bsp_key.h
 * @author ZB (2536566200@qq.com)
 * @brief 按键驱动
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

#include <stdint.h>

/**> 函数状态 */
typedef enum {
    BSP_KEY_STATUS_OK = 0,             // 正常
    BSP_KEY_STATUS_ERROR,              // 异常
}bsp_key_status_e;

typedef enum {
    KEY_TOP_ID,
    KEY_MID_ID,
    KEY_DOWN_ID
}bsp_key_id_e;

/**
 * @brief 按键初始化
 * 
 * @return bsp_key_status_e 运行状态
 */
bsp_key_status_e bsp_key_init(void);

/**
 * @brief 按键逆初始化
 * 
 * @return bsp_key_status_e 运行状态
 */
bsp_key_status_e bsp_key_deinit(void);

/**
 * @brief 按键休眠
 * 
 * @return bsp_key_status_e 运行状态
 */
bsp_key_status_e bsp_key_sleep(void);

/**
 * @brief 按键唤醒
 * 
 * @return bsp_key_status_e 运行状态
 */
bsp_key_status_e bsp_key_weakup(void);

/**
 * @brief 按键状态获取
 * 
 * @param id 按键ID
 * @param state 状态
 * @return bsp_key_status_e 运行状态
 */
bsp_key_status_e bsp_key_get(bsp_key_id_e id, uint8_t *state);


#endif




