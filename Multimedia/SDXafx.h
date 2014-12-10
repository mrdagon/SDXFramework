﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
//多重定義の関係でプリコンパイル済みヘッダーにのみインクルードするヘッダー
#include <Framework/ShapeHit.h>
#include <Framework/ShapeDraw.h>

namespace SDX
{
	const Color Color::Black = { 0, 0, 0 };//!< 黒 [RGB]0,0,0
	const Color Color::Silver = { 192, 192, 192 };//!< 銀 [R]192,192,192
	const Color Color::Gray(0x80, 0x80, 0x80);//!< 灰 [RGB]128,128,128
	const Color Color::White(0xff, 0xff, 0xff);//!< 白 [RGB]255,255,255
	const Color Color::Maroon(0x80, 0x00, 0x00);//!< 栗 [RGB]128,0,0
	const Color Color::Red(0xff, 0x00, 0x00);//!< 赤 [RGB]255,0,0
	const Color Color::Purple(0x80, 0x00, 0x80);//!< 紫 [RGB]128,0,128
	const Color Color::Fuchsia(0xff, 0x00, 0xff);//!< 赤紫 [RGB]255,0,255
	const Color Color::Green(0x00, 0x80, 0x00);//!< 濃緑 [RGB]0,128,0
	const Color Color::Lime(0x00, 0xff, 0x00);//!< 明緑 [RGB]0,255,0
	const Color Color::Olive(0x80, 0x80, 0x00);//!< 暗黄 [RGB]128,128,0
	const Color Color::Yellow(0xff, 0xff, 0x00);//!< 黄 [[RGB]255,255,0
	const Color Color::Navy(0x00, 0x00, 0x80);//!< 濃青 [RGB]0,0,128
	const Color Color::Blue(0x00, 0x00, 0xff);//!< 青 [RGB]0,0,255
	const Color Color::Teal(0x00, 0x80, 0x80);//!< 青緑 [RGB]0,128,128
	const Color Color::Aqua(0x00, 0xff, 0xff);//!< 水 [RGB]0,255,255

	Camera* Camera::active = nullptr;

	Joypad Input::pad;
	Mouse Input::mouse;
	Keyboard Input::key;
	Touch Input::touch[10];
	Gesture Input::gesture;

	Renderer &Renderer::mainRenderer = SubWindow::mainWindow.renderer;
	SubWindow SubWindow::mainWindow;

	std::list<SubWindow*> SubWindow::windowS;

	Renderer* Screen::activeRenderer = nullptr;
	SubWindow* Window::activeWindow = nullptr;

	Music* Music::active = nullptr;
	Music* Music::next = nullptr;
	bool Music::nextLoop;//!< 次に再生するMusicがループするか
	bool Music::nextRestart;//!< 次に再生するMusicがリスタートするか

	bool Loading::isLoading = false;
	int Loading::loadingCount = 0;
	int Loading::succesCount = 0;
	std::mutex Loading::mtx;
	std::vector<std::function<void(void)>> Loading::funcS;

	bool Renderer::SetTarget(Image *描画対象)
	{
		bool a;

		if (描画対象 == nullptr)
		{
			a = (SDL_SetRenderTarget(handle, nullptr) == 0);
		}
		else
		{
			a = (SDL_SetRenderTarget(handle, 描画対象->GetHandle()) == 0);
		}

		if ( a )
		{
			target = 描画対象;
		}

		return a;
	}

}