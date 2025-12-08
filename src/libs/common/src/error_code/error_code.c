#include "common/types/error_code.h"
#include "common/types/common_types.h"

#include <string.h>

static ModuleData g_currModuleDatas[MAX_MODULE_ID + 1] = {0};

ErrorSeverity ErrCode_GetSeverity(ErrorCode err)
{
    return (ErrorSeverity)((err & ERR_SEVERITY_MASK) >> ERR_SEVERITY_SHIFT);
}

ModuleId ErrCode_GetModuleId(ErrorCode err)
{
    return (ModuleId)((err & ERR_MODULE_MASK) >> ERR_MODULE_SHIFT);
}

ErrorType ErrCode_GetErrorType(ErrorCode err)
{
    return (ErrorType)((err & ERR_TYPE_MASK) >> ERR_TYPE_SHIFT);
}

ErrorId ErrCode_GetErrorId(ErrorCode err)
{
    return (uint8_t)((err & ERR_ID_MASK) >> ERR_ID_SHIFT);
}

static const char *get_module_common_err_message(ErrorCode errCode)
{
    switch (errCode) {
        case ERR_COMM_SUCCESS:
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

void ErrCode_RegisterModule(ModuleData data)
{
    g_currModuleDatas[data.moduleId] = data;
}

const char *ErrCode_GetErrMsg(ErrorCode errorCode)
{
    ModuleId moduleId = ErrCode_GetModuleId(errorCode);

    if (moduleId == COMMON_MODULE_ID) {
        return get_module_common_err_message(errorCode);
    }

    if (g_currModuleDatas[moduleId].getErrMsgFunc == NULL) {
        return "Module not register";
    }

    return (*g_currModuleDatas[moduleId].getErrMsgFunc)(errorCode);
}
