//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>

namespace SDX
{
	/*! ウィンドウを表すクラス.*/
	/*!    \include WindowSample.h*/
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

		/*! スクリーンモードを設定する.*/
		static bool SetFullScreen(bool フルスクリーンフラグ)
		{
			Single().isFullScreen = フルスクリーンフラグ;

			if (Single().isFullScreen)
			{
				SDL_RenderSetLogicalSize(Screen::GetHandle(), GetWidth(), GetHeight());
				SDL_SetWindowFullscreen(Single().handle, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			else
			{
				SDL_SetWindowFullscreen(Single().handle, 0);
				SDL_SetWindowSize(Single().handle, GetWidth(), GetHeight());
			}
			return false;
		}

		/*! ウィンドウタイトルを設定.*/
		static bool SetTitle(const char *タイトル名)
		{
			SDL_SetWindowTitle(Single().handle, タイトル名);
			return true;
		}

		/*! ウィンドウサイズの設定.*/
		static void SetSize(int 幅, int 高さ)
		{
			Window::Single().width = 幅;
			Window::Single().height = 高さ;

			SDL_RenderSetLogicalSize(Screen::GetHandle(), 幅, 高さ);
			SDL_SetWindowSize(Single().handle, 幅, 高さ);
		}

		/*! ウィンドウ幅の取得.*/
		static int GetWidth()
		{
			return Single().width;
		}

		/*! ウィンドウ高さの取得.*/
		static int GetHeight()
		{
			return Single().height;
		}
	};
}