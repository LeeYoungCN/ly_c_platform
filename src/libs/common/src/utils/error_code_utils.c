#include "common/utils/error_code_utils.h"

#include <stddef.h>

#include "common/common_error_code.h"
#include "common/types/error_code_types.h"

static ErrModuleData g_currModuleDatas[MAX_MODULE_ID + 1] = {0};

ErrorSeverity ErrCode_GetSeverity(ErrorCode err)
{
    return (ErrorSeverity)((err & ERR_SEVERITY_MASK) >> ERR_SEVERITY_SHIFT);
}

ErrModuleId ErrCode_GetModuleId(ErrorCode err)
{
    return (ErrModuleId)((err & ERR_MODULE_MASK) >> ERR_MODULE_SHIFT);
}

ErrorType ErrCode_GetErrorType(ErrorCode err)
{
    return (ErrorType)((err & ERR_TYPE_MASK) >> ERR_TYPE_SHIFT);
}

ErrorId ErrCode_GetErrorId(ErrorCode err)
{
    return (uint8_t)((err & ERR_ID_MASK) >> ERR_ID_SHIFT);
}

void ErrCode_RegisterModule(ErrModuleData data)
{
    g_currModuleDatas[data.moduleId] = data;
}

const char *ErrCode_GetErrMsg(ErrorCode errorCode)
{
    ErrModuleId moduleId = ErrCode_GetModuleId(errorCode);

    if (moduleId == COMMON_MODULE_ID) {
        return ErrCode_GetCommErrMsg(errorCode);
    }

    if (g_currModuleDatas[moduleId].getErrMsgFunc == NULL) {
        return "Module not register";
    }

    return (*g_currModuleDatas[moduleId].getErrMsgFunc)(errorCode);
}
