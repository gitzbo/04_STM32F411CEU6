/**
 * @file app_updata.c
 * @author ZB (2536566200@qq.com)
 * @brief 应用升级
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "app_updata.h"

/**< static */
static void _app_updata_app2(void);				/**< APP2分区升级函数 */
static uint8_t _g_ymodel_rx_buffer[1028];		/**< YMODEL协议buffer */

/**< 升级协议表驱动 */
static app_updata_cmd_t _g_updata_cmd[3] = {
	{UPDATA_APP2, _app_updata_app2},
};

void app_updata_force(void)
{
    /**< 1.发送是否进行升级命令 */
    bsp_driver_uart_object_t uart1_obj = {0};
    bsp_driver_uart_get_object(0, &uart1_obj);
	app_updata_force_t send_cmd = {
		.head = UPDATA_HEAD,
		.len	= 0x08,
		.cmd	= UPDATA_QUERY,
		.tail = UPDATA_TAIL,
	};
	send_cmd.crc = app_updata_crc32(&send_cmd, 3);
	bsp_driver_uart_send(&uart1_obj, 
						(uint8_t *)&send_cmd, 
						sizeof(send_cmd), 
						sizeof(send_cmd));									/**< 查询是否进行升级 */
    
    /**< 2.判断是否进行强制升级 */
	uint8_t data[8] = {0};
    bsp_driver_uart_recv(&uart1_obj, data, 8, 1000);						/**< 等待1s判断是否进行强制升级 */
	
    /**< 3.调用YMODEL对目标区域进行强制升级 */
	for(uint32_t i = 0; i < UPDATA_MAX; i++) {
		if(data[2] == _g_updata_cmd[i].cmd) {
			if(_g_updata_cmd[i].updata_cb != NULL) {
				_g_updata_cmd[i].updata_cb();
			}
		}
	}
}

void app_updata_general(void)
{
	
}

void app_updata_jump_app(void)
{
    uint32_t jump_address;
    pfunction jump_to_applictaion;

    /* 1.检查栈顶地址是否合法 */
    if(((*(__IO uint32_t *)APP1_START_ADDR) & 0x2FFD0000) == 0x20000000) {
        /* 1.1 屏蔽所有中断，防止在跳转过程中，中断干扰出现异常 */
        __disable_irq();

        /* 1.2 用户代码区第二个字为程序开始地址(复位地址/MSP起始地址) */
        jump_address = *(__IO uint32_t *)(APP1_START_ADDR + 4);

        /* 1.3 设置主堆栈指针 */
        __set_MSP(*(__IO uint32_t *)APP1_START_ADDR);

        /* 1.4 类型转换 */
        jump_to_applictaion = (pfunction)jump_address;

        /* 1.5 跳转到APP */
        jump_to_applictaion();
    }
}

uint32_t app_updata_crc32(void *addr, uint32_t size)
{
	uint32_t i;
	uint32_t data;
	uint32_t crc = 0xFFFFFFFF;
	uint8_t *byte_ptr = (uint8_t *)addr;
	
	for (i = 0; i < size; i++) {
		data = byte_ptr[i];
		crc ^= data;
		
		for (data = 0; data < 8; data++) {
			if (crc & 1) {
				crc = (crc >> 1) ^ 0xEDB88320;
			}
			else {
				crc >>= 1;
			}
		}
	}

  return ~crc;
}

uint32_t app_updata_flash_crc32(uint32_t flash_start, uint32_t flash_size)
{
    uint32_t crc = 0xFFFFFFFF;
    uint32_t i = 0;
	uint8_t data = 0;	
	bsp_driver_flash_object_t flash1_obj = {0};
	bsp_driver_flash_get_object(0, &flash1_obj);
	
    for (i = 0; i < flash_size; i++) {
        bsp_driver_flash_read(&flash1_obj, (flash_start + i), &data, 1);
        
        crc ^= data;
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    
    return ~crc;
}


static void _app_updata_app2(void)
{
	/**< 1.调用YMODEL协议，将数据写入到APP2分区中  */
	app_ymodem_receive(APP2_START_ADDR, _g_ymodel_rx_buffer);
}


