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

uint8_t file_name[FILE_NAME_LENGTH];			/**< 文件名称 */
uint32_t FlashDestination 	= APP1_START_ADDR;  /**< flash偏移地址 */
uint32_t EraseCounter 		= 0x0;				/**< 删除计数 */
uint32_t NbrOfPage 			= 0;				/**< 删除的页面数 */	
//FLASH_Status FLASHStatus 	= FLASH_COMPLETE;	/**< flash状态 */
//uint16_t PageSize 		= FLASH_PAGE_SIZE;	/**< flash页大小 */
uint32_t RamSource;								/**< 存放APP的包地址 */


static uint16_t _app_ymodel_crc16(uint16_t crcIn, uint8_t byte);
static int32_t _app_ymodel_receive_packet (uint8_t *data, int32_t *length, uint32_t timeout);
static uint32_t _app_ymodel_send_byte (uint8_t c);
static int32_t _app_ymodel_recv_byte (uint8_t *c, uint32_t timeout);
static uint32_t _app_ymodel_str2int(uint8_t *inputstr, int32_t *intnum);

void app_ymodel_int2str(uint8_t* str, int32_t intnum)
{
	uint32_t i, Div = 1000000000, j = 0, Status = 0;

	for (i = 0; i < 10; i++) {
		str[j++] = (intnum / Div) + '0';		/**< 计算当前位的数字并转换为ASCII字符 */
		intnum = intnum % Div;					/**< 取余数，用于下一位计算 */
		Div /= 10;								/**< 除数减10倍，用于处理下一位 */
		
		/**< 处理前导零：如果当前字符是'0'且尚未遇到非零字符 */ 
		if ((str[j - 1] == '0') & (Status == 0)) {
			j = 0;
		}
		
		else {
			Status++;
		}
	}
}

