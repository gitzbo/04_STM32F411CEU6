/**
 * @file app_adapter_uart.c
 * @author ZB (2536566200@qq.com)
 * @brief UART适配层
 * @version 0.1
 * @date 2025-09-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_adapter_uart.h"

extern UART_HandleTypeDef huart1;

/**< static */
static bsp_driver_uart_status_e _app_adapter_uart1_init(const bsp_driver_uart_object_t *dev);           /**< 串口1初始化函数 */
static bsp_driver_uart_status_e _app_adapter_uart1_deinit(const bsp_driver_uart_object_t *dev);         /**< 串口1逆初始化函数 */
static bsp_driver_uart_status_e _app_adapter_uart1_send(const bsp_driver_uart_object_t *dev, 
                                                            const uint8_t *data, 
                                                            uint32_t len, 
                                                            uint32_t timeout);                          /**< 串口1发送函数 */
static bsp_driver_uart_status_e _app_adapter_uart1_recv(const bsp_driver_uart_object_t *dev, 
                                                            uint8_t *data,
                                                            uint32_t len,
                                                            uint32_t timeout);                          /**< 串口1接收函数 */
static bsp_driver_uart_status_e _app_adapter_uart1_sleep(const bsp_driver_uart_object_t *dev);          /**< 串口1休眠函数 */
static bsp_driver_uart_status_e _app_adapter_uart1_weakup(const bsp_driver_uart_object_t *dev);         /**< 串口1唤醒函数 */
static uint8_t _g_uart1_char[1] = {0};																	/**< 串口1接收字符缓存 */
static uint8_t _g_uart1_buf[UART1_BUFFER_SIZE] = {0};                                                   /**< 串口1缓冲区内存池 */
static lwrb_t _g_uart1_rb = {0};                                                                        /**< 串口1环形缓冲区结构体 */

/**< func */
app_adapter_uart_status_e app_adapter_uart_register(void)
{
    bsp_driver_uart_object_t uart1 = {
        .index     = 0, 
        .user_data = NULL,
        .pf_uart_init   = _app_adapter_uart1_init,    
        .pf_uart_deinit = _app_adapter_uart1_deinit,    
        .pf_uart_send   = _app_adapter_uart1_send,    
        .pf_uart_recv   = _app_adapter_uart1_recv,    
        .pf_uart_sleep  = _app_adapter_uart1_sleep,    
        .pf_uart_weakup = _app_adapter_uart1_weakup,    
    };

    bsp_driver_uart_register(0, &uart1);                        /**< 目标对象初始化 */

    return UART_ADAPTER_OK;
}

static bsp_driver_uart_status_e _app_adapter_uart1_init(const bsp_driver_uart_object_t *dev)
{
    if(dev == NULL) {
        return UART_DRIVER_ERROR;
    }

    /**< 1.初始化串口1的GPIO */
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin         = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull        = GPIO_NOPULL;
    GPIO_InitStruct.Speed       = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate   = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /**< 2.初始化串口1外设 */
    huart1.Instance             = USART1;
    huart1.Init.BaudRate        = 9600;
    huart1.Init.WordLength      = UART_WORDLENGTH_8B;
    huart1.Init.StopBits        = UART_STOPBITS_1;
    huart1.Init.Parity          = UART_PARITY_NONE;
    huart1.Init.Mode            = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl       = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling    = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
	
	/**< 3.配置中断 */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_UART_Receive_IT(&huart1, _g_uart1_char, 1);
	
    /**< 3.初始化串口1的环形缓冲区 */
    lwrb_init(&_g_uart1_rb, _g_uart1_buf, UART1_BUFFER_SIZE);

    return UART_DRIVER_OK;
}

static bsp_driver_uart_status_e _app_adapter_uart1_deinit(const bsp_driver_uart_object_t *dev)
{
    if(dev == NULL) {
        return UART_DRIVER_ERROR;
    }

    return UART_DRIVER_OK;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1) {
		lwrb_write(&_g_uart1_rb, _g_uart1_char, 1);                       /**< 将数据写入到fifo中 */ 
        HAL_UART_Receive_IT(&huart1, _g_uart1_char, 1);                   /**< 接收一位数据 */
    }
}

static bsp_driver_uart_status_e _app_adapter_uart1_send(const bsp_driver_uart_object_t *dev, 
                                                            const uint8_t *data, 
                                                            uint32_t len, 
                                                            uint32_t timeout)
{
    if((dev == NULL) || (data == NULL) || (len == 0)) {
        return UART_DRIVER_ERROR;
    }

    /**< 1.直接调用发送函数进行同步发送 */
    /**< 待优化：这里可以优化为写入环形缓冲区中，然后在主循环中进行异步发送 */
    HAL_UART_Transmit(&huart1, data, len, timeout);         
    
    return UART_DRIVER_OK;    
}

static bsp_driver_uart_status_e _app_adapter_uart1_recv(const bsp_driver_uart_object_t *dev, 
                                                            uint8_t *data,
                                                            uint32_t len,
                                                            uint32_t timeout)
{
    if((dev == NULL) || (data == NULL) || (len == 0)) {
        return UART_DRIVER_ERROR;
    }

    /**< 1.获取开始时间 */
    uint32_t start_time = HAL_GetTick();

    /**< 2.获取可用空间 */
    uint32_t bytes_read = 0;
    while (bytes_read < len) {
        uint32_t bytes_available = lwrb_get_full(&_g_uart1_rb);             /**< 获取环形缓冲区中可读字节数 */ 
        if (bytes_available > 0) {
            /**< 计算本次读取的字节数：最少为（可用字节数）和（剩余需要读取的字节数）的较小值 */ 
            uint32_t to_read = (bytes_available < (len - bytes_read)) ? bytes_available : (len - bytes_read);
            uint32_t read = lwrb_read(&_g_uart1_rb, data + bytes_read, to_read);
            bytes_read += read;
        }
        else {
            /**< 如果没有数据，检查是否超时 */ 
            if (HAL_GetTick() - start_time >= timeout) {
                return UART_DRIVER_TIMEOUT;
            }
            // 这里可以添加一个延时以避免忙等待，或者让出CPU，具体取决于操作系统环境
            // 例如，如果是在操作系统中，可以使用任务延时函数；如果是裸机，可以适当延时或直接循环
            // 由于是裸机，我们可能不需要延时，因为我们需要尽快再次检查缓冲区
            // 但是为了避免高速循环，可以加入一个小的延时，比如1ms，具体取决于系统
            // HAL_Delay(1);
        }
    }

    return UART_DRIVER_OK;
}


static bsp_driver_uart_status_e _app_adapter_uart1_sleep(const bsp_driver_uart_object_t *dev)
{
	if(dev == NULL) {
		return UART_DRIVER_ERROR;
	}
	

	return UART_DRIVER_OK;
}

static bsp_driver_uart_status_e _app_adapter_uart1_weakup(const bsp_driver_uart_object_t *dev)
{
	if(dev == NULL) {
		return UART_DRIVER_ERROR;
	}

	return UART_DRIVER_OK;
}








