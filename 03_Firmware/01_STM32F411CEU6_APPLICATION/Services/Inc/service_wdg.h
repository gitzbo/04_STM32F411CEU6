/**
 * @file service_wdg.h
 * @author ZB (2536566200@qq.com)
 * @brief 看门狗服务
 * 1. 实现看门狗守护线程
 * @version 0.1
 * @date 2025-10-30
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef __SERVICE_WDG_H__
#define __SERVICE_WDG_H__

#include <stdint.h>
#include <stdbool.h>

#define SERVICE_WDG_DAEMON_PERIOD_MS (0.5 * 1000)  // 单位：毫秒

typedef enum {
    SERVICE_WDG_STATUS_OK = 0,
    SERVICE_WDG_STATUS_ERROR,
}service_wdg_status_e;

typedef struct {
    char task_name[32];                     // 任务标识名
    uint32_t last_heart_beat_tick;          // 最后心跳时间戳
    uint32_t heart_beat_timeout_tick;       // 超时阈值
    void (*pf_timeout_cb)(void);            // 超时回调
    bool is_registered;                     // 注册状态
} service_wdg_task_info_t;

/**
 * @brief 看门狗服务初始化
 * 
 * @return service_wdg_status_e 运行状态
 */
service_wdg_status_e service_wdg_init(void);

/**
 * @brief 	 注册守护进程任务
 * @param 	 pTaskName, 守护任务的名称，用于识别特定的任务
 * @param 	 heartbeatTimeoutMs, 心跳超时时间，单位为毫秒
 * @param 	 timeoutCallback, 心跳超时回调函数指针
 * @retval 	 返回0表示注册成功，非0表示注册失败
 * @author 	 chenningzhan
 * @note 	 用于向守护进程注册一个任务，守护进程会监控该任务的心跳，并在心跳超时时调用回调函数通知用户
 */
service_wdg_status_e service_wdg_daemon_register(const char *p_task_name, const uint32_t heartbeatTimeoutMs, void (*pf_timeout_cb)(void));

/**
 * @brief 	 更新指定任务的心跳
 * @param 	 pTaskName, 守护任务的名称，用于识别特定的任务
 * @retval 	 0表示心跳成功更新，-1表示参数无效或任务未找到
 * @author 	 chenningzhan
 * @note 	 None
 */
int service_wdg_daemon_heart_beat(const char *task_name);

/**
 * @brief 守护线程
 * 
 * @param pParams 用户参数
 */
void service_wdg_task(void *pParams);


#endif


