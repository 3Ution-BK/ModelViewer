#ifndef MODELVIEWER_EVENT_KEYBOARDCODE_HPP_
#define MODELVIEWER_EVENT_KEYBOARDCODE_HPP_

#include "OpenGL/OpenGLLib.hpp"

namespace Event
{

/**
 * \brief Represent the available keycode of the keyboard.
 *
 * The enum storage is the same as the int, which is what input key code glfw is
 * using.
 */
enum class KeyboardCode : int
{
    // Unknown
    Unknown = GLFW_KEY_UNKNOWN, ///< Unknown key.

    // ASCII printable keys
    Space = GLFW_KEY_SPACE,                ///< Space key.
    Apostrophe = GLFW_KEY_APOSTROPHE,      ///< Apostrophe "'".
    Comma = GLFW_KEY_COMMA,                ///< Comma ",".
    Minus = GLFW_KEY_MINUS,                ///< Minus "-".
    Period = GLFW_KEY_PERIOD,              ///< Period ".".
    Slash = GLFW_KEY_SLASH,                ///< Slash "/".
    Alpha0 = GLFW_KEY_0,                   ///< Alphanumeric "0".
    Alpha1 = GLFW_KEY_1,                   ///< Alphanumeric "1".
    Alpha2 = GLFW_KEY_2,                   ///< Alphanumeric "2".
    Alpha3 = GLFW_KEY_3,                   ///< Alphanumeric "3".
    Alpha4 = GLFW_KEY_4,                   ///< Alphanumeric "4".
    Alpha5 = GLFW_KEY_5,                   ///< Alphanumeric "5".
    Alpha6 = GLFW_KEY_6,                   ///< Alphanumeric "6".
    Alpha7 = GLFW_KEY_7,                   ///< Alphanumeric "7".
    Alpha8 = GLFW_KEY_8,                   ///< Alphanumeric "8".
    Alpha9 = GLFW_KEY_9,                   ///< Alphanumeric "9".
    Semicolon = GLFW_KEY_SEMICOLON,        ///< Semicolon ";".
    Equal = GLFW_KEY_EQUAL,                ///< Equal "=".
    A = GLFW_KEY_A,                        ///< Alphanumeric "A".
    B = GLFW_KEY_B,                        ///< Alphanumeric "B".
    C = GLFW_KEY_C,                        ///< Alphanumeric "C".
    D = GLFW_KEY_D,                        ///< Alphanumeric "D".
    E = GLFW_KEY_E,                        ///< Alphanumeric "E".
    F = GLFW_KEY_F,                        ///< Alphanumeric "F".
    G = GLFW_KEY_G,                        ///< Alphanumeric "G".
    H = GLFW_KEY_H,                        ///< Alphanumeric "H".
    I = GLFW_KEY_I,                        ///< Alphanumeric "I".
    J = GLFW_KEY_J,                        ///< Alphanumeric "J".
    K = GLFW_KEY_K,                        ///< Alphanumeric "K".
    L = GLFW_KEY_L,                        ///< Alphanumeric "L".
    M = GLFW_KEY_M,                        ///< Alphanumeric "M".
    N = GLFW_KEY_N,                        ///< Alphanumeric "N".
    O = GLFW_KEY_O,                        ///< Alphanumeric "O".
    P = GLFW_KEY_P,                        ///< Alphanumeric "P".
    Q = GLFW_KEY_Q,                        ///< Alphanumeric "Q".
    R = GLFW_KEY_R,                        ///< Alphanumeric "R".
    S = GLFW_KEY_S,                        ///< Alphanumeric "S".
    T = GLFW_KEY_T,                        ///< Alphanumeric "T".
    U = GLFW_KEY_U,                        ///< Alphanumeric "U".
    V = GLFW_KEY_V,                        ///< Alphanumeric "V".
    W = GLFW_KEY_W,                        ///< Alphanumeric "W".
    X = GLFW_KEY_X,                        ///< Alphanumeric "X".
    Y = GLFW_KEY_Y,                        ///< Alphanumeric "Y".
    Z = GLFW_KEY_Z,                        ///< Alphanumeric "Z".
    LeftBracket = GLFW_KEY_LEFT_BRACKET,   ///< LeftBracket "[".
    BackSlash = GLFW_KEY_BACKSLASH,        ///< BackSlash "\\".
    RightBracket = GLFW_KEY_RIGHT_BRACKET, ///< RightBracket "]".
    GraveAccent = GLFW_KEY_GRAVE_ACCENT,   ///< GraveAccent "`".
    World1 = GLFW_KEY_WORLD_1,             ///< non-US #1.
    World2 = GLFW_KEY_WORLD_2,             ///< non-US #2.

