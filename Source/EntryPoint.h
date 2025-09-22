#ifndef DVRPL_ENTRY_PT_H // ========================================================
#define DVRPL_ENTRY_PT_H
#include "__Prelude.h"
#include "Window.h"
EXTERN_C_BEGIN

/**
 * This is the main entry point of the application.
 * It is not actually implemented inside the Dvaarpaal library,
 * but rather in the application that uses the library.
 * This is done to allow the application to have its own entry point.
 *
 * The code for the main entry point (platform-specific) will be included
 * in the built static libraries, but if compiling from source, add
 * `#define DVRPL_SKIP_ENTRY_PT` when compiling the source.
 */
i32 DVRPL_Main(DVRPL_App app, PNSLR_ArraySlice(utf8str) args);

EXTERN_C_END
#endif // DVRPL_ENTRY_PT_H =========================================================
