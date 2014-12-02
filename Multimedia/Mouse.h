//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Framework/Shape.h>
#include <Multimedia/Window.h>
#include <Utility/EnumArray.h>

namespace SDX
{
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
		_8,

		COUNT,
	};

	/** マウスの状態を表すクラス.*/
	/** \include Input.h*/
	class Mouse
	{
		friend class Input;
	private:
		int xBuffer;//!<
		int yBuffer;//!<

		EnumArray<bool, MouseCode> press;

		Mouse(const Mouse &mouse){};
		Mouse operator =(const Mouse &mouse) = delete;
	public:
		Mouse()
		{
			Reset();
		}

		int x;//!<
		int y;//!<

		int moveX;//!<
		int moveY;//!<

		int Whell;//!<

		Key Left;
		Key Right;
		Key Middle;

		Key Button4;
		Key Button5;
		Key Button6;
		Key Button7;
		Key Button8;

		/** 状態のリセット.*/
		void Reset()
		{
			x = 0;
			y = 0;
			moveX = 0;
			moveY = 0;
			Left.Reset();
			Right.Reset();
			Middle.Reset();
			Button4.Reset();
			Button5.Reset();
			Button6.Reset();
			Button7.Reset();
			Button8.Reset();
			Whell = 0;
		}

		/** 状態の更新.*/
		void Update()
		{
			Left.Update(press[MouseCode::Left]);
			Right.Update(press[MouseCode::Right]);
			Middle.Update(press[MouseCode::Middle]);

			Button4.Update(press[MouseCode::_4]);
			Button5.Update(press[MouseCode::_5]);
			Button6.Update(press[MouseCode::_6]);
			Button7.Update(press[MouseCode::_7]);
			Button8.Update(press[MouseCode::_8]);

			moveX = xBuffer - x;
			moveY = yBuffer - y;

			x = xBuffer;
			y = yBuffer;

			Whell = 0;
		}

		/** カーソルの表示設定.*/ 
		bool SetVisible(bool 表示フラグ)
		{
			if (表示フラグ)
			{
				SDL_ShowCursor( 1 );
			}
			else
			{
				SDL_ShowCursor( 0 );
			}

			return true;
		}

		/** カーソル位置を移動.*/
		bool SetPoint(int 移動先X, int 移動先Y)
		{
			SDL_WarpMouseInWindow(Window::activeWindow->handle, x, y);
			return true;
		}

		/** MouseCodeでアクセス.*/
		/** MouseCode::COUNTや範囲外の場合Leftを返す*/
		Key& operator[](MouseCode index)
		{
			switch (index)
			{
			case MouseCode::Left:return Left;
			case MouseCode::Right:return Right;
			case MouseCode::Middle:return Middle;
			case MouseCode::_4:return Button4;
			case MouseCode::_5:return Button5;
			case MouseCode::_6:return Button6;
			case MouseCode::_7:return Button7;
			case MouseCode::_8:return Button8;
			default: return Left;
			}
		}
	};
}