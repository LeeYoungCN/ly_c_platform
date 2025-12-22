#include "common/utils/date_time_utils.h"

#include <stdint.h>

#include "common/common_error_code.h"
#include "common/constants/date_time_constants.h"
#include "common/debug/debug_log.h"
#include "common/types/date_time_types.h"
#include "common/types/error_code_types.h"
#include "common/utils/error_code_utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif  // _WIN32
#include <stdbool.h>
#include <time.h>

static ErrorCode SafeLocalTime(time_t timer, struct tm* timeInfo)
{
#ifdef _WIN32
    // Windows 使用 localtime_s
    errno_t err = localtime_s(timeInfo, &timer);
    if (err != 0) {
        SetLastError(ERR_COMM_TIMESTAMP_INVALID);
        特别处理负数时间戳的错误提示
        if (timer < 0) {
            DEBUG_LOG_WARN("[FAILED] localtime_s may not support negative. time: %lld, err: %d", timer, err);
        } else {
            DEBUG_LOG_ERR("[FAILED] localtime_s. time: %lld, err: %d", timer, err);
        }
        return false;
    }
#else
    // Linux/macOS 使用 localtime_r
    if (localtime_r(&timer, timeInfo) == NULL) {
        SetLastError(ERR_COMM_TIMESTAMP_INVALID);
        DEBUG_LOG_ERR("[FAILED] localtime_r. time: %lld, msg: %s", timer, GetLastErrStr());
        return ERR_COMM_TIMESTAMP_INVALID;
    }
#endif
    SetLastError(ERR_COMM_SUCCESS);
    return ERR_COMM_SUCCESS;
}

static ErrorCode SafeGmtime(time_t timer, struct tm* timeInfo)
{
    if (timeInfo == NULL) {
        SetLastError(ERR_COMM_PARAM_NULL);
        return ERR_COMM_PARAM_NULL;
    }
#ifdef _WIN32
    // Windows下使用gmtime_s，增加负数时间戳检查
    errno_t err = gmtime_s(timeInfo, &timer);
    if (err != 0) {
        DtInternal_SetLastError(ERR_COMM_TIMESTAMP_INVALID);
        // 针对负数时间戳的错误做特殊提示
        if (timer < 0) {
            DEBUG_LOG_WARN("[FAILED] gmtime_s may not support negative time: %lld, err: %d", timer, err);
        } else {
            DEBUG_LOG_ERR("[FAILED] gmtime_s time: %lld, err: %d", timer, err);
        }
        return ERR_COMM_TIMESTAMP_INVALID;
    }
#else
    // Linux/macOS使用gmtime_r（对负数时间戳支持更完善）
    if (gmtime_r(&timer, timeInfo) == NULL) {
        SetLastError(ERR_COMM_TIMESTAMP_INVALID);
        DEBUG_LOG_ERR("[FAILED] gmtime_r. time: %lld, msg: %s", timer, GetLastErrStr());
        return ERR_COMM_TIMESTAMP_INVALID;
    }
#endif
    SetLastError(ERR_COMM_SUCCESS);
    return ERR_COMM_SUCCESS;
}

void ConvertTmToTimeComp(const struct tm timeInfo, int32_t millis, TimeComponent* timeComp)
{
    timeComp->year = (uint32_t)(TIME_COMP_START_YEAR + timeInfo.tm_year);
    timeComp->month = (uint32_t)(TIME_COMP_START_MONTH + timeInfo.tm_mon);
    timeComp->day = (uint32_t)(timeInfo.tm_mday);
    timeComp->hour = (uint32_t)(timeInfo.tm_hour);
    timeComp->minute = (uint32_t)(timeInfo.tm_min);
    timeComp->second = (uint32_t)(timeInfo.tm_sec);
    timeComp->millis = (uint32_t)(millis);
    timeComp->wday = (uint32_t)(timeInfo.tm_wday);
    timeComp->yday = (uint32_t)(timeInfo.tm_yday);
}

TimestampMs GetCurrentTimestampMs(void)
{
    SetLastError(ERR_COMM_SUCCESS);
#ifdef _WIN32
    FILETIME ft;
    // 获取当前系统时间，以FILETIME格式存储（从Windows纪元1601-01-01 00:00:00开始的100纳秒间隔数）
    GetSystemTimeAsFileTime(&ft);

    // 将FILETIME的高低位 DWORD 合并为64位无符号整数，得到完整的100纳秒单位时间戳
    const int FILETIME_HIGH_SHIFT_BITS = 32;  // FILETIME高32位左移位数
    uint64_t file_time = ((uint64_t)ft.dwHighDateTime << FILETIME_HIGH_SHIFT_BITS) | ft.dwLowDateTime;

    // 转换为Unix时间戳（毫秒级）：
    // 1. 先将100纳秒单位转换为毫秒（除以10000，因1毫秒=10000×100纳秒）
    // 2. 减去Windows纪元到Unix纪元（1970-01-01 00:00:00）的毫秒差值，得到标准Unix时间戳
    const uint64_t HUNDRED_NANOSECONDS_PER_MILLISECOND = 10000;
    return (TimestampMs)((file_time / HUNDRED_NANOSECONDS_PER_MILLISECOND)  // 转换为毫秒
                         - WINDOWS_EPOCH_TO_UNIX_EPOCH_MS                   // 校正到Unix纪元
    );
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (TimestampMs)tv.tv_sec * 1000000 + tv.tv_usec;
#endif
}

TimeComponent GetCurrentTimeComponent(void)
{
    return TimeStampMs2Component(GetCurrentTimestampMs(), TZ_LOCAL);
}

TimeComponent LocalTimeComponent(TimestampMs timestamp)
{
    return TimeStampMs2Component(timestamp, TZ_LOCAL);
}

TimeComponent UtcTimeComponent(TimestampMs timestamp)
{
    return TimeStampMs2Component(timestamp, TZ_UTC);
}

TimeComponent TimeStampMs2Component(TimestampMs timestamp, TimeZone timeZone)
{
    time_t timer = (time_t)(timestamp / MILLIS_PER_SECOND);
    int32_t millis = (int32_t)(timestamp % MILLIS_PER_SECOND);

    struct tm timeInfo = {0};
    TimeComponent timeComp = {0};
    ErrorCode rst = false;
    switch (timeZone) {
        case TZ_UTC:
            rst = SafeGmtime(timer, &timeInfo);
            break;
        case TZ_LOCAL:
        default:
            rst = SafeLocalTime(timer, &timeInfo);
    }

    if (rst != ERR_COMM_SUCCESS) {
        DEBUG_LOG_ERR("[FAILED] Get time info, zone: %s, message: %s.", GetTimeZoneString(timeZone), GetLastErrStr());
    } else {
        ConvertTmToTimeComp(timeInfo, millis, &timeComp);
        SetLastError(ERR_COMM_SUCCESS);
        DEBUG_LOG_DBG("[SUCCESS] Get time info, zone: %s, message: %s.", GetTimeZoneString(timeZone), GetLastErrStr());
    }
    return timeComp;
}
