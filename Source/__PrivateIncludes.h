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

#if PNSLR_ANDROID
    #include "Dependencies/AndroidGameActivity/game-activity/android_native_app_glue.h"
    #include "Dependencies/AndroidGameActivity/game-activity/GameActivityEvents.h"
    #ifdef DVRPL_IMPLEMENTATION
        // it includes stdbool, which defines bool, which we 'uninclude'
        #include "Dependencies/AndroidGameActivity/UnityBuild.c"
    #endif
#endif

PNSLR_UNSUPPRESS_WARN

#endif//DVRPL_PRIVATE_INCLUDES_H
