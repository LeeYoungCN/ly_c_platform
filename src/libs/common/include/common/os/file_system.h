#ifndef COMMON_OS_FILE_SYSTEM_H
#define COMMON_OS_FILE_SYSTEM_H
#ifdef __cplusplus
extern "C" {
#endif
#include "common/compiler/macros.h"

#if PLATFORM_WINDOWS && !defined(__clang__)
const char PATH_SEP = '\\';  ///< Windows系统路径分隔符
#else
const char PATH_SEP = '/';  ///< Unix系统路径分隔符
#endif

const char *FS_GetFileName(const char *file);

#ifdef __cplusplus
}
#endif
#endif  // COMMON_OS_FILE_SYSTEM_H
