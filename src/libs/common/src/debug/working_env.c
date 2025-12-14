#include "common/debug/working_env.h"

#include "common/compiler/macros.h"
#if PLATFORM_WINDOWS
#include <windows.h>
#elif PLATFORM_LINUX
#include <unistd.h>  // Linux的readlink函数
#elif PLATFORM_MACOS
#include <mach-o/dyld.h>  // macOS的_NSGetExecutablePath
#endif
#include <stdint.h>
#include <stdio.h>

#define PATH_BUFFER_LEN 1024

static void PrintGetOsName(void)
{
    const char* OS = NULL;
#ifdef _WIN32
// Windows 32位或64位（_WIN32在64位系统上也会定义）
#ifdef _WIN64
    OS = "Windows 64-bit";
#else
    return "Windows 32-bit";
#endif
#elif defined(__linux__)
    // Linux 系统
    OS = "Linux";
#elif defined(__APPLE__) && defined(__MACH__)
    // macOS 系统（基于 Mach 内核）
    OS = "macOS";
#elif defined(__FreeBSD__)
    // FreeBSD 系统
    OS = "FreeBSD";
#elif defined(__NetBSD__)
    // NetBSD 系统
    OS = "NetBSD";
#elif defined(__OpenBSD__)
    // OpenBSD 系统
    OS = "OpenBSD";
#else
    // 未知操作系统
    OS = "Unknown OS";
#endif
    printf("OS: %s\n", OS);
}

static void PrintGetCompilers(void)
{
    const char* COMPILERS[] = {
#ifdef _MSC_VER
        "_MSC_VER",
#endif
#ifdef __clang__
        "__clang__",
#endif
#ifdef __MINGW32__
        "__MINGW32__",
#endif
#ifdef __MINGW64__
        "__MINGW64__",
#endif
#ifdef __GNUC__
        "__GNUC__",
#endif
    };
    printf("Compiler: ");
    for (uint32_t i = 0; i < sizeof(COMPILERS) / sizeof(char*); i++) {
        printf("%s, ", COMPILERS[i]);
    }
    printf("\n");
}

static void PrintProcessPath(void)
{
    char path[PATH_BUFFER_LEN] = {'\0'};
#if PLATFORM_WINDOWS
    GetModuleFileNameA(NULL, path, PATH_BUFFER_LEN);
#elif PLATFORM_LINUX
    auto length = readlink("/proc/self/exe", path, PATH_BUFFER_LEN - 1);
    path[length] = '\0';
#elif PLATFORM_MACOS
    uint32_t size = sizeof(path);
    _NSGetExecutablePath(path, &size);
#else
#error "Unsupport system."
#endif
    printf("ProcessPath: %s\n", path);
}

static void PrintArchitecture(void)
{
// x86 架构 (32位)
#if defined(__i386__) || defined(_M_IX86)
    const char* ARC = "x86 (32-bit)";

// x86_64 架构 (64位)
#elif defined(__x86_64__) || defined(_M_X64)
    const char* ARC = "x86_64 (64-bit)";

// ARM 架构 (32位)
#elif defined(__arm__) || defined(_M_ARM)
    const char* ARC = "ARM (32-bit)";

// ARM64 架构 (64位)
#elif defined(__aarch64__) || defined(_M_ARM64)
    const char* ARC = "ARM64 (64-bit)";

// 其他常见架构
#elif defined(__powerpc__) || defined(__ppc__)
    const char* ARC = "PowerPC";
#elif defined(__mips__)
    const char* ARC = "MIPS";
#elif defined(__riscv)
    const char* ARC = "RISC-V";

// 未知架构
#else
    return "Unknown architecture";
#endif
    printf("ARC: %s\n", ARC);
}

static void PrintEnvParams(void)
{
    const char* ENV_NAMES[] = {"PATH", "LD_LIBRARY_PATH", "LIBPATH", "LIB", "INCLUDE"};

    for (uint32_t i = 0; i < sizeof(ENV_NAMES) / sizeof(char*); i++) {
        const char* name = ENV_NAMES[i];
        char* value = NULL;
        errno_t err = 0;
        size_t len = 0;
#if COMPILER_MSVC
        err = _dupenv_s(&value, &len, name);
#else
        (void)err;
        (void)len;
        value = getenv(name);
#endif
        if (err == 0 && value != NULL) {
            printf("-------------------- %s  --------------------\n", name);
            printf("%s: %s\n", name, value);
#if COMPILER_MSVC
            free(value);
#endif
        }
    }
}

static void PrintfCStandard(void)
{
#if defined(__STDC_VERSION__)
#if __STDC_VERSION__ >= 202311L
    const char* STANDARD = "C23";
#elif __STDC_VERSION__ >= 201710L
    const char* STANDARD = "C17/C18";
#elif __STDC_VERSION__ >= 201112L
    const char* STANDARD = "C11";
#el #if __STDC_VERSION__ >= 199901L
    const char* STANDARD = "C99";
#else
    const char* STANDARD = "C89/C90";
#endif
#else
#error "Unknown architecture";
#endif
    printf("C standard: %s\n", STANDARD);
}

static void PrintWorkingDir(void)
{
    char cwd[PATH_BUFFER_LEN] = {'\0'};
#if PLATFORM_WINDOWS
    // 获取当前工作目录
    GetCurrentDirectory(PATH_BUFFER_LEN, cwd);
#else
    char cwd[PATH_BUFFER_LEN];
    // 获取当前工作目录
    getcwd(cwd, sizeof(cwd));
#endif
    printf("Wording directory: %s\n", cwd);
}

void ShowWorkingEnv(void)
{
    PrintGetOsName();
    PrintArchitecture();
    PrintProcessPath();
    PrintWorkingDir();
    PrintGetCompilers();
    PrintfCStandard();
    PrintEnvParams();
}
