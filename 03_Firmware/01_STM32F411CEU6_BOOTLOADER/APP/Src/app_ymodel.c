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
#include "app_ymodel.h"
#include <string.h>
#include <stdint.h>
//#include "bsp_driver_usart.h"
#include "bsp_driver_flash.h"

uint8_t file_name[FILE_NAME_LENGTH];			/**< 文件名称 */
uint32_t FlashDestination 	= WRITE_START_ADDR; /**< flash偏移地址 */
uint16_t PageSize 			= FLASH_PAGE_SIZE;	/**< flash页大小 */
uint32_t EraseCounter 		= 0x0;				/**< 删除计数 */
uint32_t NbrOfPage 			= 0;				
FLASH_Status FLASHStatus 	= FLASH_COMPLETE;	/**< flash状态 */
uint32_t RamSource;

static uint16_t Cal_CRC16(const uint8_t* data, uint32_t size);
static int32_t Receive_Packet (uint8_t *data, int32_t *length, uint32_t timeout);
static uint32_t Send_Byte (uint8_t c);
static int32_t Receive_Byte (uint8_t *c, uint32_t timeout);
static void Int2Str(uint8_t* str, int32_t intnum);
static uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);

/*
*********************************************************************************************************
*	函 数 名: Int2Str
*	功能说明: 将整数转换成字符
*	形    参: str 字符  intnum 整数
*	返 回 值: 无
*********************************************************************************************************
*/
static void Int2Str(uint8_t* str, int32_t intnum)
{
	uint32_t i, Div = 1000000000, j = 0, Status = 0;

	for (i = 0; i < 10; i++) {
		str[j++] = (intnum / Div) + 48;
		intnum = intnum % Div;
		Div /= 10;
		if ((str[j-1] == '0') & (Status == 0)) {
			j = 0;
		}
		else {
			Status++;
		}
	}
}

/*
*********************************************************************************************************
*	函 数 名: Str2Int
*	功能说明: 将字符转换成整数
*	形    参: inputstr 字符  intnum 整数
*	返 回 值: 1 正确 2 错误
*********************************************************************************************************
*/
static uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum)
{
	uint32_t i = 0, res = 0;
	uint32_t val = 0;

	if((inputstr[0] == '0') && 
    	((inputstr[1] == 'x') || (inputstr[1] == 'X'))) {
		if (inputstr[2] == '\0') {
			return 0;
		}
		
		for (i = 2; i < 11; i++) {
			if (inputstr[i] == '\0') {
				*intnum = val;
				res = 1;
				break;
			}
			
			if (ISVALIDHEX(inputstr[i])) {
				val = (val << 4) + CONVERTHEX(inputstr[i]);
			}
			else {
				res = 0;
				break;
			}
		}

		if (i >= 11) {
			res = 0;
		}
	}
	else {
		for (i = 0;i < 11;i++) {
			if (inputstr[i] == '\0') {
				*intnum = val;
				res = 1;
				break;
			}
			else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0)) {
				val = val << 10;
				*intnum = val;
				res = 1;
				break;
			}
			else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0)) {
				val = val << 20;
				*intnum = val;
				res = 1;
				break;
			}
			else if (ISVALIDDEC(inputstr[i])) {
				val = val * 10 + CONVERTDEC(inputstr[i]);
			}
			else {
				/* return 0, Invalid input */
				res = 0;
				break;
			}
		}
		/* Over 10 digit decimal --invalid */
		if (i >= 11) {
			res = 0;
		}
	}

	return res;
}

/*
*********************************************************************************************************
*	函 数 名: Receive_Byte
*	功能说明: 接收发送端发来的字符         
*	形    参：c  字符
*             timeout  溢出时间
*	返 回 值: 0 接收成功， -1 接收失败
*********************************************************************************************************
*/
static int32_t Receive_Byte(uint8_t *c, uint32_t timeout)
{
	__IO uint32_t count = timeout;
	
	while(count-- > 0) {
		if (bsp_usart1_getc(c) == 1) {
			return 0;
		}
	}
	
	return -1;
}

