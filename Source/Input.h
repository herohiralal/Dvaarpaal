#ifndef DVRPL_INPUT_H // ===========================================================
#define DVRPL_INPUT_H
#include "__Prelude.h"
#include "Window.h"
EXTERN_C_BEGIN

/**
 * The type of input event that was logged.
 */
ENUM_START(DVRPL_EvtTy, u8)
    #define DVRPL_EvtTy_Unknown    ((DVRPL_EvtTy) 0)
    #define DVRPL_EvtTy_Keyboard   ((DVRPL_EvtTy) 1)
    #define DVRPL_EvtTy_MouseWheel ((DVRPL_EvtTy) 2)
    #define DVRPL_EvtTy_Touch      ((DVRPL_EvtTy) 3)
    #define DVRPL_EvtTy_TextInput  ((DVRPL_EvtTy) 4)
    #define DVRPL_EvtTy_DropFile   ((DVRPL_EvtTy) 5)
    #define DVRPL_EvtTy_Quit       ((DVRPL_EvtTy) 6)
ENUM_END

/**
 * The information regarding a window move event.
 */
typedef struct DVRPL_WindowMoveData
{
    DVRPL_Window id;
    i16          posX;
    i16          posY;
} DVRPL_WindowMoveData;

/**
 * The information regarding a window resize event.
 */
typedef struct DVRPL_WindowResizeData
{
    DVRPL_Window id;
    u16          sizeX;
    u16          sizeY;
} DVRPL_WindowResizeData;

/**
 * The status of a touch event.
 */
ENUM_START(DVRPL_TouchStatus, u8)
    #define DVRPL_TouchStatus_Moved    ((DVRPL_TouchStatus) 0)
    #define DVRPL_TouchStatus_Pressed  ((DVRPL_TouchStatus) 1)
    #define DVRPL_TouchStatus_Released ((DVRPL_TouchStatus) 2)
ENUM_END

// Technically can just bundle this into `DVRPL_EvtTy` but considering
// how people usually use input events, first they wanna know  which key
// it was, and then whether it was pressed or released, not specifically
// tracking downs/ups and then figuring out which key.
/**
 * The status of a key event.
 */
ENUM_START(DVRPL_KeyStatus, u8)
    #define DVRPL_KeyStatus_Pressed  ((DVRPL_KeyStatus) 0)
    #define DVRPL_KeyStatus_Released ((DVRPL_KeyStatus) 1)
ENUM_END

/**
 * The possible states of a key event.
 */
ENUM_FLAGS_START(DVRPL_KeyState, u8)
    #define DVRPL_KeyState_None     ((DVRPL_KeyStateFlags) 0)
    #define DVRPL_KeyState_Pressed  ((DVRPL_KeyStateFlags) (1ULL << 0))
    #define DVRPL_KeyState_Held     ((DVRPL_KeyStateFlags) (1ULL << 1))
    #define DVRPL_KeyState_Released ((DVRPL_KeyStateFlags) (1ULL << 2))
ENUM_END

/**
 * Any modifiers that are added to a key event.
 */
ENUM_FLAGS_START(DVRPL_KeyModifier, u8)
    #define DVRPL_KeyModifier_None      ((DVRPL_KeyModifier) 0)
    #define DVRPL_KeyModifier_Alt       ((DVRPL_KeyModifier) (1ULL << 0))
    #define DVRPL_KeyModifier_Control   ((DVRPL_KeyModifier) (1ULL << 1))
    #define DVRPL_KeyModifier_Shift     ((DVRPL_KeyModifier) (1ULL << 2))
    #define DVRPL_KeyModifier_CmdOrMeta ((DVRPL_KeyModifier) (1ULL << 3))
ENUM_END

