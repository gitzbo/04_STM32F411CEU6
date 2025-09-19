/**
 * @file app_updata.h
 * @author ZB (2536566200@qq.com)
 * @brief 升级应用
 * @version 0.1
 * @date 2025-09-12
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __APP_UPDATA_H__
#define __APP_UPDATA_H__

#include <stdint.h>

#include "main.h"

#define UPDATA_HEAD						0xAA
#define UPDATA_TAIL						0x0D

typedef void (*pfunction)(void);        /**< 函数指针 */

typedef enum {
	UPDATA_NULL = 0,					/**< 无更新操作 */
	UPDATA_QUERY,						/**< 设备查询是否进行升级命令 */
	UPDATA_APP1,						/**< 升级APP1分区 */
	UPDATA_APP2,						/**< 升级APP2分区 */
	UPDATA_DATA,						/**< 升级资源区 */
	UPDATA_MAX,							/**< 最大命令 */
}app_updata_cmd_e;

#pragma pack(push, 1)
typedef struct {
	uint8_t head;						/**< 帧头 */
	uint8_t len;						/**< 长度 */
	uint8_t cmd;						/**< 命令 */
	uint32_t crc;						/**< CRC校验 */
	uint8_t tail;						/**< 帧尾 */
}app_updata_force_t;
#pragma pack(pop)


typedef struct {
	uint32_t cmd;						/**< 命令 */
	void (*updata_cb)(void);			/**< 回调函数 */
}app_updata_cmd_t;

/**< 更新数据信息地址 */
#pragma pack(push, 1)
typedef struct {
	char app_name[32];				/**< APP名称 */
	uint32_t sf_ver;				/**< APP软件版本信息 */
	uint32_t hw_ver;				/**< APP硬件版本信息 */
	char build_data[32];			/**< 程序编译日期 */
	char build_time[32];			/**< 程序编译时间 */
} app_updata_info_t;
#pragma pack(pop)

typedef struct {
	uint32_t app1_size;				/**< APP1固件大小 */
	uint32_t app1_crc32;			/**< APP1的CRC32值 */
	uint32_t app2_size;				/**< APP2固件大小 */
	uint32_t app2_crc32;			/**< APP2的CRC32值 */
} app_updata_crc_t;





/**
 * @brief 跳转到应用程序
 * 
 */
void app_updata_jump_app(void);

/**
 * @brief 使用IEEE 802.3标准计算应用的crc32值
 * 
 * @param addr 地址
 * @param size 大小
 * @return uint32_t crc32值
 */
uint32_t app_updata_crc32(void *addr, uint32_t size);

/**
 * @brief 使用IEEE 802.3标准计算APP的crc32值
 * 
 * @param addr 地址
 * @param size 大小
 * @return uint32_t crc32值
 */
uint32_t app_updata_flash_crc32(uint32_t flash_start, uint32_t flash_size);

/**
 * @brief 强制更新函数
 * 
 */
void app_updata_force(void);

/**
 * @brief 正常更新函数
 * 
 */
void app_updata_general(void);


#endif

