/**
 * @file bsp_driver_uart.h
 * @author ZB (2536566200@qq.com)
 * @brief 串口驱动
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_DRIVER_UART_H__
#define __BSP_DRIVER_UART_H__

#include <stddef.h>
#include <stdint.h>

#define UART_DEV_MAX     1                                                       /**< max uart device support */

/**< 串口运行状态 */
typedef enum {
    UART_DRIVER_OK = 0,                                                          /**< 驱动正常 */ 
    UART_DRIVER_ERROR,                                                           /**< 驱动错误 */ 
    UART_DRIVER_TIMEOUT,                                                         /**< 驱动超时 */
}bsp_driver_uart_status_e;

/**< 串口对象结构体 */
typedef struct bsp_driver_uart_object{
    uint32_t index;                                                                                     /**< Record the instance index. */
    void *user_data;                                                                                    /**< Record the user data */

    bsp_driver_uart_status_e (* pf_uart_init)(const struct bsp_driver_uart_object *dev);                /**< function pointer to device init */ 
    bsp_driver_uart_status_e (* pf_uart_deinit)(const struct bsp_driver_uart_object *dev);              /**< function pointer to device deinit */
    bsp_driver_uart_status_e (* pf_uart_send)(const struct bsp_driver_uart_object *dev, 
                                              const uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout);                                        /**< function pointer to send data */ 
    bsp_driver_uart_status_e (* pf_uart_recv)(const struct bsp_driver_uart_object *dev, 
                                              uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout);                                        /**< function pointer to receive data */
    bsp_driver_uart_status_e (* pf_uart_sleep)(const struct bsp_driver_uart_object *dev);               /**< function pointer to set sleep */
    bsp_driver_uart_status_e (* pf_uart_weakup)(const struct bsp_driver_uart_object *dev);              /**< function pointer to set weakup */
}bsp_driver_uart_object_t;

/**
 * @brief 串口对象注册
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_register(uint32_t index, bsp_driver_uart_object_t *dev);

/**
 * @brief 串口对象获取
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_get_object(uint32_t index, bsp_driver_uart_object_t *dev);

/**
 * @brief 串口初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_init(const bsp_driver_uart_object_t *dev);

/**
 * @brief 串口逆初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_deinit(const bsp_driver_uart_object_t *dev);

/**
 * @brief 串口发送数据
 * 
 * @param dev 设备对象
 * @param data 发送数据buffer
 * @param len 数据长度
 * @param timeout 超时时间
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_send(const bsp_driver_uart_object_t *dev, 
                                              const uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout);

/**
 * @brief 串口接收数据
 * 
 * @param dev 设备对象
 * @param data 接收数据buffer
 * @param len 数据长度
 * @param timeout 超时时间
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_recv(const bsp_driver_uart_object_t *dev, 
                                              uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout);

/**
 * @brief 串口休眠
 * 
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_sleep(const bsp_driver_uart_object_t *dev);

/**
 * @brief 串口唤醒
 * 
 * @param dev 设备对象
 * @return bsp_driver_uart_status_e 运行状态
 */
bsp_driver_uart_status_e bsp_driver_uart_weakup(const bsp_driver_uart_object_t *dev);




#endif





