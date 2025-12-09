#ifndef COMMON_TYPES_ERROR_CODE_H
#define COMMON_TYPES_ERROR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#include "common/types/common_types.h"

typedef uint64_t ErrorCode;

// 错误级别：高16位（第63~48位），掩码0xFFFF000000000000
#define ERR_SEVERITY_MASK   0xFFFF000000000000ULL
// 模块ID：中16位（第47~32位），掩码0x0000FFFF00000000
#define ERR_MODULE_MASK     0x0000FFFF00000000ULL
// 错误类型：次中16位（第31~16位），掩码0x00000000FFFF0000
#define ERR_TYPE_MASK       0x00000000FFFF0000ULL
// 具体错误码：低16位（第15~0位），掩码0x000000000000FFFF
#define ERR_ID_MASK         0x000000000000FFFFULL

// ======================== 移位量（与掩码对应，无溢出）

#define ERR_SEVERITY_SHIFT 48  // 错误级别左移48位
#define ERR_MODULE_SHIFT 32    // 模块ID左移32位
#define ERR_TYPE_SHIFT 16      // 错误类型左移16位
#define ERR_ID_SHIFT 0         // 具体错误码无需移位

// ======================== 错误码构造宏 ========================
#define MAKE_ERROR(severity, module, type, code)                                                           \
    ((ErrorCode)(((uint64_t)(severity) << ERR_SEVERITY_SHIFT) | ((uint64_t)(module) << ERR_MODULE_SHIFT) | \
                 ((uint64_t)(type) << ERR_TYPE_SHIFT) | ((uint64_t)(code) << ERR_ID_SHIFT)))

// ======================== 错误级别 ========================
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

typedef const char *(*GetErrMsgFunc)(ErrorCode);

typedef struct {
    ModuleId moduleId;
    const char *moduleName;
    GetErrMsgFunc getErrMsgFunc;
} ModuleData;

ErrorSeverity ErrCode_GetSeverity(ErrorCode err);
ModuleId ErrCode_GetModuleId(ErrorCode err);
ErrorType ErrCode_GetErrorType(ErrorCode err);
ErrorId ErrCode_GetErrorId(ErrorCode err);
const char *ErrCode_GetErrMsg(ErrorCode err);
void ErrCode_RegisterModule(ModuleData data);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_TYPES_ERROR_CODE_H
