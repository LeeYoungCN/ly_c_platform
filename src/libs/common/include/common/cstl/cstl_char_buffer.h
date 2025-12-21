#ifndef COMMON_CSTL_CHAR_BUFFER_H
#define COMMON_CSTL_CHAR_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "common/types/error_code_types.h"

typedef struct {
    ErrorCode lastErrCode;
    uint32_t length;
    uint32_t capacity;
    char *buffer;
} CStlCharBuff;

CStlCharBuff CStlCharBuff_Get(char *buffer, uint32_t capacity);

ErrorCode CStlCharBuff_Init(CStlCharBuff *charBuffer);

ErrorCode CStlCharBuff_Append(CStlCharBuff *buffer, const char *format, ...);

const char *CStlCharBuff_CStr(const CStlCharBuff *buffer);

uint32_t CStlCharBuff_Length(const CStlCharBuff *buffer);

uint32_t CStlCharBuff_Capacity(const CStlCharBuff *buffer);

ErrorCode CStlCharBuff_GetLastError(const CStlCharBuff *buffer);

#ifdef __cplusplus
}
#endif

#endif  // COMMON_CSTL_CHAR_BUFFER_H
