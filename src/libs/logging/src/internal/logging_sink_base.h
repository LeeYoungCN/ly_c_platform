#ifndef LOGGING_LOGGING_SINK_BASE_H
#define LOGGING_LOGGING_SINK_BASE_H

#include "internal/logging_internal.h"
#include "logging/logging.h"

typedef void (*LoggingSinkLogFunc)(LoggingSinkBase *sink, LogMsg *record);
typedef void (*LoggingSinkInitFunc)(LoggingSinkBase *sink);
typedef void (*LoggingSinkCloseFunc)(LoggingSinkBase *sink);
typedef void (*LoggingSinkFreeFunc)(LoggingSinkBase *sink);

struct LoggingSinkBase {
    LoggingSinkInitFunc init;
    LoggingSinkLogFunc log;
    LoggingSinkCloseFunc close;
    LoggingSinkFreeFunc free;
};

#define DECLARE_SINK_FUNC(SinkName)                                    \
    static void SinkName##_Init(LoggingSinkBase *sink);                \
    static void SinkName##_Close(LoggingSinkBase *sink);               \
    static void SinkName##_Log(LoggingSinkBase *sink, LogMsg *logMsg); \
    static void SinkName##_Free(LoggingSinkBase *sink);

#define DEFINE_SINK_INIT(SinkName) void SinkName##_Init(LoggingSinkBase *sink)
#define DEFINE_SINK_CLOSE(SinkName) void SinkName##_Close(LoggingSinkBase *sink)
#define DEFINE_SINK_LOG(SinkName) void SinkName##_Log(LoggingSinkBase *sink, LogMsg *logMsg)
#define DEFINE_SINK_FREE(SinkName) void SinkName##_Free(LoggingSinkBase *sink)

#define INIT_SINK_BASE_FUNC(sinkPtr, SinkName)    \
    {                                             \
        (sinkPtr)->base.init = SinkName##_Init;   \
        (sinkPtr)->base.close = SinkName##_Close; \
        (sinkPtr)->base.log = SinkName##_Log;     \
        (sinkPtr)->base.free = SinkName##_Free;   \
    }

#endif  // LOGGING_LOGGING_SINK_BASE_H
