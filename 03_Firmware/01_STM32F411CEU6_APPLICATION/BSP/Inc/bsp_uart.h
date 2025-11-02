/**
 * @file bsp_uart.h
 * @author ZB (2536566200@qq.com)
 * @brief 串口驱动
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include <stdint.h>

typedef enum {
    BSP_UART_STATUS_OK = 0x00,
    BSP_UART_STATUS_ERROR,
} bsp_uart_status_e;
                         		
/**
 * @brief 串口1初始化函数
 * 
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_init(void);

/**
 * @brief 串口1逆初始化函数
 * 
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_deinit(void);

/**
 * @brief 串口1发送函数
 * 
 * @param data 数据
 * @param len 长度
 * @param timeout 超时时间
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_send(const uint8_t *data, uint32_t len, uint32_t timeout);

/**
 * @brief 串口1接收函数
 * 
 * @param data 数据
 * @param len 长度
 * @param timeout 超时时间
 * @return bsp_uart_status_e 运行状态 
 */
bsp_uart_status_e bsp_uart1_recv(uint8_t *data, uint32_t len, uint32_t timeout);

/**
 * @brief 串口1休眠函数
 * 
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_sleep(void);

/**
 * @brief 串口1唤醒函数
 * 
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_weakup(void);

/**
 * @brief 串口1启动dma接收
 * 
 * @param buffer 缓冲区地址
 * @return bsp_uart_status_e 运行状态
 */
bsp_uart_status_e bsp_uart1_start_dma_rx(uint8_t *buffer, uint32_t size);

#endif





