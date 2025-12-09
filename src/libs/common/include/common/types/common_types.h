#ifndef COMMON_COMMON_TYPES_H
#define COMMON_COMMON_TYPES_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

typedef enum {
    ERR_SEV_SUCCESS = 0,  // 成功（无错误）
    ERR_SEV_INFO = 1,     // 提示（不影响流程）
    ERR_SEV_WARN = 2,     // 警告（可能有风险）
    ERR_SEV_ERROR = 3,    // 错误（功能失败，可恢复）
    ERR_SEV_FATAL = 4     // 严重错误（系统崩溃，不可恢复）
} ErrorSeverity;

typedef uint16_t ModuleId;
typedef uint16_t ErrorType;
typedef uint16_t ErrorId;

#define COMMON_MODULE_ID (0)
#define MAX_MODULE_ID (0xFFFF)

#ifdef __cplusplus
}
#endif

#endif // COMMON_COMMON_TYPES_H
