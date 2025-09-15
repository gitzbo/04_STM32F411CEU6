/**
 * @file bsp_driver_iwdt.h
 * @author ZB (2536566200@qq.com)
 * @brief 独立看门狗驱动
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_DRIVER_IWDT_H__
#define __BSP_DRIVER_IWDT_H__

#include <stdint.h>
#include <stddef.h>

#define IWDT_DEV_MAX                 1                                               /**< 独立看门狗设备最大数量 */ 

/**< 运行状态 */
typedef enum {
    IWDT_DRIVER_OK = 0,                                                              /**< 运行成功 */
    IWDT_DRIVER_ERROR,                                                               /**< 运行错误 */
}bsp_driver_iwdt_status_e;

/**< 看门狗结构体对象 */
typedef struct bsp_driver_iwdt_object {
    uint32_t index;                                                                 /**< Record the instance index. */
    void *user_data;                                                                /**< Record the user data       */

    void (*pf_iwdt_init)(const struct bsp_driver_iwdt_object *dev);                 /**< function pointer to device init   */
    void (*pf_iwdt_deinit)(const struct bsp_driver_iwdt_object *dev);               /**< function pointer to device deinit */
    void (*pf_iwdt_feed)(const struct bsp_driver_iwdt_object *dev);                 /**< function pointer to device refresh*/ 
} bsp_driver_iwdt_object_t;

/**
 * @brief 将独立看门狗设备注册到驱动中
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_driver_iwdt_status_e 运行状态
 */
bsp_driver_iwdt_status_e bsp_driver_iwdt_register(uint32_t index, bsp_driver_iwdt_object_t *dev);

/**
 * @brief 独立看门狗初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_iwdt_status_e 运行状态
 */
bsp_driver_iwdt_status_e bsp_driver_iwdt_init(const bsp_driver_iwdt_object_t *dev);

/**
 * @brief 独立看门狗去初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_iwdt_status_e 运行状态
 */
bsp_driver_iwdt_status_e bsp_driver_iwdt_deinit(const bsp_driver_iwdt_object_t *dev);

/**
 * @brief 独立看门狗喂狗
 * 
 * @param dev 设备对象
 * @return bsp_driver_iwdt_status_e 运行状态
 */
bsp_driver_iwdt_status_e bsp_driver_iwdt_feed(const bsp_driver_iwdt_object_t *dev);








#endif

