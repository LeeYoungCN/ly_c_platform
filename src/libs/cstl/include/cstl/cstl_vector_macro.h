#ifndef CSTL_VECTOR_MACRO_H
#define CSTL_VECTOR_MACRO_H

#include <stdlib.h>
#include "cstl/cstl_vector.h"

#define CSTL_VECTOR_DECLARE(T)  \
    typedef struct  {           \
        CStlVectorBase base;    \
        T  *datas;              \
    } CStlVector_##T;            \
                                \
    CStlVector_##T *CStlVector_##T##_New(void);   \
    CStlVector_##T *CStlVector_##T##_NewByCapacity(uint32_t capacity); \
    void CStlVector_##T##_Delete(CStlVector_##T *vector); \
    uint32_t CStlVector_##T##_Length(const CStlVector_##T *vector); \
    uint32_t CStlVector_##T##_Capacity(const CStlVector_##T *vector); \
    ErrorCode CStlVector_##T##_Push(CStlVector_##T *vector, T data);  \
    T CStlVector_##T##_Pop(CStlVector_##T *vector);   \
    CStlVector_##T *CStlVector_##T##_Copy(const CStlVector_##T *srcStr);  \
    ErrorCode CStlVector_##T##_Resize(CStlVector_##T *vector, uint32_t newCapacity);  \
    ErrorCode CStlVector_##T##_GetLastError(const CStlVector_##T *vector);

#define CSTL_VECTOR_DEFINE(T)                                  \
    CStlVector_##T *CStlVector_##T##_New(void)                   \
    {                                                          \
        CStlVector_##T *vector = malloc(sizeof(CStlVector_##T)); \
        CStlVectorBase_Init(&vector->base, sizeof(T));         \
        vector->datas = (T *)vector->base.datas;               \
        return vector;                                         \
    }   \
    \
    CStlVector_##T *CStlVector_##T##_NewByCapacity(uint32_t capacity) \
    {                                                               \
        CStlVector_##T *vector = malloc(sizeof(CStlVector_##T)); \
        CStlVectorBase_InitByCapacity(&vector->base, sizeof(T), capacity);         \
        vector->datas = (T *)vector->base.datas;               \
        return vector;                                         \
    }


#endif // CSTL_VECTOR_MACRO_H
