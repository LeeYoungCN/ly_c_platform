#ifndef COMMON_UTILS_DATE_TIME_UTILS_H
#define COMMON_UTILS_DATE_TIME_UTILS_H

#include "common/types/error_code_types.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/date_time_types.h"

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

ErrorCode DT_GetLastError(void);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_UTILS_DATE_TIME_UTILS_H
