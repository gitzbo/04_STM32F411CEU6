/**
 * @file bsp_iwdg.h
 * @author ZB (2536566200@qq.com)
 * @brief 独立看门狗驱动
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_IWDG_H__
#define __BSP_IWDG_H__

typedef enum {
    BSP_IWDG_STATUS_OK = 0,             // 正常
    BSP_IWDG_STATUS_ERROR,              // 异常
}bsp_iwdg_status_e;

/**
 * @brief 看门狗初始化
 * 
 * @return bsp_iwdg_status_e 运行状态
 */
bsp_iwdg_status_e bsp_iwdg_init(void);

/**
 * @brief 看门狗逆初始化
 * 
 * @return bsp_iwdg_status_e 运行状态
 */
bsp_iwdg_status_e bsp_iwdg_deinit(void);

/**
 * @brief 看门狗喂狗函数
 * 
 * @return bsp_iwdg_status_e 运行状态
 */
bsp_iwdg_status_e bsp_iwdg_feed(void);





#endif

