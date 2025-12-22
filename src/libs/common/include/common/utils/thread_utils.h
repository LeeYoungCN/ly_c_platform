/**
 * @file thread_utils.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "common/types/error_code_types.h"
#ifndef COMMON_UTILS_THREAD_UTILS_H
#define COMMON_UTILS_THREAD_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/thread_types.h"


/**
 * @brief 获取当前内核态线程ID
 *
 * @return 当前线程ID
 */
ThreadId GetCurrentThreadId(void);

/**
 * @brief 设置线程名称
 *
 * @param name 线程名称
 */
void SetCurrentThreadName(const char* name);

/**
 * @brief 获取当前线程名称
 *
 * @return 当前线程名称，未设置则为空
 */
const char *GetCurrentThreadName(void);

void SetLastErrCode(ErrorCode errCode);

ErrorCode GetLastErrCode(void);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_UTILS_THREAD_UTILS_H
