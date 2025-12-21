#include "internal/utils/date_time_internal.h"

#include <threads.h>

#include "common/common_error_code.h"

thread_local ErrorCode g_lastErr = ERR_COMM_SUCCESS;

ErrorCode DtInter_GetLastErr(void)
{
    return g_lastErr;
}

void DtInter_SetLastErr(ErrorCode errcode)
{
    g_lastErr = errcode;
}
