/**
 * @file adapter_u8g2.c
 * @author ZB (2536566200@qq.com)
 * @brief u8g2适配层
 * @version 0.1
 * @date 2025-09-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_u8g2.h"

//static u8g2_t _g_u8g2_obj[U8G2_OBJ_MAX];

//adapter_u8g2_status_e adapter_u8g2_register(void)
//{
//	/**< 1.初始化UI库 */			
//	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&_g_u8g2_obj[0], 				/**< u8g2对象 */
//											U8G2_R0, 						/**< 旋转方向 */
//											u8x8_byte_hw_i2c,				/**< 使用硬件iic */
//											u8g2_gpio_and_delay_stm32);		/**< 延时与操作函数 */

//    u8g2_InitDisplay(&_g_u8g2_obj[0]);                                      /**< 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态 */ 
//    u8g2_SetPowerSave(&_g_u8g2_obj[0], 0);                                  /**< 打开显示器 */ 
//    u8g2_ClearBuffer(&_g_u8g2_obj[0]);

//    return U8G2_ADAPTER_OK;
//}

//adapter_u8g2_status_e adapter_u8g2_get_object(uint32_t index, u8g2_t *obj)
//{
//    if(obj == NULL) {
//        return U8G2_ADAPTER_ERROR;
//    }

//    *obj = _g_u8g2_obj[index];

//    return U8G2_ADAPTER_OK;
//}

//adapter_u8g2_status_e adapter_u8g2_delete_object(u8g2_t *obj)
//{
//    if(obj == NULL) {
//        return U8G2_ADAPTER_ERROR;
//    }

//    return U8G2_ADAPTER_OK;
//}