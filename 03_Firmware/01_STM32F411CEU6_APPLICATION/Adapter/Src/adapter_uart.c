/**
 * @file adapter_uart.c
 * @author ZB (2536566200@qq.com)
 * @brief UART适配层
 * @version 0.1
 * @date 2025-09-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_uart.h"

static adapter_uart_object_t _uart_dev[UART_DEV_MAX] = {0};    /**< 串口设备内存池 */

adapter_uart_status_e adapter_uart_register(uint32_t index, adapter_uart_object_t *dev)
{
    if(dev == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    _uart_dev[index].index          = dev->index;
    _uart_dev[index].user_data      = dev->user_data;
    _uart_dev[index].pf_uart_init   = dev->pf_uart_init;
    _uart_dev[index].pf_uart_deinit = dev->pf_uart_deinit;
    _uart_dev[index].pf_uart_send   = dev->pf_uart_send;
    _uart_dev[index].pf_uart_recv   = dev->pf_uart_recv;

    return ADAPTER_UART_STATUS_OK;
}

adapter_uart_status_e adapter_uart_get_object(uint32_t index, adapter_uart_object_t *dev)
{
    if((dev == NULL) || (index >= UART_DEV_MAX)) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    *dev = _uart_dev[index];

    return ADAPTER_UART_STATUS_OK;
}

adapter_uart_status_e adapter_uart_init(const adapter_uart_object_t *dev)
{
    if(dev->pf_uart_init == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    return dev->pf_uart_init();
}

adapter_uart_status_e adapter_uart_deinit(const adapter_uart_object_t *dev)
{
    if(dev->pf_uart_deinit == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }
    
    return dev->pf_uart_deinit();
}

adapter_uart_status_e adapter_uart_send(const adapter_uart_object_t *dev, const uint8_t *data, uint32_t len, uint32_t timeout)
{
    if(dev->pf_uart_send == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    return dev->pf_uart_send(data, len, timeout);
}

adapter_uart_status_e adapter_uart_recv(const adapter_uart_object_t *dev, uint8_t *data, uint32_t len, uint32_t timeout)
{
    if(dev->pf_uart_recv == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    return dev->pf_uart_recv(data, len, timeout);
}

adapter_uart_status_e adapter_uart_sleep(const adapter_uart_object_t *dev)
{
    if(dev->pf_uart_sleep == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    return dev->pf_uart_sleep();
}

adapter_uart_status_e adapter_uart_weakup(const adapter_uart_object_t *dev)
{
    if(dev->pf_uart_weakup == NULL) {
        return ADAPTER_UART_STATUS_ERROR;
    }

    return dev->pf_uart_weakup();
}










