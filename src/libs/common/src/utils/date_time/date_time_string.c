#include <stdbool.h>
#include <string.h>

#include "common/common_error_code.h"
#include "common/constants/date_time_constants.h"
#include "common/cstl/cstl_string.h"
#include "common/debug/debug_log.h"
#include "common/types/date_time_types.h"
#include "common/types/error_code_types.h"
#include "common/utils/date_time_utils.h"
#include "common/utils/error_code_utils.h"

static const char *WEEKDAY_FULL_NAMES[] = {
    "Sunday",     // 星期日
    "Monday",     // 星期一
    "Tuesday",    // 星期二
    "Wednesday",  // 星期三
    "Thursday",   // 星期四
    "Friday",     // 星期五
    "Saturday"    // 星期六
};

// 星期英文名称（简称）
// 索引0-6对应：星期日-星期六
static const char *WEEKDAY_ABBR_NAMES[] = {
    "Sun",  // 星期日
    "Mon",  // 星期一
    "Tue",  // 星期二
    "Wed",  // 星期三
    "Thu",  // 星期四
    "Fri",  // 星期五
    "Sat"   // 星期六
};

// 月份英文名称（全程）
// 索引0-11对应：一月-十二月
static const char *MONTH_FULL_NAMES[] = {
    "January",    // 一月
    "February",   // 二月
    "March",      // 三月
    "April",      // 四月
    "May",        // 五月
    "June",       // 六月
    "July",       // 七月
    "August",     // 八月
    "September",  // 九月
    "October",    // 十月
    "November",   // 十一月
    "December"    // 十二月
};

// 月份英文名称（简称）
// 索引0-11对应：一月-十二月
static const char *MONTH_ABBR_NAMES[] = {
    "Jan",  // 一月
    "Feb",  // 二月
    "Mar",  // 三月
    "Apr",  // 四月
    "May",  // 五月
    "Jun",  // 六月
    "Jul",  // 七月
    "Aug",  // 八月
    "Sep",  // 九月
    "Oct",  // 十月
    "Nov",  // 十一月
    "Dec"   // 十二月
};

const char *GetWeekdayAbbrName(uint32_t weekday)
{
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        SetLastError(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return WEEKDAY_ABBR_NAMES[weekday - MIN_MONTH];
}

const char *GetWeekdayFullName(uint32_t weekday)
{
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        SetLastError(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return WEEKDAY_FULL_NAMES[weekday - MIN_MONTH];
}

const char *GetMonthFullName(uint32_t month)
{
    if (month < MIN_MONTH || month > MAX_MONTH) {
        SetLastError(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return MONTH_FULL_NAMES[month - MIN_MONTH];
}

const char *GetMonthAbbrName(uint32_t month)
{
    if (month < MIN_MONTH || month > MAX_MONTH) {
        SetLastError(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return MONTH_ABBR_NAMES[month - MIN_MONTH];
}

size_t FormatTimeStrinByStamp(CString *string, TimestampMs timestamp, const char *format, TimeZone timeZone)
{
    TimeComponent timeComp = TimeStampMs2Component(timestamp, timeZone);
    return FormatTimeStringByComp(string, &timeComp, format);
}

ErrorCode insertDateTimeNumber(CString *string, uint32_t number, size_t numberLen)
{
    uint32_t tmp = number;
    if (string->length + numberLen >= string->capacity) {
        SetLastError(ERR_COMM_OUT_OF_RANGE);
        DEBUG_LOG_ERR("Failed to insert number: %lu", number);
        return ERR_COMM_OUT_OF_RANGE;
    }

    size_t currIdx = string->length + numberLen;
    while (currIdx > string->length) {
        string->cstr[currIdx - 1] = (char)(tmp % 10 + '0');
        tmp = tmp / 10;
        currIdx--;
    }
    string->length += numberLen;
    SetLastError(ERR_COMM_SUCCESS);
    return ERR_COMM_SUCCESS;
}

size_t FormatTimeStringByComp(CString *string, const TimeComponent *timeComp, const char *format)
{
    if (string == NULL) {
        SetLastError(ERR_COMM_PARAM_NULL);
        DEBUG_LOG_ERR("Param NULL");
        return 0;
    }
    size_t formatIdx = 0;
    size_t bufferIdx = 0;

    for (; bufferIdx < string->capacity && formatIdx < strlen(format); formatIdx++) {
        if (format[formatIdx] != '%') {
            string->cstr[string->length++] = format[formatIdx];
            continue;
        }
        formatIdx++;
        if (formatIdx >= strlen(format)) {
            string->cstr[string->length++] = '%';
            break;
        }
        ErrorCode errCode = ERR_COMM_SUCCESS;
        switch (format[formatIdx]) {
            case 'Y':
                errCode = insertDateTimeNumber(string, timeComp->year, 4);
                break;
            case 'y':
                errCode = insertDateTimeNumber(string, timeComp->year, 2);
                break;
            case 'm':
                errCode = insertDateTimeNumber(string, timeComp->month, 2);
                break;
            case 'd':
                errCode = insertDateTimeNumber(string, timeComp->day, 2);
                break;
            case 'H':
                errCode = insertDateTimeNumber(string, timeComp->hour, 2);
                break;
            case 'M':
                errCode = insertDateTimeNumber(string, timeComp->minute, 2);
                break;
            case 'S':
                errCode = insertDateTimeNumber(string, timeComp->second, 2);
                break;
            case 'B':  // 完整月份名称
                errCode = CString_Append(string, "%s", GetMonthFullName(timeComp->month));
                break;
            case 'b':  // 缩写月份名称
            case 'h':  // 缩写月份名称
                errCode = CString_Append(string, "%s", GetMonthAbbrName(timeComp->month));
                break;
            case 'A':  // 完整星期名称
                errCode = CString_Append(string, "%s", GetWeekdayFullName(timeComp->wday));
                break;
            case 'a':  // 缩写星期名称
                errCode = CString_Append(string, "%s", GetWeekdayAbbrName(timeComp->wday));
                break;
            case '%':
                string->cstr[string->length++] = '%';
                break;
            case '3':
                if (formatIdx + 1 < strlen(format) && format[formatIdx + 1] == 'f') {
                    formatIdx++;
                    errCode = insertDateTimeNumber(string, timeComp->millis, 3);
                } else {
                    errCode = CString_Append(string, "%c", format + formatIdx - 1);
                }
                break;
            default:
                errCode = CString_Append(string, "%c", *(format + formatIdx - 1));
                break;
        }
        if (errCode != ERR_COMM_SUCCESS) {
            break;
        }
    }
    if (formatIdx < strlen(format) || string->length >= string->capacity) {
        DEBUG_LOG_ERR("Incomplete format processing (remaining: %s), message: %s", format + formatIdx, GetLastErrStr());
        bufferIdx = 0;
    } else {
        SetLastError(ERR_COMM_SUCCESS);
        DEBUG_LOG_DBG("[SUCCESS] Format time string, message: %s.", GetLastErrStr());
    }

    string->cstr[string->length] = '\0';

    return string->length;
}
