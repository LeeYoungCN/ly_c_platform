#include "common/cstl/cstl_char_buffer.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "common/common_error_code.h"
#include "common/types/error_code_types.h"

CStlCharBuff CStlCharBuff_Get(char *buffer, uint32_t capacity)
{
    if (buffer != NULL) {
        memset(buffer, 0, capacity);
    }
    CStlCharBuff charBuff = {.lastErrCode = (buffer == NULL ? ERR_COMM_PARAM_NULL : ERR_COMM_SUCCESS),
                             .length = 0,
                             .capacity = (buffer == NULL ? capacity : 0),
                             .buffer = buffer};
    return charBuff;
}

ErrorCode CStlCharBuff_Init(CStlCharBuff *charBuffer)
{
    if (charBuffer == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    memset(charBuffer->buffer, 0, charBuffer->capacity);
    charBuffer->length = 0;
    charBuffer->lastErrCode = ERR_COMM_SUCCESS;
    return charBuffer->lastErrCode;
}

ErrorCode CStlCharBuff_Append(CStlCharBuff *buffer, const char *format, ...)
{
    if (buffer == NULL || buffer->buffer == NULL) {
        return ERR_COMM_PARAM_NULL;
    }
    buffer->lastErrCode = ERR_COMM_SUCCESS;
    va_list args;
    va_start(args, format);

    uint32_t newLength = 0;
    if (format != NULL) {
        newLength +=
            (uint32_t)vsnprintf(buffer->buffer + buffer->length, buffer->capacity - buffer->length, format, args);
    }
    va_end(args);

    if (newLength >= buffer->capacity) {
        buffer->lastErrCode = ERR_COMM_EXCEED_MAX_CAPACITY;
    } else {
        buffer->length = newLength;
    }
    buffer->buffer[buffer->length] = '\0';
    return buffer->lastErrCode;
}

const char *CStlCharBuff_CStr(const CStlCharBuff *buffer)
{
    return (buffer != NULL ? buffer->buffer : NULL);
}

uint32_t CStlCharBuff_Length(const CStlCharBuff *buffer)
{
    return (buffer != NULL ? buffer->length : 0);
}

uint32_t CStlCharBuff_Capacity(const CStlCharBuff *buffer)
{
    return (buffer != NULL ? buffer->capacity : 0);
}

ErrorCode CStlCharBuff_GetLastError(const CStlCharBuff *buffer)
{
    return (buffer != NULL ? buffer->lastErrCode : ERR_COMM_PARAM_NULL);
}
