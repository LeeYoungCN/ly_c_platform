#ifndef COMMON_INTERNAL_UTILS_DATE_TIME_INTERNAL_H
#define COMMON_INTERNAL_UTILS_DATE_TIME_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common/types/error_code_types.h"

ErrorCode DtInter_GetLastErr(void);
void      DtInter_SetLastErr(ErrorCode errcode);

#ifdef __cplusplus
}
#endif

#endif // COMMON_INTERNAL_UTILS_DATE_TIME_INTERNAL_H
