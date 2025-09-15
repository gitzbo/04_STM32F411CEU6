/**
 * @file app_adapter_flash.c
 * @author ZB (2536566200@qq.com)
 * @brief flash适配层
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "app_adapter_flash.h"

/**< 内部flash驱动 */
static void _in_flash_init(const struct bsp_driver_flash_object *dev);
static void _in_flash_deinit(const struct bsp_driver_flash_object *dev);
static void _in_flash_erase(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr, 
                            uint32_t len);
static void _in_flash_write(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr,
                            const uint8_t *data,
                            uint32_t len);
static void _in_flash_read(const struct bsp_driver_flash_object *dev, 
							uint32_t start_addr,
							uint8_t *data,
							uint32_t len);

app_adapter_flash_status_e app_adapter_flash_register(void)
{
    /**< 1.注册内部flash操作到驱动中 */
    bsp_driver_flash_object_t _in_flash_dev = {
        .index              = 0,
        .user_data          = NULL,
        .pf_flash_init      = _in_flash_init,
        .pf_flash_deinit    = _in_flash_deinit,
        .pf_flash_erase     = _in_flash_erase,
        .pf_flash_write     = _in_flash_write,
        .pf_flash_read      = _in_flash_read,
    };
    bsp_driver_flash_register(0, &_in_flash_dev);

    return FLASH_ADAPTER_OK;
}

static void _in_flash_init(const struct bsp_driver_flash_object *dev)
{
    if(dev == NULL) {
        return;
    }
    
    return ;
}

static void _in_flash_deinit(const struct bsp_driver_flash_object *dev)
{
    if(dev == NULL) {
        return;
    }

    return ;
}

static void _in_flash_erase(const struct bsp_driver_flash_object *dev, 
                            uint32_t start_addr, 
                            uint32_t len)
{
    uint32_t PageError = 0;
    uint8_t sector = 0, number_of_sectors = 0;

    if((dev == NULL) 								|| /**< 判断对象是否正确 	*/
        (start_addr < FLASH_START_ADDRESS) 			|| /**< 判断地址是否越界 	*/
        ((start_addr + len) > FLASH_END_ADDRESS) 	|| /**< 判断地址是否越界 	*/
        (len == 0)) {                                  /**< 判断写入长度 		*/
        return ;                                       
    }
    
    /**< 1.内部flash解锁 */
    HAL_FLASH_Unlock();

    /**< 2.1擦除页起始位置计算 */
    if(start_addr < FLASH_SECTOR0_ADDR) {
        sector = FLASH_SECTOR_0;
    }
    else if(start_addr < FLASH_SECTOR1_ADDR) {
        sector = FLASH_SECTOR_1;
    }
    else if(start_addr < FLASH_SECTOR2_ADDR) {
        sector = FLASH_SECTOR_2;
    }
    else if(start_addr < FLASH_SECTOR3_ADDR) {
        sector = FLASH_SECTOR_3;
    }
    else if(start_addr < FLASH_SECTOR4_ADDR) {
        sector = FLASH_SECTOR_4;
    }
    else if(start_addr < FLASH_SECTOR5_ADDR) {
        sector = FLASH_SECTOR_5;
    }
    else if(start_addr < FLASH_SECTOR6_ADDR) {
        sector = FLASH_SECTOR_6;
    }
    else if(start_addr < FLASH_SECTOR7_ADDR) {
        sector = FLASH_SECTOR_7;
    }

    /**< 2.2擦除扇区数计算 */
    if((start_addr + len) <= FLASH_SECTOR1_ADDR) {
        number_of_sectors = FLASH_SECTOR_1 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR2_ADDR) {
        number_of_sectors = FLASH_SECTOR_2 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR3_ADDR) {
        number_of_sectors = FLASH_SECTOR_3 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR4_ADDR) {
        number_of_sectors = FLASH_SECTOR_4 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR5_ADDR) {
        number_of_sectors = FLASH_SECTOR_5 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR6_ADDR) {
        number_of_sectors = FLASH_SECTOR_6 - sector + 1;
    }
    else if((start_addr + len) <= FLASH_SECTOR7_ADDR) {
        number_of_sectors = FLASH_SECTOR_7 - sector + 1;
    }
	
    /**< 3.进行擦除操作 */
    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase       = FLASH_TYPEERASE_SECTORS;                                                                          /**< 扇区擦除 */
    EraseInitStruct.VoltageRange    = FLASH_VOLTAGE_RANGE_3;                                                                            /**< 电压范围2.7V to 3.6V */
    EraseInitStruct.Sector          = sector;                                                                                           /**< 起始扇区 */
    EraseInitStruct.NbSectors       = number_of_sectors;                                                                                /**< 擦除扇区数 */
    EraseInitStruct.Banks           = FLASH_BANK_1;                                                                                     /**< 仅支持单bank */
    if(HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK) {
        HAL_FLASH_Lock();
        return ;
    }
    
    /**< 4.内部flash上锁 */
    HAL_FLASH_Lock();

    return ;
}

static void _in_flash_write(const struct bsp_driver_flash_object *dev, 
							uint32_t start_addr,
							const uint8_t *data,
							uint32_t len)
{
    if((dev == NULL) 							 || /**< 判断对象是否正确 	*/
        (data == NULL) 							 || /**< 判断数据是否正确 	*/
        ((start_addr + len) > FLASH_END_ADDRESS) || /**< 判断地址是否越界 	*/
        (start_addr < FLASH_START_ADDRESS) 		 ||	/**< 判断地址是否越界 	*/
		(len == 0)) {       						/**< 判断写入长度 		*/
        return ;
    }

    /**< 1.内部flash进行解锁 */
    HAL_FLASH_Unlock();

    /**< 2.将数据写入内部flash */
    for(uint32_t i = 0; i < len; i++) {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, start_addr + i, data[i]) != HAL_OK) {
            /**< 发生错误 */
            HAL_FLASH_Lock();  /**< 上锁 */
            return;
        }
    }

    /**< 3.内部flash进行上锁 */
    HAL_FLASH_Lock();  /**< 上锁 */

    return ;
}


static void _in_flash_read(const struct bsp_driver_flash_object *dev, 
                                    uint32_t start_addr,
                                    uint8_t *data,
                                    uint32_t len)
{
    if((dev == NULL) 							|| 
        (data == NULL) 							|| 
		(len == 0) 								||
		((start_addr + len) > FLASH_END_ADDRESS)) {
        return;
    }

    /**< 1.读取数据 */
    for(uint32_t i = 0; i < len; i++) {
        data[i] = *(uint8_t *)(start_addr + i);
    }

    return ;
}








