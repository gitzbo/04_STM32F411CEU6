/**
 * @file service_wdt.c
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗服务
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "service_wdg.h"

#include "bsp_iwdg.h"
#include "adapter_iwdg.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#ifndef SERVICE_MAX_DAEMON_TASK
#define SERVICE_MAX_DAEMON_TASK 20
#endif


static service_wdg_task_info_t _g_iwdg_task_info_list[SERVICE_MAX_DAEMON_TASK]; /**< 线程信息列表 */
static SemaphoreHandle_t _g_iwdg_mutex = {0};                                   /**< iwdg 互斥锁 */
static void _service_wdg_daemon_task(void *pParams);                            /**< 守护线程 */

service_wdg_status_e service_wdg_init(void)
{
    /**< 1.将看门狗实例，注册看门狗对象中 */
    adapter_iwdg_object_t iwdg_obj = {
        .index          = 0,
        .user_data      = NULL,
        .pf_iwdg_init   = bsp_iwdg_init,
        .pf_iwdg_deinit = bsp_iwdg_deinit,
        .pf_iwdg_feed   = bsp_iwdg_feed,
    };
    adapter_iwdg_register(iwdg_obj.index, &iwdg_obj);

    /**< 2.初始化看门狗 */
    adapter_iwdg_init(&iwdg_obj);

    /**< 3.创建看门狗线程 */

    /**< 4.创建互斥锁 */
    _g_iwdg_mutex = xSemaphoreCreateMutex();
    if (NULL == _g_iwdg_mutex) {
        return SERVICE_WDG_STATUS_ERROR;
    }



	return SERVICE_WDG_STATUS_OK;
}

service_wdg_status_e service_wdg_daemon_register(const char *p_task_name, const uint32_t heart_beat_timeout_ms, void (*pf_timeout_cb)(void))
{
    int ret = -1;
    if (pdTRUE == xSemaphoreTake(_g_iwdg_mutex, portMAX_DELAY)) {
        for (uint8_t i = 0; i < SERVICE_MAX_DAEMON_TASK; i++) {
            if (!_g_iwdg_task_info_list[i].is_registered) {
                // snprintf(daemonInfoList[i].taskName, sizeof(daemonInfoList[i].taskName), "%s", pTaskName);

                // 填充任务信息
                _g_iwdg_task_info_list[i].last_heart_beat_tick      = xTaskGetTickCount();
                _g_iwdg_task_info_list[i].heart_beat_timeout_tick   = pdMS_TO_TICKS(heart_beat_timeout_ms);
                _g_iwdg_task_info_list[i].pf_timeout_cb             = pf_timeout_cb;
                _g_iwdg_task_info_list[i].is_registered             = true;

                // 成功
                ret = 0;
                break;
            }
        }

        xSemaphoreGive(_g_iwdg_mutex);
    }

    if (0 != ret) {
        // ESP_LOGE(MOD_TAG, "task '%s' register failed", pTaskName);
    }
    else {
        // ESP_LOGI(MOD_TAG, "task '%s' register success", pTaskName);
    }

    return ret;
}

/**
 * @brief 	 更新指定任务的心跳
 * @param 	 pTaskName, 守护任务的名称，用于识别特定的任务
 * @retval 	 0表示心跳成功更新，-1表示参数无效或任务未找到
 * @author 	 chenningzhan
 * @note 	 None
 */
int service_wdg_daemon_heart_beat(const char *task_name)
{
    if (NULL == task_name) {
        return -1;
    }

    int ret = -1;
    if (pdTRUE == xSemaphoreTake(_g_iwdg_mutex, portMAX_DELAY))
    {
        for (int i = 0; i < SERVICE_MAX_DAEMON_TASK; i++)
        {
            // 跳过未注册的任务
            if (!_g_iwdg_task_info_list[i].is_registered) {
                continue;
            }

            if (strcmp(_g_iwdg_task_info_list[i].task_name, task_name) == 0) {
                _g_iwdg_task_info_list[i].last_heart_beat_tick = xTaskGetTickCount();

                ret = 0;  // 标记成功
                break;    // 提前退出循环
            }
        }

        xSemaphoreGive(_g_iwdg_mutex);
    }

    // 记录未找到任务的警告
    if (0 != ret) {
        // ESP_LOGW(MOD_TAG, "heartbeat failed: task '%s' not registered", pTaskName);
    }

    return ret;
}

static void _service_wdg_daemon_task(void *pParams)
{
    (void)pParams;

    static uint32_t lastWakeTime;
    lastWakeTime = xTaskGetTickCount();

    adapter_iwdg_object_t iwdg_obj;
    adapter_iwdg_get_object(0, &iwdg_obj);

    for (;;) {
        if (pdTRUE == xSemaphoreTake(_g_iwdg_mutex, portMAX_DELAY)) {
            for (int i = 0; i < SERVICE_MAX_DAEMON_TASK; i++) {
                if (!_g_iwdg_task_info_list[i].is_registered) {
                    continue;
                }

                uint32_t currentTick  = xTaskGetTickCount();
                uint32_t elapsedTicks = currentTick - _g_iwdg_task_info_list[i].last_heart_beat_tick;

                /**< 检测是否超时 */ 
                if (elapsedTicks >= _g_iwdg_task_info_list[i].heart_beat_timeout_tick) {
                    // ESP_LOGW(MOD_TAG,
                    //          "Task '%s' timeout! (Elapsed: %lu ms)",
                    //          _g_iwdg_task_info_list[i].taskName,
                    //          (unsigned long)pdTICKS_TO_MS(elapsedTicks));

                    /**< 触发超时回调（如果已注册） */ 
                    if (NULL != _g_iwdg_task_info_list[i].pf_timeout_cb) {
                        _g_iwdg_task_info_list[i].pf_timeout_cb();
                    }

                    /**< 直接重启 */
//                    HAL_NVIC_SystemReset();
                }
            }
            xSemaphoreGive(_g_iwdg_mutex);
        }
        
        /**< 喂狗 */
        adapter_iwdg_feed(&iwdg_obj);
        vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(SERVICE_WDG_DAEMON_PERIOD_MS));
    }
}







