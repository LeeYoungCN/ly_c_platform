#ifndef COMMON_UTILS_DATE_TIME_UTILS_H
#define COMMON_UTILS_DATE_TIME_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "common/cstl/cstl_string.h"
#include "common/types/date_time_types.h"
#include "common/types/error_code_types.h"

/**
 * @brief 获取当前系统时间的毫秒级时间戳
 * @details 以Unix纪元（1970-01-01 00:00:00 UTC）为基准，返回当前时间的毫秒数
 * @return TimestampMs 毫秒级时间戳
 * @note 跨平台实现：Windows使用GetSystemTimeAsFileTime，Linux/macOS使用std::chrono
 */
TimestampMs GetCurrentTimestampMs(void);

/**
 * @brief 获取当前系统时间的时间组件
 * @details 直接返回分解后的时间信息（年、月、日等），等价于Timestamp2Component(GetCurrentTimestampMs())
 * @return TimeComponent 当前时间的分解结构
 */
TimeComponent GetCurrentTimeComponent(void);

/**
 * @brief 将毫秒级时间戳转换为本地时间的时间组件
 * @param[in] timestamp 待转换的毫秒级时间戳（Unix纪元基准）
 * @return TimeComponent 转换后的时间组件
 *         失败时返回所有字段为0的结构
 */
TimeComponent LocalTimeComponent(TimestampMs timestamp);

/**
 * @brief 将毫秒级时间戳转换为UTC时间的时间组件
 * @param[in] timestamp 待转换的毫秒级时间戳（Unix纪元基准）
 * @return TimeComponent 转换后的时间组件
 *         失败时返回所有字段为0的结构
 */
TimeComponent UtcTimeComponent(TimestampMs timestamp);

/**
 * @brief 将毫秒级时间戳转换为时间组件
 * @param[in] timestamp 待转换的毫秒级时间戳（Unix纪元基准）
 * @param[in] timeZone: 时区
 * @return TimeComponent 转换后的时间组件
 *         失败时返回所有字段为0的结构
 */
TimeComponent TimeStampMs2Component(TimestampMs timestamp, TimeZone timeZone);

/**
 * @brief 获取月份的完整英文名称
 * @param[in] month 月份（1-12，1表示一月，12表示十二月）
 * @return const char* 完整月份名称（如"January"）
 *         若参数超出范围，返回空字符串视图
 */
const char* GetMonthFullName(uint32_t month);

/**
 * @brief 获取月份的缩写英文名称
 * @param[in] month 月份（1-12）
 * @return const char* 缩写月份名称（如"Jan"）
 *         若参数超出范围，返回空字符串视图
 */
const char* GetMonthAbbrName(uint32_t month);

/**
 * @brief 获取星期的完整英文名称
 * @param[in] weekday 星期（0-6，0表示星期日，6表示星期六）
 * @return const char* 完整星期名称（如"Monday"）
 *         若参数超出范围，返回空字符串视图
 */
const char* GetWeekdayFullName(uint32_t weekday);

/**
 * @brief 获取星期的缩写英文名称
 * @param[in] weekday 星期（0-6）
 * @return const char* 缩写星期名称（如"Mon"）
 *         若参数超出范围，返回空字符串视图
 */
const char* GetWeekdayAbbrName(uint32_t weekday);

size_t FormatTimeStringByComp(CString* string, const TimeComponent* timeComp, const char* format);

ErrorCode DT_GetLastError(void);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_UTILS_DATE_TIME_UTILS_H
