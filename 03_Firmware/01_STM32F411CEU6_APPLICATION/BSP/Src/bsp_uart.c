/**
 * @file bsp_uart.c
 * @author ZB (2536566200@qq.com)
 * @brief 串口驱动
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_uart.h"
#include "main.h"

extern UART_HandleTypeDef huart1;

bsp_uart_status_e bsp_uart1_init(void)
{
    return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_deinit(void)
{
    return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_send(const uint8_t *data, uint32_t len, uint32_t timeout)
{
    if((data == NULL) || (len == 0)) {
        return BSP_UART_STATUS_ERROR;
    }

    HAL_UART_Transmit(&huart1, data, len, timeout);

    return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_recv(uint8_t *data, uint32_t len, uint32_t timeout)
{
    return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_sleep(void)
{
	return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_weakup(void)
{
	return BSP_UART_STATUS_OK;
}

bsp_uart_status_e bsp_uart1_start_dma_rx(uint8_t *buffer, uint32_t size)
{
    if(NULL == buffer) {
        return BSP_UART_STATUS_ERROR;
    }

    if(HAL_OK != HAL_UARTEx_ReceiveToIdle_DMA(&huart1, buffer, size))   
    {
        return BSP_UART_STATUS_ERROR;
    }

    return BSP_UART_STATUS_OK;
}







