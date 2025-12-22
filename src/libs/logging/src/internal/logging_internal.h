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

#ifndef LOGGING_INTERNAL_LOGGING_INTERNAL_H
#define LOGGING_INTERNAL_LOGGING_INTERNAL_H

#include "common/types/logging_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define LOG_BUFFER_LEN (128)
#define LOG_MSG_LEN (256)

typedef struct {
    const char *file;
    int line;
    const char *func;
    int timeStamp;
    LogLevel level;
    char buffer[LOG_BUFFER_LEN];
} LogMsg;

void LoggingFormatLogMsg(char *buffer, uint32_t size, LogMsg *logMsg);

#ifdef __cplusplus
}
#endif

#endif  // LOGGING_INTERNAL_LOGGING_INTERNAL_H
