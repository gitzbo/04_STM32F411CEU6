/**
 * @file bsp_u8g2.c
 * @author ZB (2536566200@qq.com)
 * @brief u8g2驱动
 * @version 0.1
 * @date 2025-11-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_u8g2.h"
#include "main.h"
//#include "u8g2.h"

//extern I2C_HandleTypeDef hi2c1;                                         /**< i2c句柄 */
//extern DMA_HandleTypeDef hdma_i2c1_tx;                                  /**< i2c dma句柄 */

//static uint8_t _u8x8_byte_hw_i2c(u8x8_t *u8x8, 
//                                    uint8_t msg, 
//                                    uint8_t arg_int, 
//                                    void *arg_ptr)
//{
//	static uint8_t buffer[32];	
//	static uint8_t buf_idx;
//	uint8_t *data;

//	switch(msg){
//		case U8X8_MSG_BYTE_SEND: {
//			data = (uint8_t *)arg_ptr;      
//			while( arg_int > 0 ){
//				buffer[buf_idx++] = *data;
//				data++;
//				arg_int--;
//			}
//			break;
//		}
//		case U8X8_MSG_BYTE_INIT: {
//			/* add your custom code to init i2c subsystem */
//			break;
//		}
//		case U8X8_MSG_BYTE_START_TRANSFER: {
//			buf_idx = 0;
//			break;
//		}
//		case U8X8_MSG_BYTE_END_TRANSFER: {
//			HAL_I2C_Master_Transmit(&hi2c1, u8x8_GetI2CAddress(u8x8), buffer, buf_idx, 1000);
//			break;
//		}
//		default: {
//			return 0;
//		}
//	}
//	return 1;
//}

//static uint8_t _u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, 
//                                            U8X8_UNUSED uint8_t msg, 
//                                            U8X8_UNUSED uint8_t arg_int, 
//                                            U8X8_UNUSED void *arg_ptr)
//{
//	switch(msg){
//		case U8X8_MSG_GPIO_AND_DELAY_INIT: {
//			break;
//		}
//		case U8X8_MSG_DELAY_MILLI: {
//			HAL_Delay(arg_int);
//			break;
//		}
//		case U8X8_MSG_GPIO_I2C_CLOCK: {		
//			break;
//		}
//		case U8X8_MSG_GPIO_I2C_DATA: {			
//			break;
//		}
//		default: {
//			return 0;
//		}
//	}

//	return 1;
//}

//bsp_u8g2_status_e bsp_u8g2_init(void)
//{



//    return BSP_U8G2_STATUS_OK;
//}