/*
*********************************************************************************************************
*	函 数 名: Send_Byte
*	功能说明: 发送一个字节数据         
*	形    参：c  字符
*	返 回 值: 0
*********************************************************************************************************
*/
static uint32_t Send_Byte(uint8_t c)
{
	bsp_usart1_putc(c);
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: Receive_Packet
*	功能说明: 接收一包数据        
*	形    参：data 数据
*             length 数据大小
*             timeout  0 传输结束
*                      -1 发送端终止传输
*                      >0 数据包长度
*	返 回 值: 0  正常返回
*             -1 时间溢出或数据包错误
*             1  用户终止
*********************************************************************************************************
*/
static int32_t Receive_Packet(uint8_t *data, int32_t *length, uint32_t timeout)
{
	uint16_t i, packet_size;
	uint8_t c;
	*length = 0;

	if (Receive_Byte(&c, timeout) != 0) {
	return -1;
	}

	switch (c) {
	case SOH:
		packet_size = PACKET_SIZE;
		break;
	case STX:
		packet_size = PACKET_1K_SIZE;
		break;
	case EOT:
		return 0;
	case CA:
		if ((Receive_Byte(&c, timeout) == 0) && (c == CA)) {
		*length = -1;
		return 0;
		}
		else {
		return -1;
		}
	case ABORT1:
	case ABORT2:
		return 1;
	default:
		return -1;
	}
	*data = c;

	for (i = 1; i < (packet_size + PACKET_OVERHEAD); i ++) {
		if (Receive_Byte(data + i, timeout) != 0) {
			return -1;
		}
	}

	if (data[PACKET_SEQNO_INDEX] != 
		((data[PACKET_SEQNO_COMP_INDEX] ^ 0xff) & 0xff)) {
		return -1;
	}

	*length = packet_size;
	return 0;
}

int32_t Ymodem_Receive(uint8_t *buf)
{
  uint8_t packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD]; 				/**< 目标空间buf */ 
  uint8_t file_size[FILE_SIZE_LENGTH];									/**< 升级文件buf */
  uint8_t *file_ptr, *buf_ptr;
  int32_t i, j, packet_length, session_done, file_done, packets_received, errors, session_begin, size = 0;

  /* Initialize FlashDestination variable */
  FlashDestination = WRITE_START_ADDR;

	for (session_done = 0, errors = 0, session_begin = 0; ;) {
		for (packets_received = 0, file_done = 0, buf_ptr = buf; ;) {
			switch (Receive_Packet(packet_data, &packet_length, NAK_TIMEOUT)) {
			case 0:
				errors = 0;
				switch (packet_length) {
				/* Abort by sender */
				case - 1:
					Send_Byte(ACK);
					return 0;
				/* End of transmission */
				case 0:
					Send_Byte(ACK);
					file_done = 1;
					break;
				/* Normal packet */
				default:
					if ((packet_data[PACKET_SEQNO_INDEX] & 0xff) != (packets_received & 0xff)) {
						Send_Byte(NAK);
					}
					else {
						if (packets_received == 0) {
							/* Filename packet */
							if (packet_data[PACKET_HEADER] != 0) {
							/* Filename packet has valid data */
							for (i = 0, file_ptr = packet_data + PACKET_HEADER; (*file_ptr != 0) && (i < FILE_NAME_LENGTH);) {
								file_name[i++] = *file_ptr++;
							}
							file_name[i++] = '\0';
							for (i = 0, file_ptr ++; (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH);) {
								file_size[i++] = *file_ptr++;
							}
							file_size[i++] = '\0';
							Str2Int(file_size, &size);

							/* Test the size of the image to be sent */
							/* Image size is greater than Flash size */
							if (size > (FLASH_SIZE - 1)) {
								/* End session */
								Send_Byte(CA);
								Send_Byte(CA);
								return -1;
							}

							/* Erase the needed pages where the user application will be loaded */
							/* Define the number of page to be erased */
							NbrOfPage = FLASH_PagesMask(size);

							/* Erase the FLASH pages */
							for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++) {
								FLASHStatus = FLASH_ErasePage(FlashDestination + (PageSize * EraseCounter));
							}
							Send_Byte(ACK);
							Send_Byte(CRC16);
							}
							/* Filename packet is empty, end session */
							else {
							Send_Byte(ACK);
							file_done = 1;
							session_done = 1;
							break;
							}
						}
						/* Data packet */
						else {
							memcpy(buf_ptr, packet_data + PACKET_HEADER, packet_length);
							RamSource = (uint32_t)buf;
							for (j = 0; (j < packet_length) && (FlashDestination <  WRITE_START_ADDR + size);j += 4) {
							/* Program the data received into STM32F10x Flash */
							FLASH_ProgramWord(FlashDestination, *(uint32_t*)RamSource);

							if (*(uint32_t*)FlashDestination != *(uint32_t*)RamSource) {
								/* End session */
								Send_Byte(CA);
								Send_Byte(CA);
								return -2;
							}
							FlashDestination += 4;
							RamSource += 4;
							}
							Send_Byte(ACK);
						}
						packets_received ++;
						session_begin = 1;
					}
				}
				break;
			case 1:
				Send_Byte(CA);
				Send_Byte(CA);
				return -3;
			default:
				if (session_begin > 0) {
				errors ++;
				}
				if (errors > MAX_ERRORS) {
				Send_Byte(CA);
				Send_Byte(CA);
				return 0;
				}
				Send_Byte(CRC16);
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
	return (int32_t)size;
}

uint16_t UpdateCRC16(uint16_t crcIn, uint8_t byte)
{
  uint32_t crc = crcIn;
  uint32_t in = byte | 0x100;

  do
  {
	crc <<= 1;
	in <<= 1;
	if(in & 0x100)
		++crc;
	if(crc & 0x10000)
		crc ^= 0x1021;
  }while(!(in & 0x10000));

  return crc & 0xffffu;
}

static uint16_t Cal_CRC16(const uint8_t* data, uint32_t size)
{
	uint32_t crc = 0;
	const uint8_t* dataEnd = data + size;

	while(data < dataEnd) {
		crc = UpdateCRC16(crc, *data++);
	}

	crc = UpdateCRC16(crc, 0);
	crc = UpdateCRC16(crc, 0);

	return crc & 0xffffu;
}





