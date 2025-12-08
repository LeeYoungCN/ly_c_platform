#ifndef COMMON_TYPES_ERROR_CODE_H
#define COMMON_TYPES_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

typedef uint32_t ErrorCode;

#define ERR_SEVERITY_MASK 0xFF000000  // 错误级别掩码（第31~24位）
#define ERR_MODULE_MASK 0x00FF0000    // 模块ID掩码（第23~16位）
#define ERR_TYPE_MASK 0x0000FF00      // 错误类型掩码（第15~8位）
#define ERR_ID_MASK 0x000000FF        // 具体错误码掩码（第7~0位）

#define ERR_SEVERITY_SHIFT 24  // 错误级别移位量
#define ERR_MODULE_SHIFT 16    // 模块ID移位量
#define ERR_TYPE_SHIFT 8       // 错误类型移位量
#define ERR_ID_SHIFT 0         // 具体错误码移位量

// ======================== 错误码构造宏 ========================
#define MAKE_ERROR(severity, module, type, code)                                                                    \
    ((ErrorCode)(((severity) << ERR_SEVERITY_SHIFT) | ((module) << ERR_MODULE_SHIFT) | ((type) << ERR_TYPE_SHIFT) | \
                 ((code) << ERR_ID_SHIFT)))

// ======================== 错误级别枚举 ========================
typedef enum {
    ERR_SEV_SUCCESS = 0,  // 成功（无错误）
    ERR_SEV_INFO = 1,     // 提示（不影响流程）
    ERR_SEV_WARN = 2,     // 警告（可能有风险）
    ERR_SEV_ERROR = 3,    // 错误（功能失败，可恢复）
    ERR_SEV_FATAL = 4     // 严重错误（系统崩溃，不可恢复）
} ErrorSeverity;

typedef uint8_t ModuleID;
typedef uint8_t ErrorType;
typedef uint16_t ErrorId;

#define MAX_MODULE_ID 0xFF

typedef const char *(*GetErrCodeMessageFunc)(ErrorCode);

typedef struct {
    ModuleID moduleId;
    const char *moduleName;
    GetErrCodeMessageFunc getMessageFunc;
} ModuleData;

ErrorSeverity ErrCode_GetSeverity(ErrorCode err);
ModuleID ErrCode_GetModuleId(ErrorCode err);
ErrorType ErrCode_GetErrorType(ErrorCode err);
ErrorId ErrCode_GetErrorId(ErrorCode err);
const char *ErrCode_GetErrorMessage(ErrorCode err);

void ErrCode_RegisterModule(ModuleData data);

#define COMMON_MODULE_ID 0

#define COMM_ERR_TYPE_SUCCESS 0  // 成功
#define COMM_ERR_TYPE_MEM 1      // 内存操作
#define COMM_ERR_TYPE_DATA 2     // 数据本身的存储或结构问题（如数组越界、数据格式错误）
#define COMM_ERR_TYPE_PARAM 3    // 入参校验

// 成功
#define ERR_COMM_SUCCESS MAKE_ERROR(ERR_SEV_SUCCESS, 0, COMM_ERR_TYPE_SUCCESS, 0)  // 成功
// 内存操作
#define ERR_COMM_MALLOC_FAILED MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_MEM, 1)  // 内存分配失败
// 数据本身的存储或结构问题（如数组越界、数据格式错误）
#define ERR_COMM_ARRAY_OOB MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_DATA, 1)     // 数组越界
#define ERR_COMM_ENUM_INVALID MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_DATA, 2)  // 枚举值异常
// 入参校验
#define ERR_COMM_ARRAY_IDX_OOB MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_PARAM, 1)  // 入参数组越界
#define ERR_COMM_PARAM_NULL MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_PARAM, 2)     // 空指针
#define ERR_COMM_PARAM_INVALID MAKE_ERROR(ERR_SEV_ERROR, COMMON_MODULE_ID, COMM_ERR_TYPE_PARAM, 3)  // 入参不合法

#ifdef __cplusplus
}
#endif

#endif  // COMMON_TYPES_ERROR_CODE_H
