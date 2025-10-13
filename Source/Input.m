#define DVRPL_IMPLEMENTATION
#include "Input.h"

void DVRPL_Internal_AppleResizeEventsIfBufferFull(void);
void DVRPL_Internal_AppleClearExistingInputData(void);

#if PNSLR_OSX
    static NSApplication* G_DVRPL_Internal_OSXApp = nil;
#endif

static void DVRPL_Internal_AppleSetApp(NSApplication* app)
{
    G_DVRPL_Internal_OSXApp = app;
}

void DVRPL_Internal_AppleGatherEvents(
    PNSLR_Allocator* currTempAllocator,
    PNSLR_ArraySlice(utf8str)* tempDroppedFiles,
    i64* numTempDroppedFiles,
    PNSLR_ArraySlice(DVRPL_WindowResizeData)* tempResizes,
    i64* numTempResizes,
    PNSLR_ArraySlice(DVRPL_WindowMoveData)* tempMoves,
    i64* numTempMoves,
    PNSLR_ArraySlice(DVRPL_Event)* events,
    i64* numEvents,
    i32* mouseDeltas,
    DVRPL_KeyState* keyStates,
    b8* appHasFocus,
    PNSLR_Allocator tempAllocator
)
{
    @autoreleasepool {
        DVRPL_Internal_AppleClearExistingInputData();

        NSEvent* event = [G_DVRPL_Internal_OSXApp nextEventMatchingMask:NSEventMaskAny
                                                              untilDate:[NSDate dateWithTimeIntervalSinceNow:0.01]
                                                                 inMode:NSDefaultRunLoopMode
                                                                dequeue:YES];

        if (event)
        {
            // TODO: handle event internals here
            [G_DVRPL_Internal_OSXApp sendEvent:event];
            [G_DVRPL_Internal_OSXApp updateWindows];
        }
    }
}
