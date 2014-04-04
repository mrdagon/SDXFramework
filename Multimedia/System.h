﻿#pragma once//☀SDL
#include <Multimedia/SDX.h>
#include <Multimedia/Window.h>
#include <Multimedia/Screen.h>
#include <Multimedia/Input.h>
#include <Multimedia/Font.h>
#include <Multimedia/Music.h>

namespace SDX
{
/** ライブラリの初期化やシステム的な処理を行う関数群.*/
/**    \include SystemSample.h*/
class System
{
private:
    System();
    ~System();
    static bool isEnd;
public:

    /** ライブラリの初期化.*/
    /**    初期化に失敗した場合、ソフトを強制的に終了する。\n
        一部の設定関数は初期化前に呼び出す必要がある。*/
    static void Initialise( const char* ウィンドウ名 , int 幅 , int 高さ )
    {
        if (SDL_Init( SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO ) < 0) 
        {
            fprintf(stderr, "SDLの初期化に失敗しました：%s\n", SDL_GetError());
            exit(1);
            return;
        }

        setlocale(LC_CTYPE, "jpn");//文字コードを日本語に

        int flag = 0;
        if (Window::Single().isFullScreen)
        {
            flag = SDL_WINDOW_FULLSCREEN;
        }

        Window::Single().width  = 幅;
        Window::Single().height = 高さ;

        Window::Single().handle = SDL_CreateWindow( ウィンドウ名 ,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 幅 , 高さ , flag);
        Screen::SetRenderer(SDL_CreateRenderer(Window::Single().handle, -1, SDL_RENDERER_PRESENTVSYNC));

        #ifdef TABLET
            int dpiX;
            int dpiY;
            SDL_GetWindowSize( Window::Single().handle, &dpiX, &dpiY);
            Window::Single().aspect = (double)dpiX / dpiY;
            SDL_RenderSetLogicalSize( Screen::GetHandle() , 幅, 高さ);
        #endif

        TTF_Init();

        //デフォルトフォントの設定
        Drawing::SetDefaultFont( SystemFont::Gothic , 16 );

        SDL_InitSubSystem( SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVERYTHING );

        SDL_JoystickEventState(SDL_ENABLE);

        if( SDL_NumJoysticks() > 0 )
        {
            Input::pad.Open();
        }

        //音声関連の初期化
        Mix_Init(MIX_INIT_MP3);
        Mix_OpenAudio(44100, AUDIO_S16, 2, 1024);
        Mix_AllocateChannels(16);

        isEnd = false;
    }

    /** ライブラリの終了処理.*/
    /** この関数を使用した後は速やかにプログラムを終了させなければならない。*/
    static bool End()
    {
        TTF_Quit();
        Mix_CloseAudio();
        Mix_Quit();
        SDL_Quit();
        isEnd = true;
        return true;
    }

    /** 各種更新処理をまとめて行う.*/
    static bool Update(bool 描画更新フラグ = true)
    {
        if (描画更新フラグ)
        {
            Screen::Flip();
            Screen::Clear();
        }
        bool result = System::ProcessMessage();
        Input::Update();
        return result;
    }

    /** OSのメッセージ処理を行う.*/
    /**    目安として1/60秒に一回程度、この関数を呼び出す必要があり。
        falseを返した場合、速やかにプログラムを終了させなければならない。*/    
    static bool ProcessMessage()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            /* QUIT イベントが発生したら終了する*/
            if( event.type == SDL_WINDOWEVENT)
            {
#ifdef TABLET
switch (event.window.event)
    {
        case SDL_WINDOWEVENT_MINIMIZED:
        Mix_VolumeMusic( 0 );
            break;
        case SDL_WINDOWEVENT_RESTORED:
        Mix_VolumeMusic( Music::nowVolume );
            break;
        }
#endif
            }else if (event.type == SDL_QUIT)
            {
                isEnd = true;
            }
            else
            {
                Input::GetState(event);
            }
        }

        return !isEnd;
    }

    /** ログ出力の有無を設定[DXLIB].*/
    /**    DXライブラリのデバッグ情報ログ・ファイル『App.log』を出力設定する。
        この関数は、Initialise前に呼び出す必要がある。*/
    static bool SetOutputLog( bool 出力フラグ)
    {
        return false;
    }

    /** ビデオRAM使用を設定[DXLIB].*/
    /**    この関数は、Initialise前に呼び出す必要がある。*/
    static bool SetMemToVram( bool VRAM使用フラグ)
    {
        return false;
    }

    /** 非アクティブ時も処理を続行するか設定[DXLIB].*/
    /** デフォルトで非アクティブ時は処理を停止する。*/
    static bool SetAlwaysRun( bool 常時処理フラグ )
    {
        return false;
    }
};
}
