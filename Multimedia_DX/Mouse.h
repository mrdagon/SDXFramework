#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Framework/Shape.h>
#include <Multimedia/InputEnum.h>
#include <Multimedia/Window.h>

namespace SDX
{
/** マウスの状態を表すクラス.*/
/**	\include InputSample.h*/
class Mouse
{
private:
	Mouse(const Mouse &mouse){};
	Mouse operator =(const Mouse &mouse) = delete;
public:
	Mouse()
	{
		Reset();
	}

	int x;
	int y;

	int moveX;
	int moveY;

	int Whell;

	bool press[8];

	Key Left;
	Key Right;
	Key Middle;

	Key Button4;
	Key Button5;
	Key Button6;
	Key Button7;
	Key Button8;

	int maxButton;
	
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
        static int X = 0;
        static int Y = 0;

		DxLib::GetMousePoint(&x,&y);
		int N = DxLib::GetMouseInput();

		Left.Update( N & (int)MouseCode::Left );
		Right.Update( N & (int)MouseCode::Right );
		Middle.Update( N & (int)MouseCode::Middle );

		Button4.Update( N & (int)MouseCode::_4 );
		Button5.Update( N & (int)MouseCode::_5 );
		Button6.Update( N & (int)MouseCode::_6 );
		Button7.Update( N & (int)MouseCode::_7 );
		Button8.Update( N & (int)MouseCode::_8 );

		moveX = x - X;
		moveY = y - Y;

		X = x;
		Y = y;
	}

	/** カーソルの表示設定[DXLIB].*/
	bool SetVisible(bool 表示フラグ)
	{
		return !SetMouseDispFlag(表示フラグ);
	}
	
	/** カーソル位置を移動.*/
	bool SetPoint( int 移動先X , int 移動先Y )
	{
		return !SetMousePoint(移動先X, 移動先Y);
	}
};
}