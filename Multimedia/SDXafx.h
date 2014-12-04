//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
//多重定義の関係でプリコンパイル済みヘッダーにのみインクルードするヘッダー
#include <Framework/ShapeHit.h>
#include <Framework/ShapeDraw.h>

namespace SDX
{
	const Color Color::Black(0x00, 0x00, 0x00);
	const Color Color::Dilver(0xc0, 0xc0, 0xc0);
	const Color Color::Gray(0x80, 0x80, 0x80);
	const Color Color::White(0xff, 0xff, 0xff);
	const Color Color::Maroon(0x80, 0x00, 0x00);
	const Color Color::Red(0xff, 0x00, 0x00);
	const Color Color::Purple(0x80, 0x00, 0x80);
	const Color Color::Fuchsia(0xff, 0x00, 0xff);
	const Color Color::Green(0x00, 0x80, 0x00);
	const Color Color::Lime(0x00, 0xff, 0x00);
	const Color Color::Olive(0x80, 0x80, 0x00);
	const Color Color::Yellow(0xff, 0xff, 0x00);
	const Color Color::Navy(0x00, 0x00, 0x80);
	const Color Color::Blue(0x00, 0x00, 0xff);
	const Color Color::Teal(0x00, 0x80, 0x80);
	const Color Color::Aqua(0x00, 0xff, 0xff);

	Camera* Camera::active;

	Joypad Input::pad;
	Mouse Input::mouse;
	Keyboard Input::key;
	Touch Input::touch[10];
	Gesture Input::gesture;

	Renderer &Renderer::mainRenderer = SubWindow::mainWindow.renderer;
	SubWindow SubWindow::mainWindow;

	std::list<SubWindow*> SubWindow::windowS;

	Renderer* Screen::activeRenderer;
	SubWindow* Window::activeWindow;

	Music* Music::active = nullptr;

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