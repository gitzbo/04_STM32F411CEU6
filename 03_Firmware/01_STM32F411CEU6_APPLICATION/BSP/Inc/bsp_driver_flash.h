/**
 * @file bsp_driver_flash.h
 * @author ZB (2536566200@qq.com)
 * @brief flash驱动
 * @version 0.1
 * @date 2025-09-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BSP_DRIVER_FLASH_H__
#define __BSP_DRIVER_FLASH_H__

#include <stdint.h>
#include <stddef.h>

#define FLASH_DEV_MAX       2                             				/**< FLASH设备最大数量 */

#define UPDATA_INFO_START_ADDR	0x08008000U								/**< 更新数据信息地址 */
#define UPDATA_INFO_END_ADDR	0x0800BFFFU								/**< 更新数据起始地址 */
#define APP1_START_ADDR  		0x0800C000U     						/**< APP1起始地址 */
#define APP1_END_ADDR			0x0803FFFFU								/**< APP1结束地址 */
#define APP2_START_ADDR  		0x08040000U     						/**< APP2起始地址 */
#define APP2_END_ADDR			0x08071FFFU								/**< APP2结束地址 */
#define USER_DATA_START_ADDR	0x08072000U								/**< 资源分区起始地址 */
#define USER_DATA_END_ADDR		0x08080000U								/**< 资源分区结束地址 */			
#define APP_FLASH_SIZE	 		(APP1_START_ADDR - APP1_END_ADDR)		/**< APP FLASH大小 */

/**< flash驱动文件 */
typedef enum {
    FLASH_DRIVER_OK = 0,        /**< 运行成功 */
    FLASH_DRIVER_ERROR,         /**< 运行错误 */
}bsp_driver_flash_status_e;

/**< flash结构体对象 */
typedef struct bsp_driver_flash_object {
    uint32_t index;                                                                             /**< Record the instance index. */
    void *user_data;                                                                            /**< Record the user data       */

    void (*pf_flash_init)(const struct bsp_driver_flash_object *dev);                           /**< function pointer to device init   */
    void (*pf_flash_deinit)(const struct bsp_driver_flash_object *dev);                         /**< function pointer to device deinit */
    void (*pf_flash_erase)(const struct bsp_driver_flash_object *dev, 
                                                uint32_t start_addr, 
                                                uint32_t len);                                  /**< function pointer to device erase   */
    void (*pf_flash_write)(const struct bsp_driver_flash_object *dev, 
                                                uint32_t start_addr, 
                                                const uint8_t *data, 
                                                uint32_t len);                                  /**< function pointer to device write   */
    void (*pf_flash_read)(const struct bsp_driver_flash_object *dev, 
                                                uint32_t start_addr, 
                                                uint8_t *data, 
                                                uint32_t len);                                  /**< function pointer to device read   */
} bsp_driver_flash_object_t;

/**
 * @brief 将flash设备注册到驱动中
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_register(uint32_t index, bsp_driver_flash_object_t *dev);

/**
 * @brief 获取flash对象
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_get_object(uint32_t index, bsp_driver_flash_object_t *dev);

/**
 * @brief flash初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_init(const bsp_driver_flash_object_t *dev);

/**
 * @brief flash去初始化
 * 
 * @param dev 设备对象
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_deinit(const bsp_driver_flash_object_t *dev);

/**
 * @brief flash擦除
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param len 擦除长度
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_erase(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                uint32_t len);

/**
 * @brief flash写入
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待写入数据地址
 * @param len 数据长度
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_write(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                const uint8_t *data,
                                                uint32_t len);

/**
 * @brief flash读取
 * 
 * @param dev 设备对象
 * @param start_addr 起始地址
 * @param data 待存入数据地址
 * @param len 数据长度
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_read(const bsp_driver_flash_object_t *dev, 
                                                uint32_t start_addr, 
                                                uint8_t *data,
                                                uint32_t len);

/**
 * @brief flash拷贝函数
 * 
 * @param host 待拷贝设备
 * @param host_addr 待拷贝地址
 * @param target 目标设备
 * @param target_addr 目标地址
 * @param target_len 目标长度
 * @return bsp_driver_flash_status_e 运行状态
 */
bsp_driver_flash_status_e bsp_driver_flash_copy( const bsp_driver_flash_object_t *host,
												 uint32_t host_addr,
												 const bsp_driver_flash_object_t *target,
												 uint32_t target_addr,
												 uint32_t target_len);


#endif


