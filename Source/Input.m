#define DVRPL_IMPLEMENTATION
#include "Input.h"

void DVRPL_Internal_AppleResizeEventsIfBufferFull(void);
void DVRPL_Internal_AppleClearExistingInputData(void);

void DVRPL_Internal_AppleGatherEvents(PNSLR_Allocator tempAllocator)
{
    DVRPL_Internal_AppleResizeEventsIfBufferFull();
    DVRPL_Internal_AppleClearExistingInputData();
}
