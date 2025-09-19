/**
 * @file bsp_driver_uart.c
 * @author ZB (2536566200@qq.com)
 * @brief 串口驱动
 * @version 0.1
 * @date 2025-09-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_driver_uart.h"

static bsp_driver_uart_object_t _uart_dev[UART_DEV_MAX] = {0};    /**< 串口设备内存池 */

bsp_driver_uart_status_e bsp_driver_uart_register(uint32_t index, bsp_driver_uart_object_t *dev)
{
    if(dev == NULL) {
        return UART_DRIVER_ERROR;
    }

    _uart_dev[index].index          = dev->index;
    _uart_dev[index].user_data      = dev->user_data;
    _uart_dev[index].pf_uart_init   = dev->pf_uart_init;
    _uart_dev[index].pf_uart_deinit = dev->pf_uart_deinit;
    _uart_dev[index].pf_uart_send   = dev->pf_uart_send;
    _uart_dev[index].pf_uart_recv   = dev->pf_uart_recv;

    return UART_DRIVER_OK;
}

bsp_driver_uart_status_e bsp_driver_uart_get_object(uint32_t index, bsp_driver_uart_object_t *dev)
{
    if((dev == NULL) || (index >= UART_DEV_MAX)) {
        return UART_DRIVER_ERROR;
    }

    *dev = _uart_dev[index];

    return UART_DRIVER_OK;
}

bsp_driver_uart_status_e bsp_driver_uart_init(const bsp_driver_uart_object_t *dev)
{
    if((dev == NULL) || (dev->pf_uart_init == NULL)) {
        return UART_DRIVER_ERROR;
    }

    return dev->pf_uart_init(dev);
}

bsp_driver_uart_status_e bsp_driver_uart_deinit(const bsp_driver_uart_object_t *dev)
{
    if((dev == NULL) || (dev->pf_uart_deinit == NULL)) {
        return UART_DRIVER_ERROR;
    }
    
    return dev->pf_uart_deinit(dev);
}

bsp_driver_uart_status_e bsp_driver_uart_send(const bsp_driver_uart_object_t *dev, 
                                              const uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout)
{
    if((dev == NULL) || (dev->pf_uart_send == NULL)) {
        return UART_DRIVER_ERROR;
    }

    return dev->pf_uart_send(dev, data, len, timeout);
}

bsp_driver_uart_status_e bsp_driver_uart_recv(const bsp_driver_uart_object_t *dev, 
                                              uint8_t *data, 
                                              uint32_t len, 
                                              uint32_t timeout)
{
    if((dev == NULL) || (dev->pf_uart_recv == NULL)) {
        return UART_DRIVER_ERROR;
    }

    return dev->pf_uart_recv(dev, data, len, timeout);
}

bsp_driver_uart_status_e bsp_driver_uart_sleep(const bsp_driver_uart_object_t *dev)
{
    if((dev == NULL) || (dev->pf_uart_sleep == NULL)) {
        return UART_DRIVER_ERROR;
    }

    return dev->pf_uart_sleep(dev);
}

bsp_driver_uart_status_e bsp_driver_uart_weakup(const bsp_driver_uart_object_t *dev)
{
    if((dev == NULL) || (dev->pf_uart_weakup == NULL)) {
        return UART_DRIVER_ERROR;
    }

    return dev->pf_uart_weakup(dev);
}




