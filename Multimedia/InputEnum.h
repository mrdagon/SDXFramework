//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] GNU Affero General Public License, version 3
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
/** ゲームパッドの種類.*/
enum class PadType
{
    KeyAndPad1,//!< 
    Pad1,//!< 
    Pad2,//!< 
    Pad3,//!< 
    Pad4,//!< 
    KeyBord//!< 
};

/** ゲームパッドコード.*/
enum class PadCode :unsigned int
{
    Button1,
    Button2,
    Button3,
    Button4,
    Button5,
    Button6,
    Button7,
    Button8,
    Button9,
    Button10,
    Button11,
    Button12,
    Button13,
    Button14,
    Button15,
    Button16,
    Button17,
    Button18,
    Button19,
    Button20,
    Button21,
    Button22,
    Button23,
    Button24,
    Button25,
    Button26,
    Button27,
    Button28,
    Down,
    Left,
    Right,
    Up,
};

/** キーボードコード.*/
enum class KeyCode
{
    Back,
    Tab,
    Return,
    LShift,
    RShift,
    LControl,
    RControl,
    Escape,
    Space,
    PageUp,
    PageDown,
    End,
    Home,
    Left,
    Up,
    Right,
    Down,
    Insert,
    Delete,
    Minus,
    Yen,
    PrevTrack,
    Period,
    Slash,
    LAlt,
    RAlt,
    Scroll,
    Semicolon,
    Colon,
    LBracket,
    RBracket,
    At,
    Backslash,
    Comma,
    Capslock,
    Pause,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    Multiply,
    Add,
    Subtract,
    Decimal,
    Divide,
    NUMPADEnter,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9
};

/** マウスボタンコード.*/
enum class MouseCode
{
    Left,
    Right,
    Middle,
    _4,
    _5,
    _6,
    _7,
    _8
};
}