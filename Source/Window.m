#define DVRPL_IMPLEMENTATION
#include "Window.h"
#include "Input.h"

static b8 G_DVRPL_Internal_OSXAppInitialised = false;

DVRPL_WindowData DVRPL_CreateWindow(DVRPL_WindowCreationOptions options)
{
    @autoreleasepool {
        NSApplication* app = (__bridge NSApplication*) DVRPL_BREAK_APP_HANDLE(options.app);
        if (!G_DVRPL_Internal_OSXAppInitialised)
        {
            DVRPL_Internal_AppleSetApp(app);
            G_DVRPL_Internal_OSXAppInitialised = true;
        }

        NSRect rect = NSMakeRect(options.posX, options.posY, options.sizeX, options.sizeY);
        NSWindowStyleMask style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;

        NSWindow* nativeWindow = [NSWindow alloc];

        nativeWindow = [nativeWindow initWithContentRect:rect
                                               styleMask:style
                                                 backing:NSBackingStoreBuffered
                                                   defer:NO];

        cstring titleStr = PNSLR_CStringFromString(options.title, PNSLR_GetAllocator_DefaultHeap());
        NSString* titleNsStr = [NSString stringWithUTF8String:titleStr];
        [nativeWindow setTitle:titleNsStr];
        [nativeWindow makeKeyAndOrderFront:nil];

        PNSLR_FreeCString(titleStr, PNSLR_GetAllocator_DefaultHeap(), PNSLR_GET_LOC(), nil);

        DVRPL_WindowData windowData = {0};
        windowData.window = DVRPL_MAKE_WINDOW_HANDLE((__bridge_retained rawptr) nativeWindow);

        return windowData;
    }
}

void DVRPL_DestroyWindow(DVRPL_WindowData* window)
{
    @autoreleasepool {
        NSWindow* wnd = (__bridge_transfer NSWindow*) DVRPL_BREAK_WINDOW_HANDLE(window->window);
        [wnd close];
        window->window = DVRPL_MAKE_WINDOW_HANDLE(DVRPL_Internal_InvalidWindowHandle);
    }
}

b8 DVRPL_SetFullScreen(DVRPL_WindowData* window, b8 status, i16* posX, i16* posY, u16* sizeX, u16* sizeY)
{
    return false;
}

b8 DVRPL_GetWindowDimensions(DVRPL_WindowData* window, i16* posX, i16* posY, u16* sizeX, u16* sizeY)
{
    return false;
}

b8 DVRPL_GetPtrPosFromWindow(DVRPL_Window window, i16* posX, i16* posY)
{
    return false;
}

b8 DVRPL_GetPtrPos(i16* posX, i16* posY)
{
    return false;
}
