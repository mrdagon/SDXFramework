//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Keyboard.h>
#include <Multimedia/Mouse.h>
#include <Multimedia/Joypad.h>
#include <Multimedia/Touch.h>
#include <Multimedia/Window.h>

namespace SDX
{
/** キーやマウスによる入力をまとめて管理するクラス.*/
/**    \include InputSample.h*/
class Input
{
private:
    Input(){}
    ~Input();
    static int handle;

public:

    static Joypad pad;
    static Mouse mouse;
    static Keyboard key;
    static Touch touch[10];
    static Gesture gesture;

    /** 状態をリセット.*/
    static void Reset()
    {
        pad.Reset();
        mouse.Reset();
        key.Reset();
        for (auto && it : touch) it.Reset();
        gesture.Reset();
    }
    
    /** 状態を更新.*/
    static void Update()
    {
        SDL_JoystickUpdate();
        pad.Update();
        mouse.Update();
        key.Update();
        for (auto && it : touch) it.Update();
        gesture.Update();
    }

    /** 入力の状態を更新[SDL].*/
    static void GetState(SDL_Event &event)
    {
        bool isPush = true;

        switch (event.type)
        {
            case SDL_KEYUP:
                isPush = false;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_BACKSPACE: key.press[(int)KeyCode::Back] = isPush; break;
                    case SDLK_TAB: key.press[(int)KeyCode::Tab] = isPush; break;
                    case SDLK_RETURN: key.press[(int)KeyCode::Return] = isPush; break;
                    case SDLK_LSHIFT: key.press[(int)KeyCode::LShift] = isPush; break;
                    case SDLK_RSHIFT: key.press[(int)KeyCode::RShift] = isPush; break;
                    case SDLK_LCTRL: key.press[(int)KeyCode::LControl] = isPush; break;
                    case SDLK_RCTRL: key.press[(int)KeyCode::RControl] = isPush; break;
                    case SDLK_ESCAPE: key.press[(int)KeyCode::Escape] = isPush; break;
                    case SDLK_SPACE: key.press[(int)KeyCode::Space] = isPush; break;
                    case SDLK_PAGEUP: key.press[(int)KeyCode::PageUp] = isPush; break;
                    case SDLK_PAGEDOWN: key.press[(int)KeyCode::PageDown] = isPush; break;
                    case SDLK_END: key.press[(int)KeyCode::End] = isPush; break;
                    case SDLK_HOME: key.press[(int)KeyCode::Home] = isPush; break;
                    case SDLK_LEFT:
                        key.press[(int)KeyCode::Left] = isPush;
                        pad.press[(int)PadCode::Left] = isPush;
                        break;
                    case SDLK_UP: 
                        key.press[(int)KeyCode::Up] = isPush;
                        pad.press[(int)PadCode::Up] = isPush;
                    break;
                    case SDLK_RIGHT:
                        key.press[(int)KeyCode::Right] = isPush;
                        pad.press[(int)PadCode::Right] = isPush;
                        break;
                    case SDLK_DOWN:
                        key.press[(int)KeyCode::Down] = isPush;
                        pad.press[(int)PadCode::Down] = isPush;
                        break;
                    case SDLK_INSERT: key.press[(int)KeyCode::Insert] = isPush; break;
                    case SDLK_DELETE: key.press[(int)KeyCode::Delete] = isPush; break;

                    case SDLK_MINUS: key.press[(int)KeyCode::Minus] = isPush; break;
                    //case Yen = SDLK_YEN,
                    //case PrevTrack = SDLK_PREVTRACK,
                    case SDLK_PERIOD: key.press[(int)KeyCode::Period] = isPush; break;
                    case SDLK_SLASH: key.press[(int)KeyCode::Slash] = isPush; break;
                    case SDLK_LALT: key.press[(int)KeyCode::LAlt] = isPush; break;
                    case SDLK_RALT: key.press[(int)KeyCode::RAlt] = isPush; break;
                    case SDLK_SCROLLLOCK: key.press[(int)KeyCode::Scroll] = isPush; break;
                    case SDLK_SEMICOLON: key.press[(int)KeyCode::Semicolon] = isPush; break;
                    case SDLK_COLON: key.press[(int)KeyCode::Colon] = isPush; break;
                    case SDLK_LEFTBRACKET: key.press[(int)KeyCode::LBracket] = isPush; break;
                    case SDLK_RIGHTBRACKET: key.press[(int)KeyCode::RBracket] = isPush; break;
                    case SDLK_AT: key.press[(int)KeyCode::At] = isPush; break;
                    case SDLK_BACKSLASH: key.press[(int)KeyCode::Backslash] = isPush; break;
                    case SDLK_COMMA: key.press[(int)KeyCode::Comma] = isPush; break;
                    case SDLK_CAPSLOCK: key.press[(int)KeyCode::Capslock] = isPush; break;
                    case SDLK_PAUSE: key.press[(int)KeyCode::Pause] = isPush; break;

                    case SDLK_KP_0: key.press[(int)KeyCode::Numpad0] = isPush; break;
                    case SDLK_KP_1: key.press[(int)KeyCode::Numpad1] = isPush; break;
                    case SDLK_KP_2: key.press[(int)KeyCode::Numpad2] = isPush; break;
                    case SDLK_KP_3: key.press[(int)KeyCode::Numpad3] = isPush; break;
                    case SDLK_KP_4: key.press[(int)KeyCode::Numpad4] = isPush; break;
                    case SDLK_KP_5: key.press[(int)KeyCode::Numpad5] = isPush; break;
                    case SDLK_KP_6: key.press[(int)KeyCode::Numpad6] = isPush; break;
                    case SDLK_KP_7: key.press[(int)KeyCode::Numpad7] = isPush; break;
                    case SDLK_KP_8: key.press[(int)KeyCode::Numpad8] = isPush; break;
                    case SDLK_KP_9: key.press[(int)KeyCode::Numpad9] = isPush; break;
                    case SDLK_ASTERISK: key.press[(int)KeyCode::Multiply] = isPush; break;
                    case SDLK_KP_PLUS: key.press[(int)KeyCode::Add] = isPush; break;
                    case SDLK_KP_MINUS: key.press[(int)KeyCode::Subtract] = isPush; break;
                    case SDLK_KP_PERIOD: key.press[(int)KeyCode::Decimal] = isPush; break;
                    case SDLK_KP_DIVIDE: key.press[(int)KeyCode::Divide] = isPush; break;
                    case SDLK_KP_ENTER: key.press[(int)KeyCode::NUMPADEnter] = isPush; break;

                    case SDLK_F1: key.press[(int)KeyCode::F1] = isPush; break;
                    case SDLK_F2: key.press[(int)KeyCode::F2] = isPush; break;
                    case SDLK_F3: key.press[(int)KeyCode::F3] = isPush; break;
                    case SDLK_F4: key.press[(int)KeyCode::F4] = isPush; break;
                    case SDLK_F5: key.press[(int)KeyCode::F5] = isPush; break;
                    case SDLK_F6: key.press[(int)KeyCode::F6] = isPush; break;
                    case SDLK_F7: key.press[(int)KeyCode::F7] = isPush; break;
                    case SDLK_F8: key.press[(int)KeyCode::F8] = isPush; break;
                    case SDLK_F9: key.press[(int)KeyCode::F9] = isPush; break;
                    case SDLK_F10: key.press[(int)KeyCode::F10] = isPush; break;
                    case SDLK_F11: key.press[(int)KeyCode::F11] = isPush; break;
                    case SDLK_F12: key.press[(int)KeyCode::F12] = isPush; break;

                    case SDLK_a:
                        key.press[(int)KeyCode::A] = isPush;
                        pad.press[(int)PadCode::Button5] = isPush;
                        break;
                    case SDLK_b: key.press[(int)KeyCode::B] = isPush; break;
                    case SDLK_c:
                        key.press[(int)KeyCode::C] = isPush;
                        pad.press[(int)PadCode::Button3] = isPush;
                        break;
                    case SDLK_d: 
                        key.press[(int)KeyCode::D] = isPush;
                        pad.press[(int)PadCode::Button7] = isPush;
                        break;
                    case SDLK_e: key.press[(int)KeyCode::E] = isPush; break;
                    case SDLK_f:
                        key.press[(int)KeyCode::F] = isPush;
                        pad.press[(int)PadCode::Button8] = isPush;
                        break;
                    case SDLK_g: key.press[(int)KeyCode::G] = isPush; break;
                    case SDLK_h: key.press[(int)KeyCode::H] = isPush; break;
                    case SDLK_i: key.press[(int)KeyCode::I] = isPush; break;
                    case SDLK_j: key.press[(int)KeyCode::J] = isPush; break;
                    case SDLK_k: key.press[(int)KeyCode::K] = isPush; break;
                    case SDLK_l: key.press[(int)KeyCode::L] = isPush; break;
                    case SDLK_m: key.press[(int)KeyCode::M] = isPush; break;
                    case SDLK_n: key.press[(int)KeyCode::N] = isPush; break;
                    case SDLK_o: key.press[(int)KeyCode::O] = isPush; break;
                    case SDLK_p: key.press[(int)KeyCode::P] = isPush; break;
                    case SDLK_q: key.press[(int)KeyCode::Q] = isPush; break;
                    case SDLK_r: key.press[(int)KeyCode::R] = isPush; break;
                    case SDLK_s: 
                        key.press[(int)KeyCode::S] = isPush;
                        pad.press[(int)PadCode::Button6] = isPush;
                        break;
                    case SDLK_t: key.press[(int)KeyCode::T] = isPush; break;
                    case SDLK_u: key.press[(int)KeyCode::U] = isPush; break;
                    case SDLK_v:
                        key.press[(int)KeyCode::V] = isPush;
                        pad.press[(int)PadCode::Button4] = isPush;
                        break;
                    case SDLK_w: key.press[(int)KeyCode::W] = isPush; break;
                    case SDLK_x:
                        key.press[(int)KeyCode::X] = isPush;
                        pad.press[(int)PadCode::Button2] = isPush;
                        break;
                    case SDLK_y: key.press[(int)KeyCode::Y] = isPush; break;
                    case SDLK_z:
                        key.press[(int)KeyCode::Z] = isPush;
                        pad.press[(int)PadCode::Button1] = isPush;
                        break;
                    case SDLK_0: key.press[(int)KeyCode::_0] = isPush; break;
                    case SDLK_1: key.press[(int)KeyCode::_1] = isPush; break;
                    case SDLK_2: key.press[(int)KeyCode::_2] = isPush; break;
                    case SDLK_3: key.press[(int)KeyCode::_3] = isPush; break;
                    case SDLK_4: key.press[(int)KeyCode::_4] = isPush; break;
                    case SDLK_5: key.press[(int)KeyCode::_5] = isPush; break;
                    case SDLK_6: key.press[(int)KeyCode::_6] = isPush; break;
                    case SDLK_7: key.press[(int)KeyCode::_7] = isPush; break;
                    case SDLK_8: key.press[(int)KeyCode::_8] = isPush; break;
                    case SDLK_9: key.press[(int)KeyCode::_9] = isPush; break;
                }
                break;
            case SDL_JOYAXISMOTION:
                break;
                //左右の動き
                if (event.jaxis.axis == 0)
                {
                    pad.StickX = event.jaxis.value;
                    pad.press[(int)PadCode::Left] = (event.jaxis.value < -0x7000) ;
                    pad.press[(int)PadCode::Right] = (event.jaxis.value >  0x7000);
                }
                //上下の動き
                if (event.jaxis.axis == 1)
                {
                    pad.StickY = event.jaxis.value;
                    if (event.jaxis.value < -0x7000) pad.press[(int)PadCode::Up] = true;
                    if (event.jaxis.value >  0x7000) pad.press[(int)PadCode::Down] = true;
                }
                break;
            case SDL_JOYHATMOTION:
                pad.press[(int)PadCode::Up] = false;
                pad.press[(int)PadCode::Left] = false;
                pad.press[(int)PadCode::Down] = false;
                pad.press[(int)PadCode::Right] = false;

                switch (event.jhat.value)
                {
                    case SDL_HAT_UP       :pad.press[(int)PadCode::Up] = true;break;
                    case SDL_HAT_LEFT     :pad.press[(int)PadCode::Left] = true; break;
                    case SDL_HAT_DOWN     :pad.press[(int)PadCode::Down] = true; break;
                    case SDL_HAT_RIGHT    :pad.press[(int)PadCode::Right] = true;break;
                    case SDL_HAT_LEFTUP   :pad.press[(int)PadCode::Up] = true;pad.press[(int)PadCode::Left] = true; break;
                    case SDL_HAT_RIGHTUP  :pad.press[(int)PadCode::Up] = true;pad.press[(int)PadCode::Right] = true;break;
                    case SDL_HAT_RIGHTDOWN:pad.press[(int)PadCode::Down] = true;pad.press[(int)PadCode::Right] = true;break;
                    case SDL_HAT_LEFTDOWN :pad.press[(int)PadCode::Down] = true;pad.press[(int)PadCode::Left] = true; break;
                }
                break;
            case SDL_JOYBUTTONUP:
                isPush = false;
            case SDL_JOYBUTTONDOWN:
                pad.press[event.jbutton.button] = isPush;
                break;
            case SDL_MOUSEMOTION:
                mouse.xBuffer = event.motion.x;
                mouse.yBuffer = event.motion.y;
                break;
            case SDL_MOUSEBUTTONUP:
                isPush = false;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button)
                {
                    case SDL_BUTTON_LEFT:mouse.press[(int)MouseCode::Left] = isPush; break;
                    case SDL_BUTTON_RIGHT:mouse.press[(int)MouseCode::Right] = isPush; break;
                    case SDL_BUTTON_MIDDLE:mouse.press[(int)MouseCode::Middle] = isPush; break;
                    case SDL_BUTTON_X1:mouse.press[(int)MouseCode::_4] = isPush; break;
                    case SDL_BUTTON_X2:mouse.press[(int)MouseCode::_5] = isPush; break;
                }
                break;
            case SDL_FINGERUP:
                isPush = false;
            case SDL_FINGERDOWN:
                if (event.tfinger.fingerId >= 10) break;
                touch[(int)event.tfinger.fingerId].press = isPush;
                if(event.tfinger.fingerId == 0) mouse.press[(int)MouseCode::Left] = isPush;
                if(event.tfinger.fingerId == 1) mouse.press[(int)MouseCode::Right] = isPush;
            case SDL_FINGERMOTION:
                if (event.tfinger.fingerId >= 10) break;
                touch[(int)event.tfinger.fingerId].Position( event.tfinger.x,event.tfinger.y);
                mouse.xBuffer = (int)touch[(int)event.tfinger.fingerId].xBuffer;
                mouse.yBuffer = (int)touch[(int)event.tfinger.fingerId].yBuffer;
                break;
            case SDL_MULTIGESTURE:
                gesture.press = true;
                gesture.fingerCount = event.mgesture.numFingers;
                gesture.pinche = event.mgesture.dDist;
                gesture.rotate = event.mgesture.dTheta;
                gesture.Position( event.mgesture.x , event.mgesture.y);
                break;
        }
    }

};

}