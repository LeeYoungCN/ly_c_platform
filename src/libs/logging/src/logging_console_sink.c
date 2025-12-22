#include <stdio.h>
#include <stdlib.h>

#include "internal/logging_internal.h"
#include "internal/logging_sink_base.h"
#include "logging/logging.h"

struct LoggingConsoleSink {
    LoggingSinkBase base;
    ConsoleType consoleType;
    FILE *stream;
};

typedef struct LoggingConsoleSink LoggingConsoleSink;

DECLARE_SINK_FUNC(LoggingConsoleSink)

LoggingSinkBase *LoggingGetConsoleSink(ConsoleType consoleType)
{
    LoggingConsoleSink *sink = malloc(sizeof(LoggingConsoleSink));
    INIT_SINK_BASE_FUNC(sink, LoggingConsoleSink)
    sink->consoleType = consoleType;
    if (sink->consoleType == CONSOLE_TYPE_STDOUT) {
        sink->stream = stdout;
    } else {
        sink->stream = stderr;
    }
    return (LoggingSinkBase *)sink;
}

DEFINE_SINK_INIT(LoggingConsoleSink)
{
    (void)sink;
}

DEFINE_SINK_CLOSE(LoggingConsoleSink)
{
    (void)sink;
}

DEFINE_SINK_LOG(LoggingConsoleSink)
{
    if (sink == NULL || sink->log == NULL) {
        return;
    }
    LoggingConsoleSink *consoleSink = (LoggingConsoleSink *)sink;
    char msg[LOG_MSG_LEN] = {'\0'};
    LoggingFormatLogMsg(msg, LOG_MSG_LEN, logMsg);
    fprintf(consoleSink->stream, "%s", msg);
}

DEFINE_SINK_FREE(LoggingConsoleSink)
{
    if (sink == NULL) {
        return;
    }
    free(sink);
}
