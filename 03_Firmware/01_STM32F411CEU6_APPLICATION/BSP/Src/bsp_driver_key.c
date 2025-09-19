/**
 * @file bsp_driver_key.c
 * @author ZB (2536566200@qq.com)
 * @brief 按键驱动
 * @version 0.1
 * @date 2025-09-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bsp_driver_key.h"

bsp_driver_key_object_t _key_drv_dev[KEY_DEV_MAX] = {0};    /**< 按键驱动 */

bsp_driver_key_status_e bsp_driver_key_register(uint32_t index, bsp_driver_key_object_t *dev)
{
    if(dev == NULL) {
        return KEY_DRIVER_ERROR;
    }

    _key_drv_dev[index].index           = index;                           
    _key_drv_dev[index].pf_key_init     = dev->pf_key_init;                
    _key_drv_dev[index].pf_key_deinit   = dev->pf_key_deinit;              
    _key_drv_dev[index].pf_key_scan     = dev->pf_key_scan;                
    _key_drv_dev[index].pf_key_sleep    = dev->pf_key_sleep;
    _key_drv_dev[index].pf_key_weakup   = dev->pf_key_weakup;
	_key_drv_dev[index].pf_get_systime  = dev->pf_get_systime;
	_key_drv_dev[index].pf_key_cb		= dev->pf_key_cb;

    return KEY_DRIVER_OK;
}

bsp_driver_key_status_e bsp_driver_key_init(const bsp_driver_key_object_t *dev)
{
    if((dev == NULL) || 
        (dev->pf_key_init == NULL)) {
        return KEY_DRIVER_ERROR;
    }

    dev->pf_key_init(dev);

    return KEY_DRIVER_OK;
}

bsp_driver_key_status_e bsp_driver_key_deinit(const bsp_driver_key_object_t *dev)
{
    if((dev == NULL) || 
        (dev->pf_key_deinit == NULL)) {
        return KEY_DRIVER_ERROR;
    }

    dev->pf_key_deinit(dev);

    return KEY_DRIVER_OK;
}

bsp_driver_key_status_e bsp_driver_key_get_object(uint32_t index, bsp_driver_key_object_t *dev)
{
	if((index >= KEY_DEV_MAX) || 
		(dev == NULL)){
		return KEY_DRIVER_ERROR;	
	}

	dev = &_key_drv_dev[index];
	
	return KEY_DRIVER_OK;
}


bsp_driver_key_status_e bsp_driver_key_scan(void)
{
    uint8_t state = 0;
    for(uint8_t i = 0; i < KEY_DEV_MAX; i++) {
        /**< 1.获取当前按键电平 */
        if(_key_drv_dev[i].pf_key_scan != NULL) {
            /**< 1.1 扫描按键 */
            _key_drv_dev[i].pf_key_scan(&_key_drv_dev[i], &state);

			/**< 1.2 更新系统时间 */
			_key_drv_dev[i].pf_get_systime(&_key_drv_dev[i].key_state.time_count);
			
            /**< 1.3 按键被触发 */
            if(state == 1) {
                /**< 1.3.2 记录消抖时间 */
                if(_key_drv_dev[i].key_state.debounce_time == 0) {
                    _key_drv_dev[i].key_state.debounce_time = _key_drv_dev[i].key_state.time_count;
                }

                /**< 1.3.3 判断是否消抖完成 */
                if((_key_drv_dev[i].key_state.time_count - _key_drv_dev[i].key_state.debounce_time) >= KEY_DEV_DEBUNCE_TIME) {
                    _key_drv_dev[i].key_state.key_state = KEY_DRIVER_PRESS_EVENT;           			            /**< 记录按下 */

                    /**< 1.3.4 记录按下长按开始时间 */
                    if(_key_drv_dev[i].key_state.long_time == 0) {
                        _key_drv_dev[i].key_state.long_time = _key_drv_dev[i].key_state.time_count; 
                    }
                }

				/**< 1.3.5 判断长按 */
				if((_key_drv_dev[i].key_state.key_last_state == KEY_DRIVER_PRESS_EVENT) &&
					((_key_drv_dev[i].key_state.time_count - _key_drv_dev[i].key_state.long_time) >= KEY_DEV_LONG_TIME)) {
					_key_drv_dev[i].key_state.key_state = KEY_DRIVER_LONG_PRESS_EVENT;                              /**< 记录长按事件 */
				}
            }

            /**< 1.4 判断按键释放 */
            else {
                /**< 1.4.1 清空消抖时间 */
                _key_drv_dev[i].key_state.debounce_time = 0;                            			                /**< 消抖时间清空 */

                /**< 1.4.2 设置释放事件 */
                _key_drv_dev[i].key_state.key_state = KEY_DRIVER_RELEASE_EVENT;                                     /**< 记录释放事件 */
				
				/**< 1.4.3 判断单击 */
                if(_key_drv_dev[i].key_state.key_last_state == KEY_DRIVER_PRESS_EVENT) {				            /**< 上一次是按下状态 */
					/**< 1.4.4 判断双击 */
					if((_key_drv_dev[i].key_state.last_short_press_time != 0) &&		                            /**< 上一次短按时间不为0 */
						((_key_drv_dev[i].key_state.time_count - _key_drv_dev[i].key_state.last_short_press_time) < KEY_DEV_DOUBLE_TIME)) {
						_key_drv_dev[i].key_state.key_state = KEY_DRIVER_DOUBLE_SHORT_PRESS_EVENT;      	        /**< 记录双击事件 */
                        _key_drv_dev[i].key_state.last_short_press_time = 0;                                        /**< 上一次短按时间清空 */
					} else {
                        _key_drv_dev[i].key_state.last_short_press_time = _key_drv_dev[i].key_state.time_count;     /**< 记录上一次短按时间 */
                        _key_drv_dev[i].key_state.key_state = KEY_DRIVER_SHORT_PRESS_EVENT;                         /**< 记录短按事件 */
                    } 
                }
				
                /**< 1.4.5 超时后取消双击等待 */ 
                if((_key_drv_dev[i].key_state.time_count - _key_drv_dev[i].key_state.last_short_press_time) > KEY_DEV_DOUBLE_TIME) {
                    _key_drv_dev[i].key_state.last_short_press_time = 0;
                }

				/**< 1.4.6 清空长按时间*/
				if((_key_drv_dev[i].key_state.key_last_state == KEY_DRIVER_RELEASE_EVENT) &&			                    /**< 上一次是释放状态 */
					((_key_drv_dev[i].key_state.time_count - _key_drv_dev[i].key_state.long_time) > KEY_DEV_LONG_TIME)) {   /**< 长按时间 */
					_key_drv_dev[i].key_state.long_time = 0;                                                                /**< 长按时间清空 */
				}
            }

            /**< 1.5 调用事件回调 */
            if(_key_drv_dev[i].pf_key_cb != NULL) {

                /**< 1.5.1 启动回调 */
                _key_drv_dev[i].pf_key_cb(&_key_drv_dev[i]);    
                
                /**< 1.5.2 将此次事件记录到上一次事件中 */
				_key_drv_dev[i].key_state.key_last_state = _key_drv_dev[i].key_state.key_state;
            }
        }
    }
    return KEY_DRIVER_OK;
}


