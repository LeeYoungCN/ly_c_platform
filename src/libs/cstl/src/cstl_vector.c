#include "cstl/cstl_vector.h"
#include <stdint.h>
#include <stdlib.h>

#include "common/common_macro.h"
#include "common/types/error_code.h"
#include "cstl/cstl_error_code.h"

#define CSTL_VECTOR_DEFAULT_SIZE (32)
#define CSTL_VECTOR_MAX_CAPACITY (4096)

struct CStlVector {
    ErrorCode lastErrCode;
    uint32_t length;
    uint32_t capacity;
    void **datas;
};

ErrorCode CStlVector_Resize(CStlVector *vector, uint32_t newCapacity)
{
    if (vector == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    vector->lastErrCode = ERR_COMM_SUCCESS;
    if (newCapacity > CSTL_VECTOR_MAX_CAPACITY) {
        vector->lastErrCode = ERR_CSTL_EXCEED_MAX_CAPACITY;
        return vector->lastErrCode;
    }
    if (vector->length > newCapacity || newCapacity == 0) {
        vector->lastErrCode = ERR_CSTL_CAPACITY_INVALID;
        return vector->lastErrCode;
    }
    void **newDatas = realloc(vector->datas, sizeof(void *) * newCapacity);
    if (newDatas == NULL) {
        vector->lastErrCode = ERR_COMM_MALLOC_FAILED;
    } else {
        vector->datas = newDatas;
        vector->lastErrCode = ERR_COMM_SUCCESS;
    }
    return vector->lastErrCode;
}

CStlVector *CStlVector_NewBySize(uint32_t size)
{
    CStlVector *vector = malloc(sizeof(CStlVector));
    vector->length = 0;
    vector->capacity = size;
    vector->datas = malloc(sizeof(void *) * vector->capacity);
    return vector;
}

CStlVector *CStlVector_New(void)
{
    return CStlVector_NewBySize(CSTL_VECTOR_DEFAULT_SIZE);
}

ErrorCode CStlVector_Push(CStlVector *vector, void *data)
{
    if (vector == NULL) {
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

    vector->datas[vector->length++] = data;
    vector->lastErrCode = ERR_COMM_SUCCESS;
    return vector->lastErrCode;
}

void *CStlVector_Pop(CStlVector *vector)
{
    if (vector == NULL) {
        return vector;
    }
    if (vector->length == 0) {
        return NULL;
    }
    void *data = vector->datas[vector->length--];

    if (vector->capacity > CSTL_VECTOR_DEFAULT_SIZE && vector->length <= vector->capacity / 4) {
        CStlVector_Resize(vector, COMM_MAX(CSTL_VECTOR_DEFAULT_SIZE, vector->capacity / 2));

    }
    return data;
}
