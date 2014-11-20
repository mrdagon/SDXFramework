//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>

namespace SDX
{
	/** 2つ目以降のウィンドウを表すクラス.*/
	/** デスクトップ版のみ使用可能.*/
	/**    \include WindowSample.h*/
	class SubWindow
	{
		friend class System;
		friend class Mouse;
		friend class Gesture;
		friend class Touch;

		int width;
		int height;
		double aspect;
	};


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
		WindowHandle handle = nullptr;
	public:

		static Window& Single()
		{
			static Window single;
			return single;
		}

		static WindowHandle GetHandle()
		{
			return Single().handle;
		}

		static void Create( const char* ウィンドウ名, int 幅, int 高さ , bool フルスクリーンフラグ = false)
		{
			Single().width = 幅;
			Single().height = 高さ;
			Single().isFullScreen = フルスクリーンフラグ;

			int flag = 0;
			if (Window::Single().isFullScreen)
			{
				flag = SDL_WINDOW_FULLSCREEN;
			}

			Window::Single().handle = SDL_CreateWindow(ウィンドウ名, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 幅, 高さ, flag);

		}

		/** スクリーンモードを設定する.*/
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

		/** ウィンドウタイトルを設定.*/
		static bool SetTitle(const char *タイトル名)
		{
			SDL_SetWindowTitle(Single().handle, タイトル名);
			return true;
		}

		/** ウィンドウサイズの設定.*/
		static void SetSize(int 幅, int 高さ)
		{
			Window::Single().width = 幅;
			Window::Single().height = 高さ;

			SDL_RenderSetLogicalSize(Screen::GetHandle(), 幅, 高さ);
			SDL_SetWindowSize(Single().handle, 幅, 高さ);
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