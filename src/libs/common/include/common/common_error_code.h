#ifndef COMMON_CONSTANTS_ERROR_CODE_CONSTANTS_H
#define COMMON_CONSTANTS_ERROR_CODE_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/error_code_types.h"

#define COMMON_MODULE_ID 0

#define COMM_ERR_TYPE_MEM 1    // 内存操作
#define COMM_ERR_TYPE_DATA 2   // 数据本身的存储或结构问题（如数组越界、数据格式错误）
#define COMM_ERR_TYPE_PARAM 3  // 入参校验

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

inline const char *ErrCode_GetCommErrMsg(ErrorCode errCode)
{
    switch (errCode) {
        case 0:
            return "success";
        case ERR_COMM_MALLOC_FAILED:
            return "malloc failed";
        case ERR_COMM_ARRAY_OOB:
            return "array out of bound";
        case ERR_COMM_ENUM_INVALID:
            return "Enum invalid";
        case ERR_COMM_ARRAY_IDX_OOB:
            return "Input index array out of bound";
        case ERR_COMM_PARAM_NULL:
            return "Input param NULL";
        case ERR_COMM_PARAM_INVALID:
            return "Input param invalid";
        default:
            return "Unkown";
    };
}

#ifdef __cplusplus
}
#endif

#endif  // COMMON_CONSTANTS_ERROR_CODE_CONSTANTS_H
