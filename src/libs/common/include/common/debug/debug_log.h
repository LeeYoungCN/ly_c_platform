#ifndef COMMON_DEBUG_DEBUG_LOG_H
#define COMMON_DEBUG_DEBUG_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/logging_types.h"

void CommonDebugLog(const char* file, int line, const char* func, LogLevel level, const char* fmt, ...);

#if defined(NDEBUG) && !defined(ENABLE_TEST)
// Release模式：空操作，显式消费所有参数避免警告
#define DEBUG_LOG(level, fmt, ...) (static_cast<void>(0))
#else
// Debug模式：实际日志输出，支持所有级别
#define DEBUG_LOG(level, fmt, ...)                                                               \
    do {                                                                                         \
        CommonDebugLog(__FILE__, __LINE__, __FUNCTION__, level, fmt __VA_OPT__(, ) __VA_ARGS__); \
    } while (0)
#endif

#define DEBUG_LOG_DBG(fmt, ...) DEBUG_LOG(LOG_DEBUG, fmt __VA_OPT__(, ) __VA_ARGS__);

#define DEBUG_LOG_INFO(fmt, ...) DEBUG_LOG(LOG_INFO, fmt __VA_OPT__(, ) __VA_ARGS__);

#define DEBUG_LOG_WARN(fmt, ...) DEBUG_LOG(LOG_WARN, fmt __VA_OPT__(, ) __VA_ARGS__);

#define DEBUG_LOG_ERR(fmt, ...) DEBUG_LOG(LOG_ERROR, fmt __VA_OPT__(, ) __VA_ARGS__);

#define DEBUG_LOG_FATAL(fmt, ...)                       \
    do {                                                \
        DEBUG_LOG(LOG_FATAL, fmt __VA_OPT__(, ) __VA_ARGS__);   \
        std::abort();                                   \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif  // COMMON_DEBUG_DEBUG_LOG_H
