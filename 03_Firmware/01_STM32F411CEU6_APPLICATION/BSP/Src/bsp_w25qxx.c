/**
 * @file bsp_w25qxx.c
 * @author ZB (2536566200@qq.com)
 * @brief w25qxx驱动
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_w25qxx.h"
#include <stddef.h>

bsp_w25qxx_status_e bsp_w25qxx_init(void)
{
    return BSP_W25QXX_STATUS_OK;
}

bsp_w25qxx_status_e bsp_w25qxx_deinit(void)
{
    return BSP_W25QXX_STATUS_OK;
}

bsp_w25qxx_status_e bsp_w25qxx_erase(uint32_t start_addr, uint32_t len)
{
    if((start_addr + len > 0x800000) || (len == 0)) {
        return BSP_W25QXX_STATUS_ERROR;
    }
    
    return BSP_W25QXX_STATUS_OK;
}

bsp_w25qxx_status_e bsp_w25qxx_write(uint32_t start_addr, const uint8_t *data, uint32_t len)
{
    if((data == NULL) || (start_addr + len > 0x800000) || (len == 0)) { 
        return BSP_W25QXX_STATUS_ERROR;
    }

    return BSP_W25QXX_STATUS_OK;
}

bsp_w25qxx_status_e bsp_w25qxx_read(uint32_t start_addr, uint8_t *data, uint32_t len)
{
    if((data == NULL) || (start_addr > 0x800000)) {
        return BSP_W25QXX_STATUS_ERROR;
    }

    return BSP_W25QXX_STATUS_OK;
}







