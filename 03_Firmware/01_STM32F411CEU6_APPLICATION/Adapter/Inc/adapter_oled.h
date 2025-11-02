/**
 * @file adapter_096oled.h
 * @author ZB (2536566200@qq.com)
 * @brief 0.96寸oled适配层
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __ADAPTER_OLED_H__
#define __ADAPTER_OLED_H__

#include <stdint.h>

typedef enum {
    ADAPTER_OLED_STATUS_OK = 0,
    ADAPTER_OLED_STATUS_ERROR,
}adapter_oled_status_e;

typedef struct adapter_oled_object {
    uint32_t index;
    void *user_data;
    
    adapter_oled_status_e (*pf_oled_init)(void);
    adapter_oled_status_e (*pf_oled_deinit)(void);
    adapter_oled_status_e (*pf_oled_color_turn)(uint8_t mode);
    adapter_oled_status_e (*pf_oled_display_turn)(uint8_t mode);
    adapter_oled_status_e (*pf_oled_display_on)(void);
    adapter_oled_status_e (*pf_oled_display_off)(void);
    adapter_oled_status_e (*pf_oled_refresh)(void);
    adapter_oled_status_e (*pf_oled_clean)(void);
    adapter_oled_status_e (*pf_oled_draw_point)(uint8_t x, uint8_t y, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_line)(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_circle)(uint8_t x, uint8_t y, uint8_t r, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_char)(uint8_t x, uint8_t y, uint8_t c, uint8_t font_size, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_string)(uint8_t x, uint8_t y, uint8_t *s, uint8_t font_size, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_num)(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t font_size, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_chinese)(uint8_t x, uint8_t y, uint8_t num, uint8_t font_size, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_scroll)(uint8_t num, uint8_t space, uint8_t mode);
    adapter_oled_status_e (*pf_oled_draw_picture)(uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t *bmp, uint8_t mode);
}adapter_oled_object_t;

/**
 * @brief 将实例注册到设备对象中
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_register(uint32_t index, adapter_oled_object_t *dev);

/**
 * @brief 根据索引获取设备对象
 * 
 * @param index 索引
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_get_object(uint32_t index, adapter_oled_object_t *dev);

/**
 * @brief 设备初始化
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_init(adapter_oled_object_t *dev);

/**
 * @brief 设备逆初始化
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 
 */
adapter_oled_status_e adapter_oled_deinit(adapter_oled_object_t *dev);

/**
 * @brief 颜色反转
 * 
 * @param dev 设备对象
 * @param mode 是否反转颜色 1反转 0不反转 
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_color_turn(adapter_oled_object_t *dev, uint8_t mode);   

/**
 * @brief 屏幕旋转180度
 * 
 * @param dev 设备对象
 * @param mode 是否旋转 1旋转 0不旋转
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_display_turn(adapter_oled_object_t *dev, uint8_t mode);

/**
 * @brief 开启oled显示
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_display_on(adapter_oled_object_t *dev);

/**
 * @brief 关闭oled显示
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_display_off(adapter_oled_object_t *dev);

/**
 * @brief 更新显存到OLED
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_refresh(adapter_oled_object_t *dev);

/**
 * @brief 清空屏幕
 * 
 * @param dev 设备对象
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_clean(adapter_oled_object_t *dev);

/**
 * @brief 画点函数
 * 
 * @param dev 设备对象
 * @param x x轴坐标
 * @param y y轴坐标
 * @param mode 1.填冲，0.清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_point(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t mode);

/**
 * @brief 画线函数
 * 
 * @param dev 设备对象
 * @param x1 x轴起始坐标
 * @param y1 y轴起始坐标
 * @param x2 x轴结束坐标
 * @param y2 y轴结束坐标
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_line(adapter_oled_object_t *dev, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t mode);

/**
 * @brief 画圆函数
 * 
 * @param dev 设备对象
 * @param x x轴圆心坐标
 * @param y y轴圆心坐标
 * @param r 半径
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_circle(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t r, uint8_t mode);

/**
 * @brief 在指定位置绘制字符
 * 
 * @param dev 设备对象
 * @param x x轴起始坐标
 * @param y y轴起始坐标
 * @param c 字符
 * @param font_size 字体：6x8/6x12/8x116/12x24
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_char(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t c, uint8_t font_size, uint8_t mode);

/**
 * @brief 显示字符串
 * 
 * @param dev 设备对象
 * @param x x轴起始坐标
 * @param y y轴起始坐标
 * @param s 字符串
 * @param font_size 字体：6x8/6x12/8x116/12x24
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_string(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t *s, uint8_t font_size, uint8_t mode);

/**
 * @brief 显示数字
 * 
 * @param dev 设备对象
 * @param x x轴起始坐标
 * @param y y轴起始坐标
 * @param num 要显示的数字
 * @param len 数字位数
 * @param font_size 字体：6x8/6x12/8x116/12x24
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_num(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t font_size, uint8_t mode);

/**
 * @brief 显示汉字
 * 
 * @param dev 设备对象
 * @param x x轴起始坐标
 * @param y y轴起始坐标
 * @param num 中文数组地址
 * @param font_size 字体：6x8/6x12/8x116/12x24
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_chinese(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t num, uint8_t font_size, uint8_t mode);

/**
 * @brief 循环显示汉字
 * 
 * @param dev 设备对象
 * @param num 显示汉字个数
 * @param space 每一遍显示的间隔
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_scroll(adapter_oled_object_t *dev, uint8_t num, uint8_t space, uint8_t mode);

/**
 * @brief 显示图片
 * 
 * @param dev 设备对象
 * @param x x轴起始坐标
 * @param y y轴起始坐标
 * @param sizex 图片长度
 * @param sizey 图片宽度
 * @param bmp 图片数组
 * @param mode 1.填充，0清空
 * @return adapter_oled_status_e 运行状态
 */
adapter_oled_status_e adapter_oled_draw_picture(adapter_oled_object_t *dev, uint8_t x, uint8_t y, uint8_t sizex, uint8_t sizey, uint8_t *bmp, uint8_t mode);



#endif


