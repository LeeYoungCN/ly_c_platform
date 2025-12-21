#include "common/common_error_code.h"
#include "common/constants/date_time_constants.h"
#include "common/types/date_time_types.h"
#include "common/utils/date_time_utils.h"
#include "internal/utils/date_time_internal.h"

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

const char* GetWeekdayAbbrName(uint32_t weekday)
{
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        DtInter_SetLastErr(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return WEEKDAY_ABBR_NAMES[weekday - MIN_MONTH];
}

const char* GetWeekdayFullName(uint32_t weekday)
{
    if (weekday < MIN_WEEKDAY || weekday > MAX_WEEKDAY) {
        DtInter_SetLastErr(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return WEEKDAY_FULL_NAMES[weekday - MIN_MONTH];
}

const char *GetMonthFullName(uint32_t month)
{
    if (month < MIN_MONTH || month > MAX_MONTH) {
        DtInter_SetLastErr(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return MONTH_FULL_NAMES[month - MIN_MONTH];
}

const char *GetMonthAbbrName(uint32_t month)
{
    if (month < MIN_MONTH || month > MAX_MONTH) {
        DtInter_SetLastErr(ERR_COMM_PARAM_INVALID);
        return "";
    }
    return MONTH_ABBR_NAMES[month - MIN_MONTH];
}
