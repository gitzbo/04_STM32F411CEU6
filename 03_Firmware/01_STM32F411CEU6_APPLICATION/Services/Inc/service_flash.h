/**
 * @file service_flash.h
 * @author ZB (2536566200@qq.com)
 * @brief flash服务
 * @version 0.1
 * @date 2025-10-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SERVICE_FLASH_H__
#define __SERVICE_FLASH_H__

#include <stdint.h>

/**< flash存放结构 */
#define SERVER_UPDATA_INFO_START_ADDR	0x08008000U								/**< 更新数据信息地址 */
#define SERVER_UPDATA_INFO_END_ADDR	    0x0800BFFFU								/**< 更新数据起始地址 */
#define SERVER_APP1_START_ADDR  		0x0800C000U     						/**< APP1起始地址 */
#define SERVER_APP1_END_ADDR			0x0803FFFFU								/**< APP1结束地址 */
#define SERVER_APP2_START_ADDR  		0x08040000U     						/**< APP2起始地址 */
#define SERVER_APP2_END_ADDR			0x08071FFFU								/**< APP2结束地址 */
#define SERVER_USER_DATA_START_ADDR	    0x08072000U								/**< 资源分区起始地址 */
#define SERVER_USER_DATA_END_ADDR		0x08080000U								/**< 资源分区结束地址 */			
#define SERVER_FLASH_SIZE	 			(APP1_START_ADDR - APP1_END_ADDR)		/**< APP FLASH大小 */
#define SERVER_VER_OFFSET				0x800									/**< 版本信息偏移 */

typedef enum {
    SERVICE_FLASH_STATUS_OK = 0,
    SERVICE_FLASH_STATUS_ERROR,
}service_flash_status_e;

typedef enum {
	SERVICE_FLASH_INT_FLASH_INDEX = 0,		/**< 内部flash索引 */
	SERVICE_FLASH_EXT_FLASH_INDEX,			/**< 外部flash索引 */
}service_flash_index_e;

#pragma pack(push, 1)
typedef struct {
	char name[32];				    			/**< APP名称 */
	uint32_t sf_ver;							/**< APP软件版本信息 */
	uint32_t hw_ver;							/**< APP硬件版本信息 */
	char build_data[32];						/**< 程序编译日期 */
	char build_time[32];						/**< 程序编译时间 */
} server_updata_info_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
	uint32_t size;				    			/**< APP固件大小 */
	uint32_t crc32;			        			/**< APP的CRC32值 */
} server_crc_info_t;
#pragma pack(pop)

/**
 * @brief flash初始化
 * 此设备有两个flash需要进行管理
 * 1.内部flash设备
 * 2.外部w25q64设备
 * 
 * @return service_flash_status_e 运行状态
 */
service_flash_status_e service_flash_init(void);

/**
 * @brief 写入app版本信息
 * 
 * @param info 信息地址
 * @return service_flash_status_e 运行状态
 */
service_flash_status_e service_flash_write_version_info(server_updata_info_t *info);

/**
 * @brief 读取app版本信息
 * 
 * @param info 信息地址
 * @return service_flash_status_e 运行状态
 */
service_flash_status_e service_flash_read_version_info(server_updata_info_t *info);




#endif


