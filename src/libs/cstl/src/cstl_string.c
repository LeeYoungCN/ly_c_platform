#include "cstl/cstl_string.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/common_error_code.h"
#include "common/compiler/macros.h"
#include "common/macros/math_macro.h"
#include "common/types/error_code_types.h"
#include "cstl/cstl_error_code.h"

#define CSTL_STRING_DEFAULT_SIZE (128)
#define CSTL_STRING_INCREASE_SIZE (128)

struct CStlString {
    ErrorCode lastErrCode;
    uint32_t length;
    uint32_t capacity;
    char *cstr;
};

static void StlString_AppendVa(CStlString *string, const char *format, va_list args)
{
    string->lastErrCode = ERR_COMM_SUCCESS;
    va_list argsCpy;
    va_copy(argsCpy, args);

    int fmtLen = 0;
    if (format != NULL) {
        fmtLen = vsnprintf(string->cstr + string->length, string->capacity - string->length, format, args);
    }

    uint32_t newLength = string->length + (uint32_t)fmtLen;
    if (newLength < string->capacity) {
        string->length = newLength;
        string->lastErrCode = ERR_COMM_SUCCESS;
        goto FINISH;
    }

    if (newLength >= CSTL_STRING_MAX_CAPACITY) {
        string->lastErrCode = ERR_CSTL_EXCEED_MAX_CAPACITY;
        goto FINISH;
    }

    string->cstr[string->length] = '\0';
    uint32_t newCapacity = COMM_MIN(newLength + CSTL_STRING_INCREASE_SIZE, CSTL_STRING_MAX_CAPACITY);
    if (CStlString_Resize(string, newCapacity) == ERR_COMM_SUCCESS) {
        if (format != NULL) {
            vsnprintf(string->cstr + string->length, string->capacity - string->length, format, argsCpy);
        }
        string->length = newLength;
        string->lastErrCode = ERR_COMM_SUCCESS;
    }

FINISH:
    va_end(argsCpy);
    string->cstr[string->length] = '\0';
}

static CStlString *CStlString_NewBySizeVa(uint32_t size, const char *format, va_list args)
{
    CStlString *string = malloc(sizeof(CStlString));
    if (string == NULL) {
        return NULL;
    }
    string->length = 0;
    string->capacity = size;
    string->cstr = malloc(string->capacity);

    StlString_AppendVa(string, format, args);

    return string;
}

CStlString *CStlString_New(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    CStlString *string = CStlString_NewBySizeVa(CSTL_STRING_DEFAULT_SIZE, format, args);
    va_end(args);
    return string;
}

CStlString *CStlString_NewBySize(uint32_t size, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    size = (size == 0 ? CSTL_STRING_DEFAULT_SIZE : size);
    CStlString *string = CStlString_NewBySizeVa(size, format, args);
    va_end(args);
    return string;
}

ErrorCode CStlString_Append(CStlString *string, const char *format, ...)
{
    if (string == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    va_list args;
    va_start(args, format);
    StlString_AppendVa(string, format, args);
    va_end(args);
    return string->lastErrCode;
}

const char *CStlString_CStr(const CStlString *string)
{
    if (string == NULL) {
        return NULL;
    }
    return string->cstr;
}

uint32_t CStlString_Length(const CStlString *string)
{
    if (string == NULL) {
        return 0;
    }
    return string->length;
}

uint32_t CStlString_Capacity(const CStlString *string)
{
    if (string == NULL) {
        return 0;
    }
    return string->capacity;
}

void CStlString_Delete(CStlString *string)
{
    if (string == NULL) {
        return;
    }
    if (string->cstr != NULL) {
        free(string->cstr);
        string->cstr = NULL;
    }
    free(string);
}

CStlString *CStlString_Copy(const CStlString *srcStr)
{
    if (srcStr == NULL) {
        return NULL;
    }
    CStlString *string = malloc(sizeof(CStlString));
    if (string == NULL) {
        return NULL;
    }
    string->length = srcStr->length;
    string->capacity = srcStr->capacity;
    string->cstr = malloc(string->capacity);
#if PLATFORM_WINDOWS
    strncpy_s(string->cstr, string->capacity, srcStr->cstr, srcStr->length + 1);
#else
    strncpy(string->cstr, srcStr->cstr, srcStr->length + 1);
#endif
    string->lastErrCode = ERR_COMM_SUCCESS;
    return string;
}

ErrorCode CStlString_Resize(CStlString *string, uint32_t newCapacity)
{
    if (string == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    string->lastErrCode = ERR_COMM_SUCCESS;
    if (newCapacity > CSTL_STRING_MAX_CAPACITY || newCapacity == 0) {
        string->lastErrCode = ERR_CSTL_PARAM_CAPACITY_INVALID;
        return string->lastErrCode;
    }
    if (string->length > newCapacity) {
        string->lastErrCode = ERR_CSTL_PARAM_CAPACITY_INVALID;
        return string->lastErrCode;
    }

    char *newCstr = realloc(string->cstr, newCapacity);
    if (newCstr == NULL) {
        string->lastErrCode = ERR_COMM_MALLOC_FAILED;
    } else {
        string->cstr = newCstr;
        string->capacity = newCapacity;
        string->lastErrCode = ERR_COMM_SUCCESS;
    }

    return string->lastErrCode;
}

ErrorCode CStlString_GetLastError(const CStlString *string)
{
    if (string == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    return string->lastErrCode;
}
