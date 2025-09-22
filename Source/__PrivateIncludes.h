#ifndef DVRPL_PRIVATE_INLCUDES_H
#define DVRPL_PRIVATE_INLCUDES_H

#include "Dependencies/Panshilar/Source/__PrivateIncludes.h"

PNSLR_SUPPRESS_WARN

#if PNSLR_WINDOWS
    #pragma comment(lib, "User32.lib")
    #pragma comment(lib, "Shell32.lib")
    #pragma comment(lib, "Gdi32.lib")
#endif

#if PNSLR_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <shellapi.h>
    #include <hidusage.h>
    #undef WIN32_LEAN_AND_MEAN
#endif

PNSLR_UNSUPPRESS_WARN

#endif//DVRPL_PRIVATE_INCLUDES_H
