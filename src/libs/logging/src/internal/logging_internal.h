/**
 * @file logging.h
 * @author your name (you@domain.com)
 * @brief 日志模块内部头文件
 * @version 0.1
 * @date 2025-11-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOGGING_LOGGING_INTERNAL_H
#define LOGGING_LOGGING_INTERNAL_H

#include "logging/logging.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char *file;
    int line;
    const char *func;
} LogSource;

/**
 * @brief Get the Log Level Name object
 * 
 * @param level 日志级别
 * @return const char* 日志级别字符串
 */
const char *GetLogLevelName(LogLevel level);

#ifdef __cplusplus
}
#endif

#endif  // LOGGING_LOGGING_INTERNAL_H
