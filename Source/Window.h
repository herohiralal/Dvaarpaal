#ifndef DVRPL_WINDOW_H // ==========================================================
#define DVRPL_WINDOW_H
#include "__Prelude.h"
EXTERN_C_BEGIN

/**
 * A cross-platform opaque handle to a window.
 * On Windows, this is an HWND.
 * On OSX, this is an NSWindow*.
 * On Android, this is an ANativeWindow*.
 */
typedef struct DVRPL_Window
{
    u64 handle;
} DVRPL_Window;

/**
 * A cross-platform opaque handle to saved information for a window.
 */
typedef struct alignas(PNSLR_PTR_SIZE) DVRPL_SavedWindowData
{
    u8 buffer[5 * PNSLR_PTR_SIZE];
} DVRPL_SavedWindowData;

/**
 * A cross-platform opaque handle for window data.
 * Includes some amount of saved data for the window.
 */
typedef struct DVRPL_WindowData
{
    DVRPL_Window          window;
    DVRPL_SavedWindowData savedData;
} DVRPL_WindowData;

/**
 * Options for creating a window.
 */
typedef struct DVRPL_WindowCreationOptions
{
    i16          posX;
    i16          posY;
    u16          sizeX;
    u16          sizeY;
    utf8str      title;
    DVRPL_Window parent;
    u8           bgColR;
    u8           bgColG;
    u8           bgColB;
    u8           bgColA;
    b8           msaa;
} DVRPL_WindowCreationOptions;

/**
 * Creates a window with the specified options.
 * Returns a handle to the created window.
 * If creation failed, the returned handle will be zeroed.
 * Not thread-safe.
 */
DVRPL_WindowData DVRPL_CreateWindow(DVRPL_WindowCreationOptions options);

/**
 * Destroys the specified window.
 * Not thread-safe.
 */
void DVRPL_DestroyWindow(DVRPL_WindowData* window);

/**
 * Sets the window's fullscreen status.
 * Returns true on success, false on failure.
 * If entering fullscreen, the previous position and size are stored in the provided pointers.
 * If exiting fullscreen, the window is restored to the provided position and size.
 * If posX, posY, sizeX or sizeY are null, reasonable defaults are used instead.
 * Not thread-safe.
 */
b8 DVRPL_SetFullScreen(
    DVRPL_WindowData* window,
    b8 status,
    i16* posX OPT_ARG,
    i16* posY OPT_ARG,
    u16* sizeX OPT_ARG,
    u16* sizeY OPT_ARG
);

/**
 * Gets the window's current position and size.
 * Returns true on success, false on failure.
 * If any of posX, posY, sizeX or sizeY are null, they are ignored, otherwise
 * the corresponding value is written to the provided pointer.
 * Not thread-safe.
 */
b8 DVRPL_GetWindowDimensions(DVRPL_WindowData* window, i16* posX, i16* posY, u16* sizeX, u16* sizeY);

/**
 * Get the current position of the pointer relative to the window's top-left corner.
 * Returns true on success, false on failure.
 * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
 * Not thread-safe.
 */
b8 DVRPL_GetPtrPosFromWindow(DVRPL_Window window, i16* posX, i16* posY);

/**
 * Get the current position of the pointer relative to the screen's top-left corner.
 * Returns true on success, false on failure.
 * If posX or posY are null, they are ignored, otherwise the corresponding value is written to the provided pointer.
 * Not thread-safe.
 */
b8 DVRPL_GetPtrPos(i16* posX, i16* posY);

//+skipreflect
#ifdef DVRPL_IMPLEMENTATION
    #if PNSLR_WINDOWS
        typedef HWND NativeWindowHandle;
        static const NativeWindowHandle InvalidWindowHandle = NULL;

        typedef struct
        {
            RECT rect;
            LONG savedStyle;
            LONG savedExStyle;
        } NativeSavedWindowData;
    #else
        #error "Unimplemented."
    #endif

    static_assert(sizeof(DVRPL_Window)  == sizeof(NativeWindowHandle),  "DVRPL_Window and NativeWindowHandle must have the same size.");
    static_assert(alignof(DVRPL_Window) == alignof(NativeWindowHandle), "DVRPL_Window and NativeWindowHandle must have the same alignment.");

    static_assert(sizeof(DVRPL_SavedWindowData)  >= sizeof(NativeSavedWindowData),  "DVRPL_SavedWindowData must be large   enough to hold NativeSavedWindowData.");
    static_assert(alignof(DVRPL_SavedWindowData) >= alignof(NativeSavedWindowData), "DVRPL_SavedWindowData must be aligned enough to hold NativeSavedWindowData.");

    #define DVRPL_BREAK_WINDOW_HANDLE(h) (*(NativeWindowHandle*)&((h).handle))
    #define DVRPL_MAKE_WINDOW_HANDLE(h)  ((DVRPL_Window){.handle=*(u64*)&(h)})

    #define DVRPL_BREAK_SAVED_WINDOW_DATA(d) (*(NativeSavedWindowData*)&((d).buffer))
    static forceinline DVRPL_SavedWindowData DVRPL_MAKE_SAVED_WINDOW_DATA(NativeSavedWindowData d)
    {
        DVRPL_SavedWindowData result = {0};
        PNSLR_MemCopy(&result, &d, sizeof(NativeSavedWindowData));
        return result;
    }
#endif
//-skipreflect

EXTERN_C_END
#endif // DVRPL_WINDOW_H ===========================================================
