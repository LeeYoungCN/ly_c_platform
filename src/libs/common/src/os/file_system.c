#include "common/os/file_system.h"

#include <stdint.h>

const char *FS_GetFileName(const char *file)
{
    uint32_t rst = 0;
    for (uint32_t i = 0; file[i] != '\0'; i++) {
        if (file[i] == PATH_SEP) {
            rst = i + 1;
        }
    }
    return file + rst;
}
