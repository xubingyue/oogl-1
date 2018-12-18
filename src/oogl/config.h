//
// Created by xiaozhuai on 2018/12/18.
//
#ifndef OOGL_CONFIG_H
#define OOGL_CONFIG_H


#if defined(_WIN32)

    // Windows
    #define OOGL_SYSTEM_WINDOWS

#elif defined(__APPLE__) && defined(__MACH__)

    // Apple platform, see which one it is
    #include <TargetConditionals.h>

    #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

        // iOS
        #define OOGL_SYSTEM_IOS

    #elif TARGET_OS_MAC

        // MacOS
        #define OOGL_SYSTEM_MACOS

    #else

        // Unsupported Apple system
        #error This Apple operating system is not supported by oogl library

    #endif

// UNIX system, see which one it is
#elif defined(__unix__)

    #if defined(__ANDROID__)

        // Android
        #define OOGL_SYSTEM_ANDROID

    #elif defined(__linux__)

        // Linux
        #define OOGL_SYSTEM_LINUX

    #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

        // FreeBSD
        #define OOGL_SYSTEM_FREEBSD

    #else

        // Unsupported UNIX system
        #error This UNIX operating system is not supported by oogl library

    #endif

#else

    // Unsupported system
    #error This operating system is not supported by oogl library

#endif


#endif //OOGL_CONFIG_H
