#ifndef COMMON_UTILS_ERROR_CODE_UTILS_H
#define COMMON_UTILS_ERROR_CODE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/error_code_types.h"

ErrorSeverity ErrCode_GetSeverity(ErrorCode err);
ErrModuleId ErrCode_GetModuleId(ErrorCode err);
ErrorType ErrCode_GetErrorType(ErrorCode err);
ErrorId ErrCode_GetErrorId(ErrorCode err);

void SetLastError(ErrorCode errcode);
ErrorCode GetLastError(void);
const char *GetLastErrStr(void);

#ifdef __cplusplus
}
#endif

#endif // COMMON_UTILS_ERROR_CODE_UTILS_H
