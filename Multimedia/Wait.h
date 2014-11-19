//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Input.h>

namespace SDX
{
	/*! 一時停止処理する関数群.*/
	/*!    \include WaitSample.h*/
	class Wait
	{
	private:
		Wait();
		~Wait();
	public:
		/*! 指定ミリ秒実行を停止.*/
		static void Timer(int 停止ミリ秒)
		{
			SDL_Delay(停止ミリ秒);
		}

		/*! 垂直同期信号を指定回数待つ[未実装].*/
		static bool VSync(int 信号回数)
		{
			return false;
		}

		/*! キーを入力を待つ.*/
		static void PushKey()
		{
			while (!Keyboard::HoldAnyKey() && System::ProcessMessage()){}
		}
	};
}