    // Function keys
    Escape = GLFW_KEY_ESCAPE,              ///< Escape.
    Enter = GLFW_KEY_ENTER,                ///< Enter.
    Tab = GLFW_KEY_TAB,                    ///< Tab.
    Backspace = GLFW_KEY_BACKSPACE,        ///< Backspace.
    Insert = GLFW_KEY_INSERT,              ///< Insert.
    Delete = GLFW_KEY_DELETE,              ///< Delete.
    Right = GLFW_KEY_RIGHT,                ///< Right.
    Left = GLFW_KEY_LEFT,                  ///< Left.
    Down = GLFW_KEY_DOWN,                  ///< Down.
    Up = GLFW_KEY_UP,                      ///< Up.
    PageUp = GLFW_KEY_PAGE_UP,             ///< Page up.
    PageDown = GLFW_KEY_PAGE_DOWN,         ///< Page down.
    Home = GLFW_KEY_HOME,                  ///< Home.
    End = GLFW_KEY_END,                    ///< End.
    CapsLock = GLFW_KEY_CAPS_LOCK,         ///< Caps Lock.
    ScrollLock = GLFW_KEY_SCROLL_LOCK,     ///< Scroll Lock.
    NumLock = GLFW_KEY_NUM_LOCK,           ///< Num Lock.
    PrintScreen = GLFW_KEY_PRINT_SCREEN,   ///< Print Screen.
    Pause = GLFW_KEY_PAUSE,                ///< Pause.
    F1 = GLFW_KEY_F1,                      ///< F1.
    F2 = GLFW_KEY_F2,                      ///< F2.
    F3 = GLFW_KEY_F3,                      ///< F3.
    F4 = GLFW_KEY_F4,                      ///< F4.
    F5 = GLFW_KEY_F5,                      ///< F5.
    F6 = GLFW_KEY_F6,                      ///< F6.
    F7 = GLFW_KEY_F7,                      ///< F7.
    F8 = GLFW_KEY_F8,                      ///< F8.
    F9 = GLFW_KEY_F9,                      ///< F9.
    F10 = GLFW_KEY_F10,                    ///< F10.
    F11 = GLFW_KEY_F11,                    ///< F11.
    F12 = GLFW_KEY_F12,                    ///< F12.
    F13 = GLFW_KEY_F13,                    ///< F13.
    F14 = GLFW_KEY_F14,                    ///< F14.
    F15 = GLFW_KEY_F15,                    ///< F15.
    F16 = GLFW_KEY_F16,                    ///< F16.
    F17 = GLFW_KEY_F17,                    ///< F17.
    F18 = GLFW_KEY_F18,                    ///< F18.
    F19 = GLFW_KEY_F19,                    ///< F19.
    F20 = GLFW_KEY_F20,                    ///< F20.
    F21 = GLFW_KEY_F21,                    ///< F21.
    F22 = GLFW_KEY_F22,                    ///< F22.
    F23 = GLFW_KEY_F23,                    ///< F23.
    F24 = GLFW_KEY_F24,                    ///< F24.
    F25 = GLFW_KEY_F25,                    ///< F25.
    Keypad0 = GLFW_KEY_KP_0,               ///< Keypad "0".
    Keypad1 = GLFW_KEY_KP_1,               ///< Keypad "1".
    Keypad2 = GLFW_KEY_KP_2,               ///< Keypad "2".
    Keypad3 = GLFW_KEY_KP_3,               ///< Keypad "3".
    Keypad4 = GLFW_KEY_KP_4,               ///< Keypad "4".
    Keypad5 = GLFW_KEY_KP_5,               ///< Keypad "5".
    Keypad6 = GLFW_KEY_KP_6,               ///< Keypad "6".
    Keypad7 = GLFW_KEY_KP_7,               ///< Keypad "7".
    Keypad8 = GLFW_KEY_KP_8,               ///< Keypad "8".
    Keypad9 = GLFW_KEY_KP_9,               ///< Keypad "9".
    KeypadDecimal = GLFW_KEY_KP_DECIMAL,   ///< Keypad ".".
    KeypadDivide = GLFW_KEY_KP_DIVIDE,     ///< Keypad "/".
    KeypadMultiply = GLFW_KEY_KP_MULTIPLY, ///< Keypad "*".
    KeypadSubtract = GLFW_KEY_KP_SUBTRACT, ///< Keypad "-".
    KeypadAdd = GLFW_KEY_KP_ADD,           ///< Keypad "+".
    KeypadEnter = GLFW_KEY_KP_ENTER,       ///< Keypad "Enter".
    KeypadEqual = GLFW_KEY_KP_EQUAL,       ///< Keypad "Equal".
    LeftShift = GLFW_KEY_LEFT_SHIFT,       ///< Left shift.
    LeftControl = GLFW_KEY_LEFT_CONTROL,   ///< Left control.
    LeftAlt = GLFW_KEY_LEFT_ALT,           ///< Left alt.
    LeftSuper = GLFW_KEY_LEFT_SUPER,       ///< Left super.
    RightShift = GLFW_KEY_RIGHT_SHIFT,     ///< Right shift.
    RightControl = GLFW_KEY_RIGHT_CONTROL, ///< Right control.
    RightAlt = GLFW_KEY_RIGHT_ALT,         ///< Right alt.
    RightSuper = GLFW_KEY_RIGHT_SUPER,     ///< Right super.
    Menu = GLFW_KEY_MENU,                  ///< Menu.
    Last = GLFW_KEY_LAST
};

} // namespace Event

#endif // MODELVIEWER_EVENT_KEYBOARDCODE_HPP_
