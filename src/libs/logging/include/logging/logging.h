/**
 * @file logging.h
 * @author your name (you@domain.com)
 * @brief 日志模块头文件
 * @version 0.1
 * @date 2025-11-29
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef LOGGING_LOGGING_H
#define LOGGING_LOGGING_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { LOG_DEBUG = 0, LOG_INFO, LOG_WARNING, LOG_ERROR, LOG_PANIC } LogLevel;

/**
 * @brief 日志打印接口
 *
 * @param file 文件名称
 * @param line 行号
 * @param func 函数名
 * @param level 日志等级
 * @param format 日志格式
 * @param ...
 */
void logging_log(const char *file, int line, const char *func, LogLevel level, const char *format, ...);

#ifdef __cplusplus
}  // 结束 extern "C" 块
#endif

#endif  // LOGGING_LOGGING_H
