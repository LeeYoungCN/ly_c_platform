#include "logging/logging.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "common/os/file_system.h"
#include "internal/logging_internal.h"
#include "internal/logging_sink_base.h"

#define MAX_SINK_CNT 10

LoggingSinkBase *g_sinkList[MAX_SINK_CNT] = {NULL};
uint32_t g_sinkCnt = 0;
LogLevel g_allowedLevel = LOG_ERROR;

void Logging_SetAllowedLevel(LogLevel level)
{
    g_allowedLevel = level;
}

void Logging_RegisterSink(LoggingSinkBase *sink)
{
    g_sinkList[g_sinkCnt++] = sink;
}

void Logging_Init(void)
{
    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->init) {
            (*g_sinkList[i]->init)();
        }
    }
}

void Logging_Close(void)
{
    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->close) {
            (*g_sinkList[i]->close)();
        }
    }
}

void Logging_Log(const char *file, int line, const char *func, LogLevel level, const char *format, ...)
{
    if (level < g_allowedLevel) {
        return;
    }

    LogRecord record = {0};
    record.file = file;
    record.line = line;
    record.func = func;
    record.level = level;
    va_list args;
    va_start(args, format);
    vsnprintf(record.buffer, LOG_BUFFER_LEN, format, args);
    va_end(args);

    if (g_sinkCnt == 0) {
        printf("[%s:%d] [%s] %s\n",
               FS_GetFileName(record.file),
               record.line,
               Logging_GetLogLevelName(record.level),
               record.buffer);
        return;
    }

    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->log) {
            (*g_sinkList[i]->log)(&record);
        }
    }
}
