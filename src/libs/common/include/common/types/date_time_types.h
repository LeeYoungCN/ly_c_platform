#ifndef COMMON_FILE_SYSTEM_TYPES_H
#define COMMON_FILE_SYSTEM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// 时间戳(ms)
typedef int64_t TimestampSec;  // 秒级时间戳（自UTC epoch）
typedef int64_t TimestampMs;       // 毫秒级时间戳

/**
 * @brief 时间间隔类型（不同精度）
 */
typedef int64_t DurationSec;  // 秒级间隔
typedef int64_t DurationMs;   // 毫秒级间隔

/**
 * @brief 时间分量结构体，用于表示分解后的日期和时间信息（含毫秒）
 *
 * 该结构体将时间分解为年、月、日、时、分、秒、毫秒等独立字段，
 * 方便时间的格式化、计算和展示。
 */
typedef struct {
    uint32_t year;    ///< 年份（4位完整年份，如2024）
    uint32_t month;   ///< 月份（1-12，1表示一月，12表示十二月）
    uint32_t day;     ///< 日期（1-31，当月的第几天）
    uint32_t hour;    ///< 小时（0-23，24小时制）
    uint32_t minute;  ///< 分钟（0-59）
    uint32_t second;  ///< 秒（0-59）
    uint32_t millis;  ///< 毫秒（0-999）
    uint32_t wday;    ///< 星期几（0-6，具体对应关系取决于系统，通常0为星期日）
    uint32_t yday;    ///< 年内天数（0-365，0表示1月1日）
} TimeComponent;

/**
 * @brief 时区类型（预定义常用时区）
 */
typedef enum {
    TZ_UTC = 0,  // 世界协调时间
    TZ_LOCAL,    // 本地时区（跟随系统）
} TimeZone;

static inline const char *GetTimeZoneString(TimeZone zone)
{
    switch (zone) {
        case TZ_UTC:
            return "UTC";
        case TZ_LOCAL:
        default:
            return "LOCAL";
    }
}

#ifdef __cplusplus
}
#endif
#endif  // COMMON_FILE_SYSTEM_TYPES_H
