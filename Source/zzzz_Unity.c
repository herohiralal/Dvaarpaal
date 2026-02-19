#ifndef DVRPL_UNITY_C
#define DVRPL_UNITY_C

#define PNSLR_IMPLEMENTATION
#define DVRPL_IMPLEMENTATION
#include "__Prelude.h"

#include "Window.c"
#include "Input.c"
#include "EntryPoint.c"

#include "../../Panshilar/Source/zzzz_Unity.c"

#if PNSLR_ANDROID
    PNSLR_SUPPRESS_WARN
    #include <android_native_app_glue.c>
    PNSLR_UNSUPPRESS_WARN
#endif

#endif//DVRPL_UNITY_C
