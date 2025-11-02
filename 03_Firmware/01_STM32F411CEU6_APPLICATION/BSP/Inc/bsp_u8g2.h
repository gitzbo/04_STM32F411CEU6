/**
 * @file bsp_u8g2.h
 * @author ZB (2536566200@qq.com)
 * @brief u8g2驱动
 * @version 0.1
 * @date 2025-11-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BSP_U8G2_H__
#define __BSP_U8G2_H__

typedef enum {
    BSP_U8G2_STATUS_OK = 0,
    BSP_U8G2_STATUS_ERROR
} bsp_u8g2_status_e;

/**
 * @brief u8g2初始化
 * 
 * @return bsp_u8g2_status_e 运行状态
 */
bsp_u8g2_status_e bsp_u8g2_init(void);

/**
 * @brief 获取u8g2对象
 * 
 * @param dev 设备对象
 * @return bsp_u8g2_status_e 运行状态
 */
bsp_u8g2_status_e bsp_u8g2_get_obj(void *dev);

/**
 * @brief 删除u8g2对象
 * 
 * @param dev 设备对象
 * @return bsp_u8g2_status_e 运行状态
 */
bsp_u8g2_status_e bsp_u8g2_delete(void *dev);



#endif


