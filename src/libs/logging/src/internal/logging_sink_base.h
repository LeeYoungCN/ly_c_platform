#ifndef LOGGING_LOGGING_SINK_H
#define LOGGING_LOGGING_SINK_H

#include "internal/logging_internal.h"

typedef void (*LoggingSinkLogFunc)(LogRecord record);
typedef void (*LoggingSinkInitFunc)(void);
typedef void (*LoggingSinkCloseFunc)(void);

typedef struct {
    LoggingSinkInitFunc init;
    LoggingSinkLogFunc log;
    LoggingSinkCloseFunc close;
} LoggingSinkBase;

#endif // LOGGING_LOGGING_SINK_H
