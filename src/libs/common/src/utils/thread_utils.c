/**
 * @file thread_utils.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "common/utils/thread_utils.h"

#include <string.h>
#include <threads.h>

#include "common/compiler/macros.h"
#include "common/types/thread_types.h"

#if PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM_LINUX
#include <sys/syscall.h>
#include <unistd.h>
#elif PLATFORM_MACOS
#include <pthread.h>
#else
#error "Unsupport system"
#endif

#define THREAD_NAME_LEN 64

thread_local char g_threadName[THREAD_NAME_LEN] = "";

ThreadId GetCurrentThreadIdInternal(void)
{
#if PLATFORM_WINDOWS
    return (ThreadId)(GetCurrentThreadId());
#elif PLATFORM_LINUX
    return (ThreadId)(syscall(SYS_gettid));
#elif PLATFORM_MACOS
    uint64_t tid;
    pthread_threadid_np(nullptr, &tid);
    return (ThreadId)(tid);
#else
    return 0;
#endif
}

ThreadId GetCurrentThreadId(void)
{
    static thread_local ThreadId tid = 0;
    if (tid == 0) {
        tid = GetCurrentThreadIdInternal();
    }
    return tid;
}

void SetCurrentThreadName(const char *name)
{
    strncpy(g_threadName, name, THREAD_NAME_LEN);
}

const char *GetCurrentThreadName(void)
{
    return g_threadName;
}
