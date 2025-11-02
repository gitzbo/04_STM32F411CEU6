/**
 * @file platform_init.c
 * @author ZB (2536566200@qq.com)
 * @brief 平台初始化
 * @version 0.1
 * @date 2025-10-31
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "platform_init.h"

const app_server_updata_info_t firmware_version __attribute__((section(".ARM.__at_0x0800C800"))) = {
	.name       = "STM32f411CE",
	.sf_ver 	= 9001,
	.hw_ver 	= 9001,
	.build_data = __DATE__,
	.build_time = __TIME__,
};

platform_status_e platform_board_init(void)
{


    return PLATFORM_STATUS_OK;
}

platform_status_e platform_app_init(void)
{


    return PLATFORM_STATUS_OK;
}




