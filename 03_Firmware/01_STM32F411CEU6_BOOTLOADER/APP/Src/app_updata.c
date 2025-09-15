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

        /* 1.3 初始化APP堆栈指针 */
        __set_MSP(*(__IO uint32_t *)APP1_START_ADDR);

        /* 1.4 类型转换 */
        jump_to_applictaion = (pfunction)jump_address;

        /* 1.5 跳转到APP */
        jump_to_applictaion();
    }
}

uint32_t app_updata_crc32(uint32_t addr, uint32_t size)
{
  uint32_t i;
  uint32_t data;
  uint32_t crc = 0xFFFFFFFF;
  uint32_t session_done = 0;
  uint32_t file_done = 0;

  for (i = 0; i < size; i++) {
    data = *(uint8_t*)(addr + i);
    crc ^= data;
    for (data = 0; data < 8; data++) {
      if (crc & 1) {
        crc = (crc >> 1) ^ 0xEDB88320;
      }
      else {
        crc >>= 1;
      }
      if (session_done != 0) {
        break;
      }
      if (file_done != 0) {
        break;
      }
    }

    if (session_done != 0) {
      break;
    }
  }

  return ~crc;
}







