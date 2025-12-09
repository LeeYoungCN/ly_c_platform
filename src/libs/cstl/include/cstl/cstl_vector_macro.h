#ifndef CSTL_VECTOR_MACRO_H
#define CSTL_VECTOR_MACRO_H

#include <stdlib.h>
#include "cstl/cstl_vector.h"

#define CSTL_VECTOR_DECLARE(T)  \
    typedef struct  {           \
        CStlVectorBase base;    \
        T  *datas;              \
    } CStlVector##T;            \
                                \
    CStlVector##T *CStlVector##T##_New(void);   \
    CStlVector##T *CStlVector##T##_NewByCapacity(uint32_t capacity); \
    void CStlVector##T##_Delete(CStlVector##T *vector); \
    uint32_t CStlVector##T##_Length(const CStlVector##T *vector); \
    uint32_t CStlVector##T##_Capacity(const CStlVector##T *vector); \
    ErrorCode CStlVector##T##_Push(CStlVector##T *vector, T data);  \
    T CStlVector##T##_Pop(CStlVector##T *vector);   \
    CStlVector##T *CStlVector##T##_Copy(const CStlVector##T *srcStr);  \
    ErrorCode CStlVector##T##_Resize(CStlVector##T *vector, uint32_t newCapacity);  \
    ErrorCode CStlVector##T##_GetLastError(const CStlVector##T *vector);

#define CSTL_VECTOR_DEFINE(T)                                  \
    CStlVector##T *CStlVector##T##_New(void)                   \
    {                                                          \
        CStlVector##T *vector = malloc(sizeof(CStlVector##T)); \
        CStlVectorBase_Init(&vector->base, sizeof(T));         \
        vector->datas = (T *)vector->base.datas;               \
        return vector;                                         \
    }   \
    \
    CStlVector##T *CStlVector##T##_NewByCapacity(uint32_t capacity) \
    {                                                               \
        CStlVector##T *vector = malloc(sizeof(CStlVector##T)); \
        CStlVectorBase_InitByCapacity(&vector->base, sizeof(T), capacity);         \
        vector->datas = (T *)vector->base.datas;               \
        return vector;                                         \
    }


#endif // CSTL_VECTOR_MACRO_H
