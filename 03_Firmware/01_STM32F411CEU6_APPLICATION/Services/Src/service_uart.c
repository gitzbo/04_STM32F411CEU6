/**
 * @file service_uart.c
 * @author ZB (2536566200@qq.com)
 * @brief 串口服务
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "service_uart.h"
#include "main.h"
#include "bsp_uart.h"
#include "adapter_uart.h"

static service_uart_param_t _g_service_uart_param = {0};

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1) {
  
    }
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t size)
{
    if(huart->Instance == USART1) {
        usart1_handler(huart, size);
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_PE))!=RESET) {
        __HAL_UNLOCK(huart);
        __HAL_UART_CLEAR_PEFLAG(huart);
    }
    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE))!=RESET) {
        __HAL_UNLOCK(huart);
        __HAL_UART_CLEAR_FEFLAG(huart);
    }
    
    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_NE))!=RESET) {
        __HAL_UNLOCK(huart);
        __HAL_UART_CLEAR_NEFLAG(huart);
    }       
    
    if((__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE))!=RESET) {
        __HAL_UNLOCK(huart);
        __HAL_UART_CLEAR_OREFLAG(huart);
    }
 
    if(huart->Instance == USART1) {
        _g_service_uart_param.rb.r_ptr = 0;
        _g_service_uart_param.rb.w_ptr = 0;

        adapter_uart_object_t uart1_obj;
        adapter_uart_get_object(0, &uart1_obj);
        adapter_uart_init(&uart1_obj);
    }
}

service_uart_status_e service_uart_init(void)
{
    /**< 1.注册串口1缓冲区 */
    lwrb_init(&_g_service_uart_param.rb, _g_service_uart_param.buf, sizeof(_g_service_uart_param.buf));
    if(0 == lwrb_is_ready(&_g_service_uart_param.rb)) {
        return SERVICE_UART_STATUS_ERROR;
    }
    _g_service_uart_param.uart_cb   = NULL;
    _g_service_uart_param.id        = SERVICE_UART_ID_1;

    /**< 2.将串口注册到对象 */
    adapter_uart_object_t uart1_obj = {
        .pf_uart_init           = (adapter_uart_status_e (*)(void))bsp_uart1_init,
        .pf_uart_deinit         = (adapter_uart_status_e (*)(void))bsp_uart1_deinit,
        .pf_uart_recv           = (adapter_uart_status_e (*)(uint8_t *, uint32_t , uint32_t))bsp_uart1_recv,
        .pf_uart_send           = (adapter_uart_status_e (*)(const uint8_t *, uint32_t , uint32_t))bsp_uart1_send,
        .pf_uart_sleep          = (adapter_uart_status_e (*)(void))bsp_uart1_sleep,
        .pf_uart_weakup         = (adapter_uart_status_e (*)(void))bsp_uart1_weakup,
        .pf_uart_start_dma_rx   = (adapter_uart_status_e (*)(uint8_t *, uint32_t))bsp_uart1_start_dma_rx,
    };
    adapter_uart_register(0, &uart1_obj);

    /**< 3.初始化串口 */
    adapter_uart_init(&uart1_obj);
    adapter_uart_start_dma_rx(&uart1_obj, _g_service_uart_param.buf, sizeof(_g_service_uart_param.buf));

    /**< 4.创建串口线程 */
    if (pdPASS != xTaskCreate(service_uart_task,          // 任务函数指针
                              "uart_task",                // 任务名称（调试用）
                              2048,                       // 任务栈大小
                              NULL,                       // 任务参数
                              27,                         // 任务优先级
                              NULL)) {                    // 任务句柄指针
        return SERVICE_UART_STATUS_ERROR;
    }

    /**< 5.创建串口信号量 */
    _g_service_uart_param.queue = xQueueCreate(10, sizeof(service_uart_queue_t));
    if(NULL == _g_service_uart_param.queue) {
        return SERVICE_UART_STATUS_ERROR;
    }

    /**< 6.将串口线程加入到守护线程中 */
    
    
    return SERVICE_UART_STATUS_OK;
}

void service_uart_dma_half_irq_cal(lwrb_t *buff, uint32_t size)
{
    /* 比如,当前缓冲区长度为10（0~9)，head当前位置为32，
        产生半满说明数据已经到达4，于是32%5 = 2，
        所以将head添加到34即可（因为0~4中，它在2的位置，所以+2就到34）。*/
    uint32_t head       = buff->w_ptr;                                              
    uint32_t now_head   = ((buff->size / 2)) - (head % ((buff->size / 2))) + head;  
    buff->w_ptr         = now_head;                                                 
}

void service_uart_dma_comp_irq_cal(lwrb_t *buff, uint32_t size)
{
    /* 比如,当前缓冲区长度为10（0~9)，head当前位置为37，
    产生全满说明数据已经到达4，于是37%10 = 7，
    将head添加到39即可（因为0~9中，它在7的位置，所以+2就到39）。 */
    uint32_t head       = buff->w_ptr;                                        
    uint32_t now_head   = ((buff->size) - (head % (buff->size))) + head;      
    buff->w_ptr         = now_head % buff->size;                              
} 

