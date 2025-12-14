#include "common/utils/file_system_utils.h"

#include <stdint.h>

#include "common/constants/file_system_constants.h"

const char *Utils_GetFileName(const char *file)
{
    uint32_t rst = 0;
    for (uint32_t i = 0; file[i] != '\0'; i++) {
        if (file[i] == PATH_SEP) {
            rst = i + 1;
        }
    }
    return file + rst;
}
