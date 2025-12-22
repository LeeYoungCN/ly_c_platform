#include "logging/logging.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#include "common/types/logging_types.h"
#include "common/utils/file_system_utils.h"
#include "internal/logging_internal.h"
#include "internal/logging_sink_base.h"

#define MAX_SINK_CNT 10

LoggingSinkBase *g_sinkList[MAX_SINK_CNT] = {NULL};
uint32_t g_sinkCnt = 0;
LogLevel g_allowedLevel = LOG_ERROR;

void LoggingSetAllowedLevel(LogLevel level)
{
    g_allowedLevel = level;
}

void LoggingRegisterSink(LoggingSinkBase *sink)
{
    g_sinkList[g_sinkCnt++] = sink;
}

void LoggingInit(void)
{
    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->init) {
            (*g_sinkList[i]->init)(g_sinkList[i]);
        }
    }
}

void LoggingClose(void)
{
    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->close) {
            (*g_sinkList[i]->close)(g_sinkList[i]);
        }
    }

    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->free) {
            (*g_sinkList[i]->free)(g_sinkList[i]);
            g_sinkList[i] = NULL;
        }
    }
}

void LoggingLog(const char *file, int line, const char *func, LogLevel level, const char *format, ...)
{
    if (level < g_allowedLevel) {
        return;
    }
    // TODO: Used mempool get LogRecord.
    LogMsg record = {0};
    record.file = Utils_GetFileName(file);
    record.line = line;
    record.func = func;
    record.level = level;
    va_list args;
    va_start(args, format);
    vsnprintf(record.buffer, LOG_BUFFER_LEN, format, args);
    va_end(args);

    for (uint32_t i = 0; i < g_sinkCnt; i++) {
        if (g_sinkList[i] != NULL && g_sinkList[i]->log) {
            (*g_sinkList[i]->log)(g_sinkList[i], &record);
        }
    }
}
