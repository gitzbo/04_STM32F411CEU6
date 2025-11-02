/**
 * @file bsp_oled.h
 * @author ZB (2536566200@qq.com)
 * @brief oled显示屏驱动
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __BSP_OLED_H__
#define __BSP_OLED_H__

#include <stdint.h>

#define BSP_OLED_PAGE   8           /**< 屏幕页数 */
#define BSP_OLED_HEIGH  64          /**< 高 */
#define BSP_OLED_WIDTH  128         /**< 宽 */
#define BSP_OLED_ADDR   0x78        /**< IIC地址 */

typedef enum {
    BSP_OLED_STATUS_OK = 0,
    BSP_OLED_STATUS_ERROR,
} bsp_oled_status_e;

/**
 * @brief oled初始化
 * 
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_init(void);

/**
 * @brief oled逆初始化
 * 
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_deinit(void);

/**
 * @brief 清空oled
 * 
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_clean(void);

/**
 * @brief 更新oled缓冲
 * 
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_refresh(void);

/**
 * @brief oled画点函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_point(uint8_t x, uint8_t y, uint8_t mode);

/**
 * @brief oled画线函数
 * 
 * @param x1 x1轴坐标
 * @param y1 y1轴坐标
 * @param x2 x2轴坐标
 * @param y2 y2轴坐标
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);

/**
 * @brief oled画圆函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param r 半径
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_circle(uint8_t x, uint8_t y, uint8_t r, uint8_t mode);

/**
 * @brief oled画字函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param chr 字
 * @param font_size 字体
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t font_size, uint8_t mode);

/**
 * @brief oled显示字符串函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param str 字符串
 * @param font_size 字体
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_string(uint8_t x, uint8_t y, uint8_t *str, uint8_t font_size, uint8_t mode);

/**
 * @brief oled显示数字函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param num 数
 * @param len 长度
 * @param font_size 字体
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t font_size, uint8_t mode);

/**
 * @brief oled显示中文函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param num 第几个字
 * @param font_size 字体
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_chinese(uint8_t x, uint8_t y, uint8_t num, uint8_t font_size, uint8_t mode);

/**
 * @brief oled显示滚动字符函数
 * 
 * @param num 数
 * @param space 空间
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_scroll(uint8_t num, uint8_t space, uint8_t mode);

/**
 * @brief oled显示图片函数
 * 
 * @param x x轴坐标
 * @param y y轴坐标
 * @param sizex x轴长度
 * @param sizey y轴长度
 * @param bmp 图片地址
 * @param mode 是否反色
 * @return bsp_oled_status_e 运行状态
 */
bsp_oled_status_e bsp_oled_draw_picture(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t *bmp, uint8_t mode);    


#endif



