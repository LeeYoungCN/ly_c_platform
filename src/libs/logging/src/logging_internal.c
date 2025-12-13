/**
 * @file macros.h
 * @author your name (you@domain.com)
 * @brief 公共宏定义
 * @version 0.1
 * @date 2025-07-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "internal/logging_internal.h"
#include "logging/logging.h"

const char *Logging_GetLogLevelName(LogLevel level)
{
    switch (level) {
        case LOG_DEBUG:
            return "DBG";
        case LOG_INFO:
            return "INF";
        case LOG_WARNING:
            return "WARN";
        case LOG_ERROR:
            return "ERR";
        case LOG_FATAL:
            return "PANIC";
        default:
            return "Unkown";
    }
}
