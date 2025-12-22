#ifndef COMMON_CSTL_STRING_H
#define COMMON_CSTL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "common/types/error_code_types.h"

#define CSTL_STRING_MAX_CAPACITY (4096)

typedef enum {
    CSTR_TYPE_STATIC,
    CSTR_TYPE_DYNAMIC
} CStrType;

typedef struct {
    ErrorCode lastErrCode;
    CStrType type;
    uint32_t length;
    uint32_t capacity;
    char *cstr;
} CString;

CString *CString_New(const char *format, ...);

CString *CString_NewBySize(uint32_t size, const char *format, ...);

ErrorCode CString_Append(CString *string, const char *format, ...);

const char *CString_CStr(const CString *string);

uint32_t CString_Length(const CString *string);

uint32_t CString_Capacity(const CString *string);

void CString_Delete(CString *string);

CString *CString_Copy(const CString *srcStr);

ErrorCode CString_Resize(CString *string, uint32_t newCapacity);

ErrorCode CString_GetLastError(const CString *string);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_CSTL_STRING_H
