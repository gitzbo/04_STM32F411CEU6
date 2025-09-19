/**
 * @file app_ymodel.h
 * @author ZB (2536566200@qq.com)
 * @brief YMODEL协议
 * @version 0.1
 * @date 2025-06-21
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __APP_YMODEL_H__
#define __APP_YMODEL_H__

/********************** INCLUDE ***************************/
#include <stdint.h>
#include <string.h>

#include "main.h"

#include "bsp_driver_uart.h"
#include "bsp_driver_flash.h"
#include "bsp_driver_iwdg.h"

/********************** DEFINE ***************************/

#define IS_AF(c)  ((c >= 'A') && (c <= 'F'))
#define IS_af(c)  ((c >= 'a') && (c <= 'f'))
#define IS_09(c)  ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)  IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)  IS_09(c)
#define CONVERTDEC(c)  (c - '0')
#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)   (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#define PACKET_SEQNO_INDEX      (1)			/**< 命令位 */
#define PACKET_SEQNO_COMP_INDEX (2)			/**< 命令补码位 */

#define PACKET_HEADER           (3)			/**< 包头长度 */
#define PACKET_TRAILER          (2)			/**< 包尾长度 */
#define PACKET_OVERHEAD         (PACKET_HEADER + PACKET_TRAILER)
#define PACKET_SIZE             (128)		/**< 128包大小 */
#define PACKET_1K_SIZE          (1024)		/**< 1024包大小 */
#define FILE_NAME_LENGTH        (64)		/**< 文件名称 */
#define FILE_SIZE_LENGTH        (16)		/**< 文件大小 */
#define SOH                     (0x01)  	/* start of 128-byte data packet */
#define STX                     (0x02)  	/* start of 1024-byte data packet */
#define EOT                     (0x04)  	/* end of transmission */
#define ACK                     (0x06)  	/* acknowledge */
#define NAK                     (0x15)  	/* negative acknowledge */
#define CA                      (0x18)  	/* two of these in succession aborts transfer */
#define CRC16                   (0x43)  	/* 'C' == 0x43, request 16-bit CRC */
#define ABORT1                  (0x41)  	/* 'A' == 0x41, abort by user */
#define ABORT2                  (0x61)  	/* 'a' == 0x61, abort by user */
#define NAK_TIMEOUT             (0x10000)	/**< 超时时间 */
#define MAX_ERRORS              (5)			/**< 最大错误数 */


/********************** FUNCTION ***************************/

/**
 * @brief 接收函数
 * 
 * @param addr 待写入的数据地址
 * @param buf 接收数据
 * @return int32_t 运行结果
 */
int32_t app_ymodem_receive(uint32_t addr ,uint8_t *buf);

/**
 * @brief CRC16计算函数
 * 
 * @param data 数据
 * @param size 数据大小
 * @return size CRC16的值
 */
uint16_t app_ymodel_cal_crc16(const uint8_t* data, uint32_t size);

/**
 * @brief INT转STR函数
 * 
 * @param str 目标字符串buf
 * @param intnum 待转换的数据
 */
void app_ymodel_int2str(uint8_t* str, int32_t intnum);

#endif

