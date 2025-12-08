#include "common/types/error_code.h"

#include <string.h>

static ModuleData g_currModuleDatas[MAX_MODULE_ID + 1] = {0};

ErrorSeverity ErrCode_GetSeverity(ErrorCode err)
{
    return (ErrorSeverity)((err & ERR_SEVERITY_MASK) >> ERR_SEVERITY_SHIFT);
}

ModuleID ErrCode_GetModuleId(ErrorCode err)
{
    return (ModuleID)((err & ERR_MODULE_MASK) >> ERR_MODULE_SHIFT);
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
            return "array out of bound.";
        default:
            return "Unkown";
    };
}

void ErrCode_RegisterModule(ModuleData data)
{
    g_currModuleDatas[data.moduleId] = data;
}

const char *ErrCode_GetErrorMessage(ErrorCode errorCode)
{
    ModuleID moduleId = ErrCode_GetModuleId(errorCode);

    if (moduleId == COMMON_MODULE_ID) {
        return get_module_common_err_message(errorCode);
    }

    if (g_currModuleDatas[moduleId].getMessageFunc == NULL) {
        return "Module not register";
    }

    return (*g_currModuleDatas[moduleId].getMessageFunc)(errorCode);
}
