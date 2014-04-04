﻿#pragma once//☀SDL
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>

namespace SDX
{
/** ウィンドウを表すクラス.*/
/**    \include WindowSample.h*/
class Window
{
    friend class System;
    friend class Mouse;
    friend class Gesture;
    friend class Touch;
private:
    bool isFullScreen = false;
    int width;
    int height;
    double aspect;

    Window(){}
    WindowHandle handle = 0;

public:

    static Window& Single()
    {
        static Window single;
        return single;        
    }

    /** スクリーンモードを設定する.*/
    /** DXLIBでは色々な設定が初期化される上、アスペクトが無視されます*/
    static bool SetFullScreen(bool フルスクリーンフラグ)
    {
        Single().isFullScreen = フルスクリーンフラグ;

        if (Single().isFullScreen)
        {
            SDL_RenderSetLogicalSize(Screen::GetHandle() , GetWidth() , GetHeight() );
            SDL_SetWindowFullscreen(Single().handle, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        else
        {
            SDL_SetWindowFullscreen(Single().handle, 0);
            SDL_SetWindowSize(Single().handle, GetWidth(), GetHeight());
        }
        return false;
    }
    
    /** ウィンドウタイトルを設定.*/
    static bool SetTitle(const char *タイトル名)
    {
        SDL_SetWindowTitle( Single().handle , タイトル名 );
        return true;
    }
    
    /** アイコンIDの設定[DXLIB].*/
    static bool SetIconID(int アイコンID)
    {    
        return false;
    }
    
    /** ウィンドウの拡大縮小可否設定[DXLIB].*/
    static bool SetSizeChangeEnable(bool 拡大縮小可能フラグ)
    {
        return false;
    }
    
    /** ウィンドウサイズの設定.*/
    static bool SetSize(int 幅,int 高さ )
    {
        Window::Single().width  = 幅;
        Window::Single().height = 高さ;

        SDL_RenderSetLogicalSize(Screen::GetHandle(), 幅, 高さ);
        SDL_SetWindowSize( Single().handle , 幅, 高さ);
        return true;
    }
    
    /** ウィンドウ幅の取得.*/
    static int GetWidth()
    {
        return Single().width;
    }

    /** ウィンドウ高さの取得.*/
    static int GetHeight()
    {
        return Single().height;
    }
};
}