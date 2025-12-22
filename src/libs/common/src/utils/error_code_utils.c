#include "common/utils/error_code_utils.h"

#include <stddef.h>
#include <threads.h>

#include "common/common_error_code.h"
#include "common/types/error_code_types.h"


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

static volatile thread_local ErrorCode g_lastErr = ERR_COMM_SUCCESS;

void SetLastError(ErrorCode errcode)
{
    g_lastErr = errcode;
}

ErrorCode GetLastError(void)
{
    return g_lastErr;
}

const char *GetLastErrStr(void)
{
    return ErrCode_GetCommErrMsg(g_lastErr);
}