ENUM_START(DVRPL_InputControl, u8)
    #define DVRPL_InputControl_MouseLeft               ((DVRPL_InputControl)   0)
    #define DVRPL_InputControl_MouseRight              ((DVRPL_InputControl)   1)
    #define DVRPL_InputControl_MouseMiddle             ((DVRPL_InputControl)   2)
    #define DVRPL_InputControl_Mouse4                  ((DVRPL_InputControl)   3)
    #define DVRPL_InputControl_Mouse5                  ((DVRPL_InputControl)   4)
    #define DVRPL_InputControl_Mouse6                  ((DVRPL_InputControl)   5)
    #define DVRPL_InputControl_Mouse7                  ((DVRPL_InputControl)   6)
    #define DVRPL_InputControl_MouseX                  ((DVRPL_InputControl)   7)
    #define DVRPL_InputControl_MouseY                  ((DVRPL_InputControl)   8)
    #define DVRPL_InputControl_MouseWheel              ((DVRPL_InputControl)   9)
    #define DVRPL_InputControl_Backtick                ((DVRPL_InputControl)  10)
    #define DVRPL_InputControl_One                     ((DVRPL_InputControl)  11)
    #define DVRPL_InputControl_Two                     ((DVRPL_InputControl)  12)
    #define DVRPL_InputControl_Three                   ((DVRPL_InputControl)  13)
    #define DVRPL_InputControl_Four                    ((DVRPL_InputControl)  14)
    #define DVRPL_InputControl_Five                    ((DVRPL_InputControl)  15)
    #define DVRPL_InputControl_Six                     ((DVRPL_InputControl)  16)
    #define DVRPL_InputControl_Seven                   ((DVRPL_InputControl)  17)
    #define DVRPL_InputControl_Eight                   ((DVRPL_InputControl)  18)
    #define DVRPL_InputControl_Nine                    ((DVRPL_InputControl)  19)
    #define DVRPL_InputControl_Zero                    ((DVRPL_InputControl)  20)
    #define DVRPL_InputControl_Minus                   ((DVRPL_InputControl)  21)
    #define DVRPL_InputControl_Equals                  ((DVRPL_InputControl)  22)
    #define DVRPL_InputControl_Backspace               ((DVRPL_InputControl)  23)
    #define DVRPL_InputControl_Tab                     ((DVRPL_InputControl)  24)
    #define DVRPL_InputControl_Q                       ((DVRPL_InputControl)  25)
    #define DVRPL_InputControl_W                       ((DVRPL_InputControl)  26)
    #define DVRPL_InputControl_E                       ((DVRPL_InputControl)  27)
    #define DVRPL_InputControl_R                       ((DVRPL_InputControl)  28)
    #define DVRPL_InputControl_T                       ((DVRPL_InputControl)  29)
    #define DVRPL_InputControl_Y                       ((DVRPL_InputControl)  30)
    #define DVRPL_InputControl_U                       ((DVRPL_InputControl)  31)
    #define DVRPL_InputControl_I                       ((DVRPL_InputControl)  32)
    #define DVRPL_InputControl_O                       ((DVRPL_InputControl)  33)
    #define DVRPL_InputControl_P                       ((DVRPL_InputControl)  34)
    #define DVRPL_InputControl_SquareBracketLeft       ((DVRPL_InputControl)  35)
    #define DVRPL_InputControl_SquareBracketRight      ((DVRPL_InputControl)  36)
    #define DVRPL_InputControl_Backslash               ((DVRPL_InputControl)  37)
    #define DVRPL_InputControl_A                       ((DVRPL_InputControl)  38)
    #define DVRPL_InputControl_S                       ((DVRPL_InputControl)  39)
    #define DVRPL_InputControl_D                       ((DVRPL_InputControl)  40)
    #define DVRPL_InputControl_F                       ((DVRPL_InputControl)  41)
    #define DVRPL_InputControl_G                       ((DVRPL_InputControl)  42)
    #define DVRPL_InputControl_H                       ((DVRPL_InputControl)  43)
    #define DVRPL_InputControl_J                       ((DVRPL_InputControl)  44)
    #define DVRPL_InputControl_K                       ((DVRPL_InputControl)  45)
    #define DVRPL_InputControl_L                       ((DVRPL_InputControl)  46)
    #define DVRPL_InputControl_Semicolon               ((DVRPL_InputControl)  47)
    #define DVRPL_InputControl_Apostrophe              ((DVRPL_InputControl)  48)
    #define DVRPL_InputControl_Enter                   ((DVRPL_InputControl)  49)
    #define DVRPL_InputControl_LeftShift               ((DVRPL_InputControl)  50)
    #define DVRPL_InputControl_Z                       ((DVRPL_InputControl)  51)
    #define DVRPL_InputControl_X                       ((DVRPL_InputControl)  52)
    #define DVRPL_InputControl_C                       ((DVRPL_InputControl)  53)
    #define DVRPL_InputControl_V                       ((DVRPL_InputControl)  54)
    #define DVRPL_InputControl_B                       ((DVRPL_InputControl)  55)
    #define DVRPL_InputControl_N                       ((DVRPL_InputControl)  56)
    #define DVRPL_InputControl_M                       ((DVRPL_InputControl)  57)
    #define DVRPL_InputControl_Comma                   ((DVRPL_InputControl)  58)
    #define DVRPL_InputControl_FullStop                ((DVRPL_InputControl)  59)
    #define DVRPL_InputControl_Slash                   ((DVRPL_InputControl)  60)
    #define DVRPL_InputControl_RightShift              ((DVRPL_InputControl)  61)
    #define DVRPL_InputControl_LeftControl             ((DVRPL_InputControl)  62)
    #define DVRPL_InputControl_LeftAlt                 ((DVRPL_InputControl)  63)
    #define DVRPL_InputControl_Space                   ((DVRPL_InputControl)  64)
    #define DVRPL_InputControl_RightAlt                ((DVRPL_InputControl)  65)
    #define DVRPL_InputControl_RightControl            ((DVRPL_InputControl)  66)
    #define DVRPL_InputControl_Up                      ((DVRPL_InputControl)  67)
    #define DVRPL_InputControl_Down                    ((DVRPL_InputControl)  68)
    #define DVRPL_InputControl_Left                    ((DVRPL_InputControl)  69)
    #define DVRPL_InputControl_Right                   ((DVRPL_InputControl)  70)
    #define DVRPL_InputControl_Numpad0                 ((DVRPL_InputControl)  71)
    #define DVRPL_InputControl_Numpad1                 ((DVRPL_InputControl)  72)
    #define DVRPL_InputControl_Numpad2                 ((DVRPL_InputControl)  73)
    #define DVRPL_InputControl_Numpad3                 ((DVRPL_InputControl)  74)
    #define DVRPL_InputControl_Numpad4                 ((DVRPL_InputControl)  75)
    #define DVRPL_InputControl_Numpad5                 ((DVRPL_InputControl)  76)
    #define DVRPL_InputControl_Numpad6                 ((DVRPL_InputControl)  77)
    #define DVRPL_InputControl_Numpad7                 ((DVRPL_InputControl)  78)
    #define DVRPL_InputControl_Numpad8                 ((DVRPL_InputControl)  79)
    #define DVRPL_InputControl_Numpad9                 ((DVRPL_InputControl)  80)
    #define DVRPL_InputControl_NumpadDivide            ((DVRPL_InputControl)  81)
    #define DVRPL_InputControl_NumpadMultiply          ((DVRPL_InputControl)  82)
    #define DVRPL_InputControl_NumpadMinus             ((DVRPL_InputControl)  83)
    #define DVRPL_InputControl_NumpadPlus              ((DVRPL_InputControl)  84)
    #define DVRPL_InputControl_NumpadEnter             ((DVRPL_InputControl)  85)
    #define DVRPL_InputControl_NumpadDecimal           ((DVRPL_InputControl)  86)
    #define DVRPL_InputControl_GamepadLeftShoulder     ((DVRPL_InputControl)  87)
    #define DVRPL_InputControl_GamepadLeftTrigger      ((DVRPL_InputControl)  88)
    #define DVRPL_InputControl_GamepadRightShoulder    ((DVRPL_InputControl)  89)
    #define DVRPL_InputControl_GamepadRightTrigger     ((DVRPL_InputControl)  90)
    #define DVRPL_InputControl_GamepadSelect           ((DVRPL_InputControl)  91)
    #define DVRPL_InputControl_GamepadStart            ((DVRPL_InputControl)  92)
    #define DVRPL_InputControl_GamepadLeftThumbstick   ((DVRPL_InputControl)  93)
    #define DVRPL_InputControl_GamepadLeftThumbstickX  ((DVRPL_InputControl)  94)
    #define DVRPL_InputControl_GamepadLeftThumbstickY  ((DVRPL_InputControl)  95)
    #define DVRPL_InputControl_GamepadRightThumbstick  ((DVRPL_InputControl)  96)
    #define DVRPL_InputControl_GamepadRightThumbstickX ((DVRPL_InputControl)  97)
    #define DVRPL_InputControl_GamepadRightThumbstickY ((DVRPL_InputControl)  98)
    #define DVRPL_InputControl_GamepadDPadUp           ((DVRPL_InputControl)  99)
    #define DVRPL_InputControl_GamepadDPadDown         ((DVRPL_InputControl) 100)
    #define DVRPL_InputControl_GamepadDPadLeft         ((DVRPL_InputControl) 101)
    #define DVRPL_InputControl_GamepadDPadRight        ((DVRPL_InputControl) 102)
    #define DVRPL_InputControl_GamepadFaceButtonTop    ((DVRPL_InputControl) 103)
    #define DVRPL_InputControl_GamepadFaceButtonBottom ((DVRPL_InputControl) 104)
    #define DVRPL_InputControl_GamepadFaceButtonLeft   ((DVRPL_InputControl) 105)
    #define DVRPL_InputControl_GamepadFaceButtonRight  ((DVRPL_InputControl) 106)
ENUM_END

EXTERN_C_END
#endif // DVRPL_INPUT_H ============================================================
