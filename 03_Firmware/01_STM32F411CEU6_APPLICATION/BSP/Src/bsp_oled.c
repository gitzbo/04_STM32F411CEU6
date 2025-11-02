/**
 * @file bsp_oled.c
 * @author ZB (2536566200@qq.com)
 * @brief oled驱动
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_oled.h"
#include "bsp_oled_font.h"
#include "main.h"
 
extern I2C_HandleTypeDef hi2c1;                                                 /**< i2c句柄 */
extern DMA_HandleTypeDef hdma_i2c1_tx;                                          /**< i2c dma句柄 */

static uint8_t _g_oled_ram_buf[BSP_OLED_PAGE][BSP_OLED_WIDTH];                  /**< OLED 输出显存 */
static uint8_t _g_oled_ram_buf2[BSP_OLED_WIDTH][BSP_OLED_PAGE];	                /**< OLED 显存暂存 */
static uint8_t _g_oled_cmd_buf[BSP_OLED_PAGE][4];                               /**< OLED 命令 */
static uint8_t _g_oled_count;                                       	        /**< 计数行 */
static uint8_t _g_oled_flag;                                        	        /**< 启动刷新 */
                                         
void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(_g_oled_flag) {
		HAL_I2C_Mem_Write_DMA(&hi2c1, BSP_OLED_ADDR, 0x40, I2C_MEMADD_SIZE_8BIT, _g_oled_ram_buf[_g_oled_count], 128);
	}
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if(_g_oled_count == 7) {
		_g_oled_flag = 0;
		_g_oled_count = 0;
	}

	else if(_g_oled_flag) {
		_g_oled_count++;
		HAL_I2C_Master_Transmit_DMA(&hi2c1, BSP_OLED_ADDR, _g_oled_cmd_buf[_g_oled_count], 4);
	}
}

