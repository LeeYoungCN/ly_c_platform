#ifndef CSTL_CSTL_ERROR_CODE_H
#define CSTL_CSTL_ERROR_CODE_H
#include "common/types/error_code.h"

#define CSTL_MODULE_ID 1

// 内存操作
#define ERR_CSTL_OUT_OF_RANGE MAKE_ERROR(ERR_SEV_ERROR, CSTL_MODULE_ID, COMM_ERR_TYPE_MEM, 1)  // 超越最大容量

const char *CStl_GetErrMsg(ErrorCode errCode);

#endif  // CSTL_CSTL_ERROR_CODE_H
