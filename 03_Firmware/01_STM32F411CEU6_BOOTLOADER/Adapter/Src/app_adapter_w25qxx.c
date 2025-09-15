/**
 * @file app_adapter_w25qxx.c
 * @author ZB (2536566200@qq.com)
 * @brief w25qxx适配层
 * @version 0.1
 * @date 2025-09-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "app_adapter_w25qxx.h"

/**< w25q64驱动 */
static void _w25q64_init(const struct bsp_driver_flash_object *dev);
static void _w25q64_deinit(const struct bsp_driver_flash_object *dev);
static void _w25q64_erase(const struct bsp_driver_flash_object *dev,
                            uint32_t start_addr, 
                            uint32_t len);
static void _w25q64_write(const struct bsp_driver_flash_object *dev,
                            uint32_t start_addr,
                            const uint8_t *data,
                            uint32_t len);
static void _w25q64_read(const struct bsp_driver_flash_object *dev,
                            uint32_t start_addr,
                            uint8_t *data,
                            uint32_t len);


app_adapter_w25qxx_status_e app_adapter_w25qxx_register(void)
{
    /**< 1.注册w25q64设备到驱动层 */
    bsp_driver_flash_object_t _w25q64_dev = {
        .index              = 1,
        .user_data          = NULL,
        .pf_flash_init      = _w25q64_init,
        .pf_flash_deinit    = _w25q64_deinit,
        .pf_flash_erase     = _w25q64_erase,
        .pf_flash_write     = _w25q64_write,
        .pf_flash_read      = _w25q64_read,
    };

    bsp_driver_flash_register(1, &_w25q64_dev);

    return W25QXX_ADAPTER_OK;
}

static void _w25q64_init(const struct bsp_driver_flash_object *dev)
{
    if(dev == NULL) {
        return;
    }

    /**< 1.初始化QSPI接口 */

    /**< 2.初始化W25Q64 */

    return ;
}

static void _w25q64_deinit(const struct bsp_driver_flash_object *dev)
{
    if(dev == NULL) {
        return;
    }

    return ;
}

static void _w25q64_erase(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr, 
                            uint32_t len)
{
    if((dev == NULL) ||
        (start_addr + len > 0x800000) ||
        (len == 0)) {
        return ;
    }




    return ;
}

static void _w25q64_write(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr,
                            const uint8_t *data,
                            uint32_t len)
{
    if((dev == NULL) ||   
        (data == NULL) ||
        (start_addr + len > 0x800000) ||
        (len == 0)) { 
        return ;
    }

    return ;
}

static void _w25q64_read(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr,
                            uint8_t *data,
                            uint32_t len)
{
    if((dev == NULL) || 
        (data == NULL)) {
        return;
    }

    return ;
}




