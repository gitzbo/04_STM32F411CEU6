/**
 * @file adapter_096oled.c
 * @author ZB (2536566200@qq.com)
 * @brief 0.96寸oled适配层
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "adapter_oled.h"
#include <stddef.h>
#include "platform_config.h"

#ifndef OLED_DEV_MAX
#define OLED_DEV_MAX    1
#endif

static adapter_oled_object_t _oled_drv_dev[OLED_DEV_MAX];

adapter_oled_status_e adapter_oled_register(uint32_t index, adapter_oled_object_t *dev)
{
    if((dev == NULL) || (index >= OLED_DEV_MAX)) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    _oled_drv_dev[index].index                  = index;
    _oled_drv_dev[index].user_data              = dev->user_data;
    _oled_drv_dev[index].pf_oled_init           = dev->pf_oled_init;
    _oled_drv_dev[index].pf_oled_deinit         = dev->pf_oled_deinit;
    _oled_drv_dev[index].pf_oled_color_turn     = dev->pf_oled_color_turn;
    _oled_drv_dev[index].pf_oled_display_turn   = dev->pf_oled_display_turn;
    _oled_drv_dev[index].pf_oled_display_on     = dev->pf_oled_display_on;
    _oled_drv_dev[index].pf_oled_display_off    = dev->pf_oled_display_off;
    _oled_drv_dev[index].pf_oled_refresh        = dev->pf_oled_refresh;
    _oled_drv_dev[index].pf_oled_clean          = dev->pf_oled_clean;
    _oled_drv_dev[index].pf_oled_draw_point     = dev->pf_oled_draw_point;
    _oled_drv_dev[index].pf_oled_draw_line      = dev->pf_oled_draw_line;
    _oled_drv_dev[index].pf_oled_draw_circle    = dev->pf_oled_draw_circle;
    _oled_drv_dev[index].pf_oled_draw_char      = dev->pf_oled_draw_char;
    _oled_drv_dev[index].pf_oled_draw_string    = dev->pf_oled_draw_string;
    _oled_drv_dev[index].pf_oled_draw_num       = dev->pf_oled_draw_num;
    _oled_drv_dev[index].pf_oled_draw_chinese   = dev->pf_oled_draw_chinese;
    _oled_drv_dev[index].pf_oled_draw_scroll    = dev->pf_oled_draw_scroll;
    _oled_drv_dev[index].pf_oled_draw_picture   = dev->pf_oled_draw_picture;

    return ADAPTER_OLED_STATUS_OK;
}

adapter_oled_status_e adapter_oled_get_object(uint32_t index, adapter_oled_object_t *dev)
{
    if((index > OLED_DEV_MAX) || (dev == NULL)) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    *dev = _oled_drv_dev[index];

    return ADAPTER_OLED_STATUS_OK;
}

adapter_oled_status_e adapter_oled_init(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_init == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_init();
}

adapter_oled_status_e adapter_oled_deinit(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_deinit == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_deinit();
}

adapter_oled_status_e adapter_oled_color_turn(adapter_oled_object_t *dev, uint8_t mode)
{
    if(dev->pf_oled_color_turn == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_color_turn(mode);
}

adapter_oled_status_e adapter_oled_display_turn(adapter_oled_object_t *dev, uint8_t mode)
{
    if(dev->pf_oled_display_turn == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_display_turn(mode);
}

adapter_oled_status_e adapter_oled_display_on(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_display_on == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_display_on();
}

adapter_oled_status_e adapter_oled_display_off(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_display_off == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_display_off();
}

adapter_oled_status_e adapter_oled_refresh(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_refresh == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_refresh();
}

adapter_oled_status_e adapter_oled_clean(adapter_oled_object_t *dev)
{
    if(dev->pf_oled_clean == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_clean();
}

adapter_oled_status_e adapter_oled_draw_point(adapter_oled_object_t *dev,    
                                              uint8_t x,                                  
                                              uint8_t y,                                  
                                              uint8_t mode)
{
    if(dev->pf_oled_draw_point == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_point(x, y, mode);
}

adapter_oled_status_e adapter_oled_draw_line(adapter_oled_object_t *dev,     
                                             uint8_t x1,                                 
                                             uint8_t y1,                                 
                                             uint8_t x2,                                 
                                             uint8_t y2,                                 
                                             uint8_t mode)
{
    if(dev->pf_oled_draw_line == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_line(x1, y1, x2, y2, mode);
}

adapter_oled_status_e adapter_oled_draw_circle(adapter_oled_object_t *dev, 
                                               uint8_t x, 
                                               uint8_t y, 
                                               uint8_t r,
                                               uint8_t mode)
{
    if(dev->pf_oled_draw_circle == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_circle(x, y, r, mode);
}

adapter_oled_status_e adapter_oled_draw_char(adapter_oled_object_t *dev, 
                                             uint8_t x, 
                                             uint8_t y, 
                                             uint8_t c, 
                                             uint8_t font_size,                          
                                             uint8_t mode)
{
    if(dev->pf_oled_draw_char == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_char(x, y, c, font_size, mode);
}

adapter_oled_status_e adapter_oled_draw_string(adapter_oled_object_t *dev,   
                                               uint8_t x,                                  
                                               uint8_t y,                                  
                                               uint8_t *s,                                 
                                               uint8_t font_size,                          
                                               uint8_t mode)
{
    if(dev->pf_oled_draw_string == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_string(x, y, s, font_size, mode);
}

adapter_oled_status_e adapter_oled_draw_num(adapter_oled_object_t *dev,      
                                            uint8_t x,                                  
                                            uint8_t y,                                  
                                            uint32_t num, 
                                            uint8_t len,    
                                            uint8_t font_size, 
                                            uint8_t mode)
{
    if(dev->pf_oled_draw_num == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_num(x, y, num, len, font_size, mode);
}

adapter_oled_status_e adapter_oled_draw_chinese(adapter_oled_object_t *dev,
                                                uint8_t x, 
                                                uint8_t y,                              
                                                uint8_t num, 
                                                uint8_t font_size,
                                                uint8_t mode)
{
    if(dev->pf_oled_draw_chinese == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_chinese(x, y, num, font_size, mode);
}

adapter_oled_status_e adapter_oled_draw_scroll(adapter_oled_object_t *dev,
                                                    uint8_t num,
                                                    uint8_t space,
                                                    uint8_t mode)
{
    if(dev->pf_oled_draw_scroll == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_scroll(num, space, mode);
}

adapter_oled_status_e adapter_oled_draw_picture(adapter_oled_object_t *dev,
                                                        uint8_t x,
                                                        uint8_t y, 
                                                        uint8_t sizex,
                                                        uint8_t sizey,
                                                        uint8_t *bmp,
                                                        uint8_t mode)
{
    if(dev->pf_oled_draw_picture == NULL) {
        return ADAPTER_OLED_STATUS_ERROR;
    }

    return dev->pf_oled_draw_picture(x, y, sizex, sizey, bmp, mode);
}





