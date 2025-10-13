#define DVRPL_IMPLEMENTATION
#include "Window.h"
#include "Input.h"

DVRPL_WindowData DVRPL_CreateWindow(DVRPL_WindowCreationOptions options)
{
    return (DVRPL_WindowData){0};
}

void DVRPL_DestroyWindow(DVRPL_WindowData* window)
{
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
