/**
 * @file service_uart.h
 * @author ZB (2536566200@qq.com)
 * @brief 串口服务
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SERVICE_UART_H__
#define __SERVICE_UART_H__

#include <stdint.h>
#include "lwrb.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "main.h"

typedef enum {
    SERVICE_UART_STATUS_OK = 0, 
    SERVICE_UART_STATUS_ERROR,
} service_uart_status_e;

typedef enum {
    SERVICE_UART_HALF_EVENT = 0,    /**< 半满中断 */
    SERVICE_UART_FULL_EVENT,        /**< 全满中断 */
    SERVICE_UART_IDLE_EVENT,        /**< 空闲中断 */
} service_uart_event_e;

typedef enum {
    SERVICE_UART_ID_1 = 0,          /**< 串口1 */
    SERVICE_UART_ID_2,              /**< 串口2 */
} service_uart_id_e;

typedef struct {
    uint32_t id;                    /**< 串口ID */
    service_uart_event_e event;     /**< 串口中断事件 */
    void (*uart_cb)(void);          /**< 串口回调函数 */
    
    uint8_t buf[512];               /**< 串口接收缓冲区 */
    lwrb_t  rb;                     /**< 串口环形缓冲区句柄 */

    QueueHandle_t queue;            /**< 串口队列 */
} service_uart_param_t;

typedef struct {
    service_uart_event_e event;     /**< 串口中断事件 */
    service_uart_param_t *param;    /**< 串口参数指针 */
} service_uart_queue_t;

/**
 * @brief 串口服务初始化
 * 
 * @return service_uart_status_e 运行状态
 */
service_uart_status_e service_uart_init(void);

/**
 * @brief DMA半满中断回调函数
 * 
 * @param number_of_data 数据长度
 */
void service_uart_dma_half_irq_cal(lwrb_t *buff, uint32_t size);

/**
 * @brief DMA全满中断回调函数
 * 全满后直接把位置置为0
 * 如果需要计算整包长度还是得把now更新到head中不断累加
 * @param number_of_data 数据长度
 */
void service_uart_dma_comp_irq_cal(lwrb_t *buff, uint32_t size);

/**
 * @brief DMA空闲中断回调函数
 * 1.计算当前偏移量
 * @param number_of_data 数据长度
 */
void service_uart_idle_irq_cal(lwrb_t *buff, uint32_t size);

/**
 * @brief 串口处理函数
 * 
 * @param huart 串口句柄
 * @param size 字符大小
 */
void usart1_handler(UART_HandleTypeDef *huart, uint16_t size);

/**
 * @brief 串口线程
 * 
 * @param pvParameters 用户参数
 */
void service_uart_task(void *pvParameters);

/**
 * @brief 从中断中发送串口队列
 * 
 * @param queue 队列指针
 * @return service_uart_status_e 运行状态
 */
service_uart_status_e service_uart_send_irq_queue(service_uart_queue_t *queue);

/**
 * @brief 从队列中取出一个
 * 
 * @param queue 队列指针
 * @return service_uart_status_e 运行状态
 */
service_uart_status_e service_uart_recv_queue(service_uart_queue_t *queue, uint32_t timeout);


#endif
