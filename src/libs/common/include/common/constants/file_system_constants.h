#ifndef COMMON_FILE_SYSTEM_CONSTANTS_H
#define COMMON_FILE_SYSTEM_CONSTANTS_H

#if __cplusplus
extern "C" {
#endif

#if (defined(__MINGW32__) || defined(__MINGW64__)) || (defined (_MSC_VER) && !defined (__clang__))
const char PATH_SEP = '\\';
#else
const char PATH_SEP = '/';
#endif

#if __cplusplus
}
#endif
#endif
