#ifndef CSTL_VECTOR_H
#define CSTL_VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif
#include "common/types/error_code_types.h"

static const uint32_t CSTL_VECTOR_MIN_CAPACITY = 4;
static const uint32_t CSTL_VECTOR_MAX_CAPACITY = 4096;

typedef struct {
    ErrorCode lastErrCode;
    uint32_t length;
    uint32_t capacity;
    uint32_t elemSize;
    char *elements;
} CStlVector;

CStlVector *CStlVector_New(uint32_t elemSize);

CStlVector *CStlVector_NewByCapacity(uint32_t elemSize, uint32_t capacity);

void CStlVector_Delete(CStlVector *vector);

void CStlVector_Init(CStlVector *vector, uint32_t elemSize);

void CStlVector_InitByCapacity(CStlVector *vector, uint32_t elemSize, uint32_t capacity);

void CStlVector_DeInit(CStlVector *vector);

ErrorCode CStlVector_GetElem(CStlVector *vector, uint32_t idx, void *elem);

ErrorCode CStlVector_SetElem(CStlVector *vector, uint32_t idx, void *newElem, void *oldElem);

uint32_t CStlVector_Length(const CStlVector *vector);

uint32_t CStlVector_Capacity(const CStlVector *vector);

ErrorCode CStlVector_Resize(CStlVector *vector, uint32_t newCapacity);

ErrorCode CStlVector_Push(CStlVector *vector, void *elem);

ErrorCode CStlVector_Pop(CStlVector *vector,  void *elem);

CStlVector *CStlVector_Copy(const CStlVector *srcStr);

ErrorCode CStlVector_GetLastError(const CStlVector *vector);

#ifdef __cplusplus
}
#endif

#endif  // CSTL_VECTOR_H
