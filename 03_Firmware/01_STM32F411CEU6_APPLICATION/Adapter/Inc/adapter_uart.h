/**
 * @file adapter_uart.h
 * @author ZB (2536566200@qq.com)
 * @brief UART适配层
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ADAPTER_UART_H__
#define __ADAPTER_UART_H__

#include <stddef.h>
#include <stdint.h>
#include "platform_config.h"

#ifndef UART_DEV_MAX
#define UART_DEV_MAX     1                                                                              /**< max uart device support */
#endif
           
/**< 串口运行状态 */                        
typedef enum {                      
    ADAPTER_UART_STATUS_OK = 0,                                                                                 /**< 驱动正常 */ 
    ADAPTER_UART_STATUS_ERROR,                                                                                  /**< 驱动错误 */ 
}adapter_uart_status_e;

/**< 串口对象结构体 */
typedef struct adapter_uart_object{
    uint32_t index;                                                                                     /**< Record the instance index. */
    void *user_data;                                                                                    /**< Record the user data */

    adapter_uart_status_e (*pf_uart_init)(void);                                                        /**< function pointer to device init */ 
    adapter_uart_status_e (*pf_uart_deinit)(void);                                                      /**< function pointer to device deinit */
    adapter_uart_status_e (*pf_uart_send)(const uint8_t *data, uint32_t len, uint32_t timeout);         /**< function pointer to send data */ 
    adapter_uart_status_e (*pf_uart_recv)(uint8_t *data, uint32_t len, uint32_t timeout);               /**< function pointer to receive data */
    adapter_uart_status_e (*pf_uart_sleep)(void);                                                       /**< function pointer to set sleep */
    adapter_uart_status_e (*pf_uart_weakup)(void);                                                      /**< function pointer to set weakup */
}adapter_uart_object_t;

/**
 * @brief 串口对象注册
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_register(uint32_t index, adapter_uart_object_t *dev);

/**
 * @brief 串口对象获取
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_get_object(uint32_t index, adapter_uart_object_t *dev);

/**
 * @brief 串口初始化
 * 
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_init(const adapter_uart_object_t *dev);

/**
 * @brief 串口逆初始化
 * 
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_deinit(const adapter_uart_object_t *dev);

/**
 * @brief 串口发送数据
 * 
 * @param dev 设备对象
 * @param data 发送数据buffer
 * @param len 数据长度
 * @param timeout 超时时间
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_send(const adapter_uart_object_t *dev, const uint8_t *data, uint32_t len, uint32_t timeout);

/**
 * @brief 串口接收数据
 * 
 * @param dev 设备对象
 * @param data 接收数据buffer
 * @param len 数据长度
 * @param timeout 超时时间
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_recv(const adapter_uart_object_t *dev, uint8_t *data, uint32_t len, uint32_t timeout);

/**
 * @brief 串口休眠
 * 
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_sleep(const adapter_uart_object_t *dev);

/**
 * @brief 串口唤醒
 * 
 * @param dev 设备对象
 * @return adapter_uart_status_e 运行状态
 */
adapter_uart_status_e adapter_uart_weakup(const adapter_uart_object_t *dev);

#endif