static uint32_t _app_ymodel_str2int(uint8_t *inputstr, int32_t *intnum)
{
	uint32_t i = 0, res = 0;
	uint32_t val = 0;

	/**< 16进制输入 */
	if((inputstr[0] == '0') && ((inputstr[1] == 'x') || (inputstr[1] == 'X'))) {
		if (inputstr[2] == '\0') {
			return 0;
		}
		
		for (i = 2; i < 11; i++) {
			/**> 判断结束 */
			if (inputstr[i] == '\0') {
				*intnum = val;
				res = 1;
				break;
			}
			
			/**> 判断是否为16进制，然后进行转换 */
			if (ISVALIDHEX(inputstr[i])) {
				val = (val << 4) + CONVERTHEX(inputstr[i]);
			}
			
			/**> 参数错误退出 */
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
		/**< 十进制输入 */
		for (i = 0;i < 11;i++) {
			if (inputstr[i] == '\0') {
				*intnum = val;
				res = 1;
				break;
			}
			
			/**< 按照K为单位的转换  */
			else if ((inputstr[i] == 'k' || inputstr[i] == 'K') && (i > 0)) {
				val = val << 10;
				*intnum = val;
				res = 1;
				break;
			}
			
			/**< 按照M为单位的转换 */
			else if ((inputstr[i] == 'm' || inputstr[i] == 'M') && (i > 0)) {
				val = val << 20;
				*intnum = val;
				res = 1;
				break;
			}
			
			/**< 没有k和m判断是否是10进制然后直接转换 */
			else if (ISVALIDDEC(inputstr[i])) {
				val = val * 10 + CONVERTDEC(inputstr[i]);
			}
			/**< 无效数据 */
			else {
				res = 0;
				break;
			}
		}
		/* 超过10位数无效 */
		if (i >= 11) {
			res = 0;
		}
	}

	return res;
}

static int32_t _app_ymodel_recv_byte(uint8_t *c, uint32_t timeout)
{
	if(c == NULL) {
		return -1;
	}
	
	bsp_driver_uart_object_t uart1_obj;
	bsp_driver_uart_get_object(0, &uart1_obj);
	if(bsp_driver_uart_recv(&uart1_obj, c, 1, timeout) == UART_DRIVER_OK) {
		return 0;
	}
	
	return -1;
}

static uint32_t _app_ymodel_send_byte(uint8_t c)
{
	bsp_driver_uart_object_t uart1_obj;
	bsp_driver_uart_get_object(0, &uart1_obj);
	
	bsp_driver_uart_send(&uart1_obj, &c, 1, 1);
	
	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: _app_ymodel_receive_packet
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
static int32_t _app_ymodel_receive_packet(uint8_t *data, int32_t *length, uint32_t timeout)
{
	uint16_t i, packet_size;
	uint8_t c;
	*length = 0;
	/**< 接收一个字符数据 */
	if (_app_ymodel_recv_byte(&c, timeout) != 0) {
		return -1;
	}
	
	/**< 判断这个字符数据是那个命令 */
	switch (c) {
		/**< 128包大小的数据 */
		case SOH:
			packet_size = PACKET_SIZE;
			break;
		/**< 1024包大小的数据 */
		case STX:
			packet_size = PACKET_1K_SIZE;
			break;
		/**< 结束标志 */
		case EOT:
			return 0;
		/**< 连续两个CA代表终止命令 */
		case CA:
			if ((_app_ymodel_recv_byte(&c, timeout) == 0) && (c == CA)) {
				*length = -1;
				return 0;
			}
			else {
				return -1;
			}
		/**< 用户终止命令 */
		case ABORT1:
		case ABORT2:
			return 1;
		default:
			return -1;
	}
	*data = c;		/**< 将第一个数据放入buf的第一位 */
	
	/**< 通过接收到的数据包大小进行接下来的数据接收 */
	for (i = 1; i < (packet_size + PACKET_OVERHEAD); i ++) {
		if (_app_ymodel_recv_byte(data + i, timeout) != 0) {
			return -1;
		}
	}

	/**< 判断首位和第二位的补码是否相同（包验证机制） */
	if (data[PACKET_SEQNO_INDEX] != ((data[PACKET_SEQNO_COMP_INDEX] ^ 0xff) & 0xff)) {
		return -1;
	}

	*length = packet_size;
	return 0;
}

int32_t app_ymodem_receive(uint32_t addr ,uint8_t *buf)
{
	uint8_t packet_data[PACKET_1K_SIZE + PACKET_OVERHEAD]; 				/**< 目标空间buf */ 
	uint8_t file_size[FILE_SIZE_LENGTH];								/**< 升级文件buf */
	uint8_t *file_ptr, *buf_ptr;										/**< buf指针 */
	int32_t i, j, packet_length, session_done, file_done, packets_received, errors, session_begin, size = 0;

	/* 初始化变量 */
	bsp_driver_flash_object_t flash1_obj = {0};
	bsp_driver_flash_get_object(0, &flash1_obj);
	FlashDestination = addr;

	for (session_done = 0, errors = 0, session_begin = 0; ;) {
		for (packets_received = 0, file_done = 0, buf_ptr = buf; ;) {
			switch (_app_ymodel_receive_packet(packet_data, &packet_length, NAK_TIMEOUT)) {
			case 0:
				errors = 0;
				switch (packet_length) {
				/**< 发送端终止 */
				case - 1:
					_app_ymodel_send_byte(ACK);
					return 0;
				
				/**< 结束传输*/
				case 0:
					_app_ymodel_send_byte(ACK);
					file_done = 1;
					break;
				
				/**< 普通包 */
				default:
					if ((packet_data[PACKET_SEQNO_INDEX] & 0xff) != (packets_received & 0xff)) {
						_app_ymodel_send_byte(NAK);
					}
					
					else {
						if (packets_received == 0) {
							/**< 文件信息buffer */
							if (packet_data[PACKET_HEADER] != 0) {
								
								/**< 接收文件名称 */
								for (i = 0, file_ptr = packet_data + PACKET_HEADER; (*file_ptr != 0) && (i < FILE_NAME_LENGTH);) {
									file_name[i++] = *file_ptr++;
								}
								file_name[i++] = '\0';
								
								/* 接收文件大小 */
								for (i = 0, file_ptr ++; (*file_ptr != ' ') && (i < FILE_SIZE_LENGTH);) {
									file_size[i++] = *file_ptr++;
								}
								
								/**< 接收flash大小并验证FLASH是否超过APP的最大值 */
								file_size[i++] = '\0';
								_app_ymodel_str2int(file_size, &size);
								if (size > (APP_FLASH_SIZE - 1)) {
									_app_ymodel_send_byte(CA);
									_app_ymodel_send_byte(CA);
									return -1;
								}

								/**< 计算APP需要的空间并清空 */
								bsp_driver_flash_erase(&flash1_obj, FlashDestination, size);
								
								_app_ymodel_send_byte(ACK);
								_app_ymodel_send_byte(CRC16);
							}
							
							/* 文件名为空跳出更新 */
							else {
								_app_ymodel_send_byte(ACK);
								file_done = 1;
								session_done = 1;
								break;
							}
						}
						
						/* 数据包 */
						else {
							/**< 将有效数据给到待写入buf中 */
							memcpy(buf_ptr, packet_data + PACKET_HEADER, packet_length);
							RamSource = (uint32_t)buf;										/**< 将buf地址给到源中 */
							
							/**< 按照每次写入4位的方式写入 */
							for (j = 0; (j < packet_length) && (FlashDestination <  addr + size);j += 4) {
								/**< 将获取到的数据写入到flash中 */
								bsp_driver_flash_write(&flash1_obj, FlashDestination, (uint8_t *)&RamSource, 4);
								
								/**< 判断写入值的是否相等 */
								if (*(uint32_t *)FlashDestination != *(uint32_t *)RamSource) {
									_app_ymodel_send_byte(CA);
									_app_ymodel_send_byte(CA);
									return -2;
								}
								
								/**< 更新写入地址 */
								FlashDestination += 4;
								RamSource += 4;
							}
							/**< 发送应答 */
							_app_ymodel_send_byte(ACK);
						}
						packets_received ++;
						session_begin = 1;
					}
				}
				break;
			
			/**< 用户终止操作 */
			case 1:
				_app_ymodel_send_byte(CA);
				_app_ymodel_send_byte(CA);
				return -3;
			
			/**< 包错误 */
			default:
				if (session_begin > 0) {
					errors ++;
				}
				if (errors > MAX_ERRORS) {
					_app_ymodel_send_byte(CA);
					_app_ymodel_send_byte(CA);
					return 0;
				}
				_app_ymodel_send_byte(CRC16);
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

static uint16_t _app_ymodel_crc16(uint16_t crcIn, uint8_t byte)
{
	uint32_t crc = crcIn;
	uint32_t in = byte | 0x100;
	
	do {
		crc <<= 1;
		in <<= 1;
		if(in & 0x100) ++crc;
		if(crc & 0x10000) crc ^= 0x1021;
	}while(!(in & 0x10000));

	return crc & 0xffffu;
}

uint16_t app_ymodel_cal_crc16(const uint8_t* data, uint32_t size)
{
	uint32_t crc = 0;
	const uint8_t* data_end = data + size;

	while(data < data_end) {
		crc = _app_ymodel_crc16(crc, *data++);
	}

	crc = _app_ymodel_crc16(crc, 0);
	crc = _app_ymodel_crc16(crc, 0);

	return crc & 0xffffu;
}





