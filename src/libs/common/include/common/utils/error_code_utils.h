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

typedef const char *(*ErrCode_GetErrMsgFunc)(ErrorCode);

typedef struct {
    ErrModuleId moduleId;
    const char *moduleName;
    ErrCode_GetErrMsgFunc getErrMsgFunc;
} ErrModuleData;

void ErrCode_RegisterModule(ErrModuleData data);
const char *ErrCode_GetErrMsg(ErrorCode err);

#ifdef __cplusplus
}
#endif

#endif // COMMON_UTILS_ERROR_CODE_UTILS_H
