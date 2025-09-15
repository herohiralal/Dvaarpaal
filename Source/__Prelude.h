#ifndef DVRPL_ENTRY_H // ===========================================================
#define DVRPL_ENTRY_H
//+skipreflect

// Includes ========================================================================

#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Compiler.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Platforms.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Warnings.h"
#ifdef DVRPL_IMPLEMENTATION

    #if PNSLR_WINDOWS
        #define WIN32_LEAN_AND_MEAN
        #include <Windows.h>
        #include <shellapi.h>
        #undef WIN32_LEAN_AND_MEAN
    #endif

#endif
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Primitives.h"
#include "Dependencies/Panshilar/Source/Dependencies/PNSLR_Intrinsics/Macros.h"
#include "Dependencies/Panshilar/Source/Panshilar.h"

//-skipreflect
#endif // DVRPL_ENTRY_H ============================================================
