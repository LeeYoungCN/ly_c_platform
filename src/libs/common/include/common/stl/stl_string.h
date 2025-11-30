#ifndef COMMON_STL_STRING_H
#define COMMON_STL_STRING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct Stl_String Stl_String;

Stl_String *StlString_New(const char* format, ...);

void StlString_Append(Stl_String *string, const char* format, ...);

const char* StlString_CStr(const Stl_String *string);

uint32_t StlString_Length(const Stl_String *string);

void StlString_Delete(Stl_String* string);

#ifdef __cplusplus
}
#endif

#endif // COMMON_STL_STRING_H