void service_uart_idle_irq_cal(lwrb_t *buff, uint32_t size)
{
    /* 比如,当前缓冲区长度为10（0~9)，head当前位置为35，
    产生空闲中断得到的size数据为9,于是需要增加(9-1)-(35%10)= 3，
    将head添加到38即可。*/ 
    uint32_t head       = buff->w_ptr;
    uint32_t now_head   = 0;
	if((size) < (head % buff->size)) {
        now_head = (size + buff->size) - (head % buff->size) + head;
    }
    else {
        now_head = (size - (head % buff->size)) + head;
    }
    buff->w_ptr         = now_head;
}

void usart1_handler(UART_HandleTypeDef *huart, uint16_t size)
{
    /* 1.半满中断 */
    if(huart->RxEventType == HAL_UART_RXEVENT_HT) {
        service_uart_dma_half_irq_cal(&_g_service_uart_param.rb, size);
        _g_service_uart_param.event = SERVICE_UART_HALF_EVENT;
    }

    /* 2.全满中断 */
    else if(huart->RxEventType == HAL_UART_RXEVENT_TC) {
        service_uart_dma_comp_irq_cal(&_g_service_uart_param.rb, size);
        _g_service_uart_param.event = SERVICE_UART_FULL_EVENT;
    }

    /* 3.空闲中断 */
    else if(huart->RxEventType == HAL_UART_RXEVENT_IDLE) {
        service_uart_idle_irq_cal(&_g_service_uart_param.rb, size);
        _g_service_uart_param.event = SERVICE_UART_IDLE_EVENT;
    }
    
    _g_service_uart_param.id = SERVICE_UART_ID_1;
    
    /* 4.线程通知流程 */
    if((NULL != _g_service_uart_param.uart_cb) && 
       (_g_service_uart_param.event == SERVICE_UART_IDLE_EVENT)) {
        _g_service_uart_param.uart_cb();
    }
}

void service_uart_task(void *pvParameters)
{
    service_uart_queue_t uart_queue = {0};

    for(;;) {
        if(SERVICE_UART_STATUS_OK == service_uart_recv_queue(&uart_queue, 1000)) {

        }
    }
}

service_uart_status_e service_uart_send_irq_queue(service_uart_queue_t *queue)
{
    if(queue == NULL) {
        return SERVICE_UART_STATUS_ERROR;
    }

    if(pdTRUE != xQueueSendFromISR(_g_service_uart_param.queue, queue, NULL)) {
       return SERVICE_UART_STATUS_ERROR;
    }

    return SERVICE_UART_STATUS_OK;
}

service_uart_status_e service_uart_recv_queue(service_uart_queue_t *queue, uint32_t timeout)
{
    if(queue == NULL) {
        return SERVICE_UART_STATUS_ERROR;
    }

    if(pdTRUE != xQueueReceive(_g_service_uart_param.queue, queue, timeout)) {
        return SERVICE_UART_STATUS_ERROR;
    }

    return SERVICE_UART_STATUS_OK;
}

service_uart_status_e service_uart_read_at(void)
{
	/**< 1.检查是否有数据 */
	uint32_t available = lwrb_get_full(&_g_service_uart_param.rb);
    if(available == 0) {
        return SERVICE_UART_STATUS_ERROR;
    }
	
    /**< 2.临时缓冲区用于查找完整帧 */
    char temp_buf[64] = {0};
    uint32_t to_peek = (available < sizeof(temp_buf) - 1) ? available : sizeof(temp_buf) - 1;
	
	// 查看数据而不消费
    lwrb_peek(&_g_service_uart_param.rb, 0, temp_buf, sizeof(temp_buf));
    temp_buf[to_peek] = '\0';

    /**< 3.查找帧头和帧尾 */
    char *frame_start = strstr(temp_buf, "AT+");
    if(frame_start == NULL) {
        // 没有找到帧头，丢弃一些数据继续查找
        lwrb_read(&_g_service_uart_param.rb, temp_buf, 1);
        return SERVICE_UART_STATUS_ERROR;
    }

    char *frame_end = strstr(frame_start, "\r\n");
    if(frame_end == NULL) {
        // 找到帧头但没有完整帧尾，等待更多数据
        return SERVICE_UART_STATUS_ERROR;
    }	
	
	/**< 4.计算完整帧长度并读取 */
    uint32_t frame_length = frame_end - frame_start + 2; // 包含\r\n
    char frame_buf[32] = {0};
    if(frame_length >= sizeof(frame_buf)) {
        return SERVICE_UART_STATUS_ERROR;
    }

    // 消费掉帧头之前的数据
    uint32_t bytes_to_skip = frame_start - temp_buf;
    if(bytes_to_skip > 0) {
        lwrb_read(&_g_service_uart_param.rb, temp_buf, bytes_to_skip);
    }

	// 读取完整帧
    if(lwrb_read(&_g_service_uart_param.rb, frame_buf, frame_length) != frame_length) {
        return SERVICE_UART_STATUS_ERROR;
    }

    /**< 5.进行指令查表 */
    
    

    return SERVICE_UART_STATUS_OK;
}


