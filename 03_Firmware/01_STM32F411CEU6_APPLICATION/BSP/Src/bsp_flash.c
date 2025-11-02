/**
 * @file bsp_flash.c
 * @author ZB (2536566200@qq.com)
 * @brief flash驱动
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "bsp_flash.h"
#include "main.h"

bsp_flash_status_e bsp_int_flash_init(void)
{
    return BSP_FLASH_STATUS_OK;
}

bsp_flash_status_e bsp_int_flash_deinit(void)
{
    return BSP_FLASH_STATUS_OK;
}

bsp_flash_status_e bsp_int_flash_erase(uint32_t start_addr, uint32_t len)
{
    uint32_t page_error = 0;
    uint8_t sector = 0, number_of_sectors = 0;

    if((start_addr < FLASH_START_ADDRESS) || ((start_addr + len) > FLASH_END_ADDRESS) || (len == 0)) {
        return BSP_FLASH_STATUS_ERROR;                                       
    }
    
    HAL_FLASH_Unlock();
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
	
    FLASH_EraseInitTypeDef EraseInitStruct;
    EraseInitStruct.TypeErase       = FLASH_TYPEERASE_SECTORS;
    EraseInitStruct.VoltageRange    = FLASH_VOLTAGE_RANGE_3;
    EraseInitStruct.Sector          = sector;
    EraseInitStruct.NbSectors       = number_of_sectors;
    EraseInitStruct.Banks           = FLASH_BANK_1;
    if(HAL_FLASHEx_Erase(&EraseInitStruct, &page_error) != HAL_OK) {
        HAL_FLASH_Lock();
        return BSP_FLASH_STATUS_ERROR;
    }
    HAL_FLASH_Lock();

    return BSP_FLASH_STATUS_OK;
}

bsp_flash_status_e bsp_int_flash_write(uint32_t start_addr, const uint8_t *data, uint32_t len)
{
    if((data == NULL) || ((start_addr + len) > FLASH_END_ADDRESS) || (start_addr < FLASH_START_ADDRESS) || (len == 0)) {
        return BSP_FLASH_STATUS_ERROR;
    }

    HAL_FLASH_Unlock();
    for(uint32_t i = 0; i < len; i++) {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, start_addr + i, data[i]) != HAL_OK) {
            HAL_FLASH_Lock();
            return BSP_FLASH_STATUS_ERROR;
        }
    }
    HAL_FLASH_Lock();

    return BSP_FLASH_STATUS_OK;
}

bsp_flash_status_e bsp_int_flash_read(uint32_t start_addr, uint8_t *data, uint32_t len)
{
    if((data == NULL) || (len == 0) || ((start_addr + len) > FLASH_END_ADDRESS)) {
        return BSP_FLASH_STATUS_ERROR;
    }

    for(uint32_t i = 0; i < len; i++) {
        data[i] = *(uint8_t *)(start_addr + i);
    }

    return BSP_FLASH_STATUS_OK;
}




