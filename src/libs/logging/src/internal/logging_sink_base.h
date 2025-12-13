#ifndef LOGGING_LOGGING_SINK_BASE_H
#define LOGGING_LOGGING_SINK_BASE_H

#include "internal/logging_internal.h"

typedef void (*LoggingSinkLogFunc)(const LogRecord *record);
typedef void (*LoggingSinkInitFunc)(void);
typedef void (*LoggingSinkCloseFunc)(void);

struct LoggingSinkBase {
    LoggingSinkInitFunc init;
    LoggingSinkLogFunc log;
    LoggingSinkCloseFunc close;
};

#endif // LOGGING_LOGGING_SINK_BASE_H