bsp_oled_status_e bsp_oled_init(void)
{
    /**< 1.初始化IIC */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {
        .Pin        = OLED_SCL_Pin | OLED_SDA_Pin,
        .Mode       = GPIO_MODE_AF_OD,
        .Pull       = GPIO_NOPULL,
        .Speed      = GPIO_SPEED_FREQ_VERY_HIGH,
        .Alternate  = GPIO_AF4_I2C1,
    };
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    hi2c1.Instance              = I2C1;
    hi2c1.Init.ClockSpeed       = 400000;
    hi2c1.Init.DutyCycle        = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1      = 0;
    hi2c1.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2      = 0;
    hi2c1.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }

    /**< 2.设置DMA */
    hdma_i2c1_tx.Instance                   = DMA1_Stream1;
    hdma_i2c1_tx.Init.Channel               = DMA_CHANNEL_0;
    hdma_i2c1_tx.Init.Direction             = DMA_MEMORY_TO_PERIPH;
    hdma_i2c1_tx.Init.PeriphInc             = DMA_PINC_DISABLE;
    hdma_i2c1_tx.Init.MemInc                = DMA_MINC_ENABLE;
    hdma_i2c1_tx.Init.PeriphDataAlignment   = DMA_PDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.MemDataAlignment      = DMA_MDATAALIGN_BYTE;
    hdma_i2c1_tx.Init.Mode                  = DMA_NORMAL;
    hdma_i2c1_tx.Init.Priority              = DMA_PRIORITY_LOW;
    hdma_i2c1_tx.Init.FIFOMode              = DMA_FIFOMODE_DISABLE;
    if (HAL_DMA_Init(&hdma_i2c1_tx) != HAL_OK) {
      Error_Handler();
    }
	
    __HAL_LINKDMA(&hi2c1, hdmatx, hdma_i2c1_tx);
	
    /**< 3.设置OLED寄存器 */
    static uint8_t cmd[] = {0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8,
							0x3F, 0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1,
							0xDA, 0x12, 0xDB, 0x30, 0x8D, 0x14, 0xAF, 0x20, 0x00};
	HAL_I2C_Mem_Write_DMA(&hi2c1, BSP_OLED_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT, cmd, sizeof(cmd));
    
    /**< 4.清空显存 */
    bsp_oled_clean();

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_deinit(void)
{

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_clean(void)
{
    for(uint8_t i = 0; i < BSP_OLED_PAGE; i++) {
        for(uint8_t j = 0; j < BSP_OLED_WIDTH; j++) {
            _g_oled_ram_buf2[j][i] = 0;
        }
    }

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_refresh(void)
{
    if(_g_oled_flag == 0) {
        for(uint8_t i = 0; i < BSP_OLED_PAGE; i++) {
            _g_oled_cmd_buf[i][0] = 0x00;
            _g_oled_cmd_buf[i][1] = 0xb0 + i;
            _g_oled_cmd_buf[i][2] = 0x10;
            _g_oled_cmd_buf[i][3] = 0x00;
			for(uint8_t j = 0; j < BSP_OLED_WIDTH; j++) {
				_g_oled_ram_buf[i][j] = _g_oled_ram_buf2[j][i];
			}
        }
		
		_g_oled_flag = 1;
		HAL_I2C_Master_Transmit_DMA(&hi2c1, BSP_OLED_ADDR, _g_oled_cmd_buf[0], 4);
    }

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_point(uint8_t x, uint8_t y, uint8_t mode)
{
    uint8_t i = 0, m = 0, n = 0;

    i = y / 8;
    m = y % 8;
    n = 1 << m;
    if(mode == 1) {
        _g_oled_ram_buf2[x][i] |= n;
    }
    else {
        _g_oled_ram_buf2[x][i] = ~_g_oled_ram_buf2[x][i];
		_g_oled_ram_buf2[x][i] |= n;
		_g_oled_ram_buf2[x][i] = ~_g_oled_ram_buf2[x][i];
    }

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode)
{
	uint16_t t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;
	delta_x = x2-x1; 		//计算坐标增量 
	delta_y = y2-y1;
	uRow = x1;				//画线起点坐标
	uCol = y1;

	if(delta_x > 0) { 
        incx = 1; 			//设置单步方向 
    }
	else if (delta_x == 0) { 
        incx=0;				//垂直线
    } 
	else {
        incx = -1; 
        delta_x = -delta_x;
    }

	if(delta_y > 0) {
        incy=1;
    }
	else if (delta_y==0)incy=0;//水平线 
	else {
        incy    = -1; 
        delta_y = -delta_x;
    }

	if(delta_x > delta_y) {
        distance = delta_x; //选取基本增量坐标轴 
    }
	else { 
        distance = delta_y;
    }

	for(t = 0; t < distance + 1; t++) {
		bsp_oled_draw_point(uRow, uCol, mode);//画点
		xerr += delta_x;
		yerr += delta_y;
		if(xerr > distance) {
			xerr -= distance;
			uRow += incx;
		}
		if(yerr>distance) {
			yerr -= distance;
			uCol += incy;
		}
	}    

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_circle(uint8_t x, uint8_t y, uint8_t r, uint8_t mode)
{
    int a, b,num;
    a = 0;
    b = r;
    while(2 * b * b >= r * r) {
        bsp_oled_draw_point(x + a, y - b, 1);
        bsp_oled_draw_point(x - a, y - b, 1);
        bsp_oled_draw_point(x - a, y + b, 1);
        bsp_oled_draw_point(x + a, y + b, 1);
 
        bsp_oled_draw_point(x + b, y + a, 1);
        bsp_oled_draw_point(x + b, y - a, 1);
        bsp_oled_draw_point(x - b, y - a, 1);
        bsp_oled_draw_point(x - b, y + a, 1);
        
        a++;
        num = (a * a + b * b) - r * r;
        if(num > 0) {
            b--;
            a--;
        }
    }

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t font_size, uint8_t mode)
{
	uint8_t i, m, temp, size2, chr1;
	uint8_t x0 = x, y0 = y;
	if(font_size == 8) {
		size2 = 6;
	}
	else {
		size2 = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * (font_size / 2);  //得到字体一个字符对应点阵集所占的字节数
	}
	
	chr1 = chr - ' ';                               //计算偏移后的值
	for(i=0; i < size2; i++) {
		if(font_size == 8) {
            temp=asc2_0806[chr1][i];
        } //调用0806字体
		else if(font_size == 12) {
            temp=asc2_1206[chr1][i];
        } //调用1206字体
		else if(font_size == 16) { 
            temp=asc2_1608[chr1][i];
        } //调用1608字体
		else if(font_size == 24) {
            temp=asc2_2412[chr1][i];
        } //调用2412字体
		else {
            return BSP_OLED_STATUS_ERROR;
        }
		
		for(m = 0; m < 8; m++) {
			if(temp & 0x01) {
                bsp_oled_draw_point(x, y, mode);
            }
			else {
                bsp_oled_draw_point(x, y, !mode);
            }
			temp >>= 1;
			y++;
		}

		x++;
		if((font_size != 8)&&((x - x0) == font_size / 2)) {
            x = x0;
            y0 = y0 + 8;
        }
		y = y0; 
    }

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_string(uint8_t x, uint8_t y, uint8_t *str, uint8_t font_size, uint8_t mode)
{
    if(bsp_oled_draw_char == NULL) {
        return BSP_OLED_STATUS_ERROR;
    }
    
    /**< 判断是不是非法字符! */
	while((*str >= ' ') && (*str <= '~')) {     
		bsp_oled_draw_char(x, y, *str, font_size, mode);
		if(font_size == 8) {
            x += 6;
        }
		else {
            x += font_size / 2;
        }
		str++;
    }

    return BSP_OLED_STATUS_OK;
}

static uint32_t _bsp_oled_pow(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while(n--) {
	  result *= m;
	}

	return result;
}

bsp_oled_status_e bsp_oled_draw_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t font_size, uint8_t mode)
{
    uint8_t t = 0, temp = 0, m=0;

	if(font_size == 8) {
        m = 2;
    }

	for(t = 0; t < len; t++) {
		temp=(num / _bsp_oled_pow(10, len - t - 1)) % 10;

        if(temp==0) {
            bsp_oled_draw_char(x + (font_size / 2 + m) * t, y, '0', font_size, mode);
        }
        else {
            bsp_oled_draw_char(x + (font_size / 2 + m) * t, y, temp + '0', font_size, mode);
        }
    }

	bsp_oled_refresh();

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_chinese(uint8_t x, uint8_t y, uint8_t num, uint8_t font_size, uint8_t mode)
{
	uint8_t m,temp;
	uint8_t x0=x,y0=y;
	uint16_t i, size3 = (font_size / 8 + ((font_size % 8) ? 1 : 0)) * font_size;  //得到字体一个字符对应点阵集所占的字节数
	for(i = 0; i < size3; i++)
	{
		if(font_size==16) {
            temp=Hzk1[num][i];
        }//调用16*16字体
		else if(font_size==24) {
            temp=Hzk2[num][i];
        }//调用24*24字体
		else if(font_size==32) {
            temp=Hzk3[num][i];
        }//调用32*32字体
		else if(font_size==64) {
            temp=Hzk4[num][i];
        }//调用64*64字体
		else {
            return BSP_OLED_STATUS_ERROR;
        }
		for(m = 0; m < 8; m++) {
			if(temp & 0x01) {
                bsp_oled_draw_point(x, y, mode);
            }
			else {
                bsp_oled_draw_point(x, y, !mode);
            }
			temp >>= 1;
			y++;
		}
		x++;
		if((x - x0) == font_size) {
            x = x0;
            y0 = y0 + 8;
        }
		y = y0;
	}
	
	bsp_oled_refresh();
    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e bsp_oled_draw_scroll(uint8_t num, uint8_t space, uint8_t mode)
{
	uint8_t i, n, t = 0, m = 0, r;

//	while(1) {
        if(m==0) {
            bsp_oled_draw_chinese(128, 24, t, 16, mode);     // 写入一个汉字保存在OLED_GRAM[][]数组中
            t++;
        }
        if(t == num) {
            for(r = 0; r < 16 * space; r++) {       // 显示间隔
                for(i = 1; i < 128; i++) {
                    for(n = 0; n < 8; n++) {
                        _g_oled_ram_buf2[i - 1][n] = _g_oled_ram_buf2[i][n];
                    }
                }

                bsp_oled_refresh();
            }
            t = 0;
        }

        m++;
        if(m == 16) {
            m = 0;
        }

        for(i = 1; i < 128; i++) {                  // 实现左移
            for(n = 0; n < 8; n++) {
                _g_oled_ram_buf2[i - 1][n] = _g_oled_ram_buf2[i][n];
            }
        }

        bsp_oled_refresh();
//	}

    return BSP_OLED_STATUS_OK;
}

bsp_oled_status_e _bsp_oled_draw_picture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t *bmp, uint8_t mode)
{
	uint16_t j = 0;
	uint8_t i, n, temp, m;
	uint8_t x0 = x, y0 = y;
	sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);

	for(n = 0; n < sizey; n++) {
        for(i = 0; i < sizex; i++) {
            temp = bmp[j];
            j++;
            for(m = 0; m < 8; m++) {
                if(temp & 0x01) {
                    bsp_oled_draw_point(x, y, mode);
                }
                else {
                    bsp_oled_draw_point(x, y, !mode);
                }
                temp >>= 1;
                y++;
            }
            x++;
            if((x - x0) == sizex) {
                x = x0;
                y0 = y0 + 8;
            }
            y = y0;
        }
    }

	bsp_oled_refresh();
    return BSP_OLED_STATUS_OK;
}


