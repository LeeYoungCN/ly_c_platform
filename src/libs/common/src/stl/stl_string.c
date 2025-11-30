#include "common/stl/stl_string.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define STL_STRING_DEFAULT_SIZE (10)
#define STL_STRING_INCREASE_SIZE (128)

struct Stl_String {
    uint32_t length;
    uint32_t capacity;
    char *cstr;
};

static void StlString_AppendVa(Stl_String *string, const char *format, va_list args)
{
    va_list argsCpy;
    va_copy(argsCpy, args);

    int fmtLen = vsnprintf(string->cstr + string->length, string->capacity - string->length, format, args);

    uint32_t newLength = string->length + (uint32_t)fmtLen;

    if (newLength >= string->capacity) {
        uint32_t newCapacity = newLength + STL_STRING_INCREASE_SIZE;
        string->cstr[string->length] = '\0';

        char *newCstr = malloc(newCapacity);
        strncpy(newCstr, string->cstr, newCapacity);
        free(string->cstr);
        string->cstr = newCstr;
        string->capacity = newCapacity;

        fmtLen = vsnprintf(string->cstr + string->length, string->capacity - string->length, format, argsCpy);
        newLength = string->length + (uint32_t)fmtLen;
    }
    va_end(argsCpy);
    string->length = newLength;
    string->cstr[string->length] = '\0'; 
}

Stl_String *StlString_New(const char *format, ...)
{
    if (format == NULL) {
        return NULL;
    }
    Stl_String *string = malloc(sizeof(Stl_String));
    string->length = 0;
    string->capacity = STL_STRING_DEFAULT_SIZE;
    string->cstr = malloc(STL_STRING_DEFAULT_SIZE);
    va_list args;
    va_start(args, format);
    StlString_AppendVa(string, format, args);
    va_end(args);
    return string;
}

void StlString_Append(Stl_String *string, const char* format, ...)
{
    if (string == NULL) {
        return;
    }
    va_list args;
    va_start(args, format);
    StlString_AppendVa(string, format, args);
    va_end(args);
}

const char *StlString_CStr(const Stl_String *string)
{
    if (string == NULL) {
        return NULL;
    }
    return string->cstr;
}

uint32_t StlString_Length(const Stl_String *string)
{
    return string->length;
}

void StlString_Delete(Stl_String *string)
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
