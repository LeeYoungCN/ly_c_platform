#ifndef CSTL_STRING_H
#define CSTL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "common/types/error_code.h"

typedef struct CStlString CStlString;

CStlString *CStlString_New(const char* format, ...);

CStlString *CStlString_NewBySize(uint32_t size, const char* format, ...);

ErrorCode CStlString_Append(CStlString *string, const char* format, ...);

const char* CStlString_CStr(const CStlString *string);

uint32_t CStlString_Length(const CStlString *string);

uint32_t CStlString_Capacity(const CStlString *string);

void CStlString_Delete(CStlString* string);

CStlString *CStlString_Copy(const CStlString *srcStr);

ErrorCode CStlString_Resize(CStlString *string, uint32_t newCapacity);

#ifdef __cplusplus
}
#endif

#endif // CSTL_STRING_H
