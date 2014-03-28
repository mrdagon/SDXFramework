#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>

namespace SDX
{
/** ウィンドウを表すクラス.*/
/**	\include WindowSample.h*/
class Window
{
	friend class System;
    friend class Mouse;
    friend class Touch;
    friend class Gesture;
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

        DxLib::ChangeWindowMode(!フルスクリーンフラグ);
        Screen::SetBack();
        return true;
	}
	
	/** ウィンドウタイトルを設定.*/
	static bool SetTitle(const char *タイトル名)
	{
		return !DxLib::SetMainWindowText(タイトル名);
	}
	
	/** アイコンIDの設定[DXLIB].*/
	static bool SetIconID(int アイコンID)
	{
		return !DxLib::SetWindowIconID( アイコンID );
	}
	
	/** ウィンドウの拡大縮小可否設定[DXLIB].*/
	static bool SetSizeChangeEnable(bool 拡大縮小可能フラグ)
	{
		return !DxLib::SetWindowSizeChangeEnableFlag(拡大縮小可能フラグ);
	}
	
	/** ウィンドウサイズの設定.*/
	static bool SetSize(int 幅,int 高さ )
	{
        Window::Single().width  = 幅;
        Window::Single().height = 高さ;

		return !DxLib::SetWindowSize(幅, 高さ);
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