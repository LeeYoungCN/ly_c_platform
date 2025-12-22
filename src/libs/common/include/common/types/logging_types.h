#ifndef COMMON_TYPES_LOGGING_TYPES_H
#define COMMON_TYPES_LOGGING_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
} LogLevel;

inline const char *Logging_GetLogLevelName(LogLevel level)
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
            return "FATAL";
        default:
            return "Unkown";
    }
}

#ifdef __cplusplus
}
#endif
#endif // COMMON_TYPES_LOGGING_TYPES_H
