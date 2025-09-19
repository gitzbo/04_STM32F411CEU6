/**
 * @file app_adapter_uart.h
 * @author ZB (2536566200@qq.com)
 * @brief UART适配层
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_ADAPTER_UART_H__
#define __APP_ADAPTER_UART_H__

#include "bsp_driver_uart.h"

#include "main.h"

#include "lwrb.h"

#define UART1_BUFFER_SIZE		256


typedef enum {
    UART_ADAPTER_OK = 0x00,
    UART_ADAPTER_ERROR,
} app_adapter_uart_status_e;

/**
 * @brief 注册串口对象
 * 
 * @return app_adapter_uart_status_e 运行状态
 */
app_adapter_uart_status_e app_adapter_uart_register(void);

/**
 * @brief 串口中断回调函数
 * 
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);                                         		



#endif

