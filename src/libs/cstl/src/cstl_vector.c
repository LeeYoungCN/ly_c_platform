#include "cstl/cstl_vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "common/common_macro.h"
#include "common/compiler/macros.h"
#include "common/types/error_code.h"
#include "cstl/cstl_error_code.h"

#if PLATFORM_WINDOWS
#define SAFE_MEMCPY(dst, dstSize, src, srcSize) memcpy_s(dst, dstSize, src, srcSize);
#else
#define SAFE_MEMCPY(dst, dstSize, src, srcSize) memcpy(dst, src, srcSize);
#endif

CStlVector *CStlVector_New(uint32_t elemSize)
{
    return CStlVector_NewByCapacity(elemSize, CSTL_VECTOR_MIN_CAPACITY);
}

CStlVector *CStlVector_NewByCapacity(uint32_t elemSize, uint32_t capacity)
{
    capacity = COMM_MAX(CSTL_VECTOR_MIN_CAPACITY, capacity);
    CStlVector *vector = malloc(sizeof(CStlVector));
    CStlVector_InitByCapacity(vector, elemSize, capacity);
    return vector;
}

void CStlVector_Delete(CStlVector *vector)
{
    if (vector == NULL) {
        return;
    }
    CStlVector_DeInit(vector);
    free(vector);
}

void CStlVector_Init(CStlVector *vector, uint32_t elemSize)
{
    CStlVector_InitByCapacity(vector, elemSize, CSTL_VECTOR_MIN_CAPACITY);
}

void CStlVector_InitByCapacity(CStlVector *vector, uint32_t elemSize, uint32_t capacity)
{
    capacity = COMM_MAX(CSTL_VECTOR_MIN_CAPACITY, capacity);
    vector->length = 0;
    vector->capacity = capacity;
    vector->elemSize = elemSize;
    vector->elements = malloc(elemSize * vector->capacity);
    memset(vector->elements, 0, elemSize * vector->capacity);
}

void CStlVector_DeInit(CStlVector *vector)
{
    if (vector == NULL || vector->elements == NULL) {
        return;
    }
    free(vector->elements);
    vector->elements = NULL;
}

ErrorCode CStlVector_GetElem(CStlVector *vector, uint32_t idx, void *elem)
{
    if (vector == NULL || vector->elements == NULL || elem == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    if (idx >= vector->length) {
        vector->lastErrCode = ERR_CSTL_PARAM_IDX_INVALID;
        return vector->lastErrCode;
    }
    vector->lastErrCode = ERR_COMM_SUCCESS;
    char *ptr = vector->elements + idx * vector->elemSize;
    SAFE_MEMCPY(elem, vector->elemSize, ptr, vector->elemSize);
    return vector->lastErrCode;
}

ErrorCode CStlVector_SetElem(CStlVector *vector, uint32_t idx, void *newElem, void *oldElem)
{
    if (vector == NULL || vector->elements == NULL || newElem == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    if (idx >= vector->length) {
        vector->lastErrCode = ERR_CSTL_PARAM_IDX_INVALID;
        return ERR_CSTL_PARAM_IDX_INVALID;
    }
    vector->lastErrCode = ERR_COMM_SUCCESS;

    char *ptr = vector->elements + idx * vector->elemSize;
    if (oldElem != NULL) {
        SAFE_MEMCPY(oldElem, vector->elemSize, ptr, vector->elemSize);
    }

    SAFE_MEMCPY(ptr, vector->elemSize, newElem, vector->elemSize);

    return vector->lastErrCode;
}

uint32_t CStlVector_Length(const CStlVector *vector)
{
    return vector == NULL || vector->elements == NULL ? 0 : vector->length;
}

uint32_t CStlVector_Capacity(const CStlVector *vector)
{
    return vector == NULL || vector->elements == NULL ? 0 : vector->capacity;
}

ErrorCode CStlVector_Resize(CStlVector *vector, uint32_t newCapacity)
{
    if (vector == NULL || vector->elements == NULL) {
        return ERR_COMM_PARAM_NULL;
    }

    vector->lastErrCode = ERR_COMM_SUCCESS;

    if (newCapacity > CSTL_VECTOR_MAX_CAPACITY) {
        vector->lastErrCode = ERR_CSTL_EXCEED_MAX_CAPACITY;
        return vector->lastErrCode;
    }

    if (vector->length > newCapacity || newCapacity < CSTL_VECTOR_MIN_CAPACITY) {
        vector->lastErrCode = ERR_CSTL_PARAM_CAPACITY_INVALID;
        return vector->lastErrCode;
    }

    char *newDatas = realloc(vector->elements, vector->elemSize * newCapacity);

    if (newDatas == NULL) {
        vector->lastErrCode = ERR_COMM_MALLOC_FAILED;
    } else {
        vector->elements = newDatas;
        vector->lastErrCode = ERR_COMM_SUCCESS;
        vector->capacity = newCapacity;
    }
    return vector->lastErrCode;
}

ErrorCode CStlVector_Push(CStlVector *vector, void *elem)
{
    if (vector == NULL || vector->elements == NULL) {
        return ERR_COMM_PARAM_NULL;
    }

    if (vector->length >= CSTL_VECTOR_MAX_CAPACITY) {
        vector->lastErrCode = ERR_CSTL_EXCEED_MAX_CAPACITY;
        return vector->lastErrCode;
    }

    if (vector->length >= vector->capacity) {
        uint32_t newCapacity = COMM_MIN(2 * vector->length, CSTL_VECTOR_MAX_CAPACITY);
        if (CStlVector_Resize(vector, newCapacity) != ERR_COMM_SUCCESS) {
            return vector->lastErrCode;
        }
    }

    SAFE_MEMCPY(vector->elements + (vector->length) * vector->elemSize, vector->elemSize, elem, vector->elemSize);

    ++vector->length;
    vector->lastErrCode = ERR_COMM_SUCCESS;
    return vector->lastErrCode;
}

ErrorCode CStlVector_Pop(CStlVector *vector, void *elem)
{
    if (vector == NULL || vector->elements == NULL) {
        return ERR_COMM_PARAM_NULL;
    }

    if (vector->length == 0) {
        memset(elem, 0, vector->elemSize);
        vector->lastErrCode = ERR_CSTL_PARAM_CONTAINER_EMPTY;
        return vector->lastErrCode;
    }

    vector->lastErrCode = ERR_COMM_SUCCESS;
    void *ptr = vector->elements + (vector->length - 1) * vector->elemSize;
    vector->length--;
    if (elem != NULL) {
        SAFE_MEMCPY(elem, vector->elemSize, ptr, vector->elemSize);
    }
    if (vector->capacity > CSTL_VECTOR_MIN_CAPACITY && vector->length <= vector->capacity / 4) {
        CStlVector_Resize(vector, COMM_MAX(CSTL_VECTOR_MIN_CAPACITY, vector->capacity / 2));
    }
    return vector->lastErrCode;
}

ErrorCode CStlVector_GetLastError(const CStlVector *vector)
{
    return vector == NULL || vector->elements == NULL ? ERR_COMM_PARAM_NULL : vector->lastErrCode;
}
