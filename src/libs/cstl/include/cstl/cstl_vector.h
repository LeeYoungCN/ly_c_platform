#ifndef CSTL_VECTOR_H
#define CSTL_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "common/types/error_code.h"

typedef struct CStlVector CStlVector;

#define CSTL_VECTOR_MAX_CAPACITY (4096)

CStlVector *CStlVector_New(void);

CStlVector *CStlVector_NewBySize(uint32_t size);

ErrorCode CStlVector_Push(CStlVector *vector, void *data);

uint32_t CStlVector_Length(const CStlVector *vector);

uint32_t CStlVector_Capacity(const CStlVector *vector);

void CStlVector_Delete(CStlVector *vector);

CStlVector *CStlVector_Copy(const CStlVector *srcStr);

ErrorCode CStlVector_Resize(CStlVector *vector, uint32_t newCapacity);

ErrorCode CStlVector_GetLastError(const CStlVector *vector);

#ifdef __cplusplus
}
#endif

#endif  // CSTL_VECTOR_H
