#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Multimedia/InputEnum.h>

namespace SDX
{
/** キーボードの状態を表すクラス.*/
/**	\include InputSample.h*/
class Keyboard
{
private:
	Keyboard(const Keyboard &key){};
	Keyboard& operator =(const Keyboard &key) = delete;
public:
	Keyboard(){};
	bool press[256];

	Key Back;
	Key Tab;
	Key Return;
	Key LShift;
	Key RShift;
	Key LControl;
	Key RControl;
	Key Escape;
	Key Space;
	Key PageUp;
	Key PageDown;
	Key End;
	Key Home;
	Key Left;
	Key Up;
	Key Right;
	Key Down;
	Key Insert;
	Key Delete;

	Key Minus;
	Key Yen;
	Key PrevTrack;
	Key Period;
	Key Slash;
	Key LAlt;
	Key RAlt;
	Key Scroll;
	Key Semicolon;
	Key Colon;
	Key LBracket;
	Key RBracket;
	Key At;
	Key Backslash;
	Key Comma;
	Key Capslock;
	Key Pause;

	Key Numpad0;
	Key Numpad1;
	Key Numpad2;
	Key Numpad3;
	Key Numpad4;
	Key Numpad5;
	Key Numpad6;
	Key Numpad7;
	Key Numpad8;
	Key Numpad9;
	Key Multiply;
	Key Add;
	Key Subtract;
	Key Decimal;
	Key Divide;
	Key NUMPADEnter;

	Key F1;
	Key F2;
	Key F3;
	Key F4;
	Key F5;
	Key F6;
	Key F7;
	Key F8;
	Key F9;
	Key F10;
	Key F11;
	Key F12;

	Key A;
	Key B;
	Key C;
	Key D;
	Key E;
	Key F;
	Key G;
	Key H;
	Key I;
	Key J;
	Key K;
	Key L;
	Key M;
	Key N;
	Key O;
	Key P;
	Key Q;
	Key R;
	Key S;
	Key T;
	Key U;
	Key V;
	Key W;
	Key X;
	Key Y;
	Key Z;
	Key _0;
	Key _1;
	Key _2;
	Key _3;
	Key _4;
	Key _5;
	Key _6;
	Key _7;
	Key _8;
	Key _9;
		
	/** 状態のリセット.*/
	void Reset()
	{
		Back.Reset();
		Tab.Reset();
		Return.Reset();
		LShift.Reset();
		RShift.Reset();
		LControl.Reset();
		RControl.Reset();
		Escape.Reset();
		Space.Reset();
		PageUp.Reset();
		PageDown.Reset();
		End.Reset();
		Home.Reset();
		Left.Reset();
		Up.Reset();
		Right.Reset();
		Down.Reset();
		Insert.Reset();
		Delete.Reset();

		Minus.Reset();
		Yen.Reset();
		PrevTrack.Reset();
		Period.Reset();
		Slash.Reset();
		LAlt.Reset();
		RAlt.Reset();
		Scroll.Reset();
		Semicolon.Reset();
		Colon.Reset();
		LBracket.Reset();
		RBracket.Reset();
		At.Reset();
		Backslash.Reset();
		Comma.Reset();
		Capslock.Reset();
		Pause.Reset();

		Numpad0.Reset();
		Numpad1.Reset();
		Numpad2.Reset();
		Numpad3.Reset();
		Numpad4.Reset();
		Numpad5.Reset();
		Numpad6.Reset();
		Numpad7.Reset();
		Numpad8.Reset();
		Numpad9.Reset();
		Multiply.Reset();
		Add.Reset();
		Subtract.Reset();
		Decimal.Reset();
		Divide.Reset();
		NUMPADEnter.Reset();

		F1.Reset();
		F2.Reset();
		F3.Reset();
		F4.Reset();
		F5.Reset();
		F6.Reset();
		F7.Reset();
		F8.Reset();
		F9.Reset();
		F10.Reset();
		F11.Reset();
		F12.Reset();

		A.Reset();
		B.Reset();
		C.Reset();
		D.Reset();
		E.Reset();
		F.Reset();
		G.Reset();
		H.Reset();
		I.Reset();
		J.Reset();
		K.Reset();
		L.Reset();
		M.Reset();
		N.Reset();
		O.Reset();
		P.Reset();
		Q.Reset();
		R.Reset();
		S.Reset();
		T.Reset();
		U.Reset();
		V.Reset();
		W.Reset();
		X.Reset();
		Y.Reset();
		Z.Reset();
		_0.Reset();
		_1.Reset();
		_2.Reset();
		_3.Reset();
		_4.Reset();
		_5.Reset();
		_6.Reset();
		_7.Reset();
		_8.Reset();
		_9.Reset();
	}
		
	/** 状態の更新.*/
	void Update()
	{
		char Buf[256];
		DxLib::GetHitKeyStateAll( Buf );

		Back.Update( Buf[ (int)KeyCode::Back ] );
		Tab.Update( Buf[ (int)KeyCode::Tab ] );
		Return.Update( Buf[ (int)KeyCode::Return ] );
		LShift.Update( Buf[ (int)KeyCode::LShift ] );
		RShift.Update( Buf[ (int)KeyCode::RShift ] );
		LControl.Update( Buf[ (int)KeyCode::LControl ] );
		RControl.Update( Buf[ (int)KeyCode::RControl ] );
		Escape.Update( Buf[ (int)KeyCode::Escape ] );
		Space.Update( Buf[ (int)KeyCode::Space ] );
		PageUp.Update( Buf[ (int)KeyCode::PageUp ] );
		PageDown.Update( Buf[ (int)KeyCode::PageDown ] );
		End.Update( Buf[ (int)KeyCode::End ] );
		Home.Update( Buf[ (int)KeyCode::Home ] );
		Left.Update( Buf[ (int)KeyCode::Left ] );
		Up.Update( Buf[ (int)KeyCode::Up ] );
		Right.Update( Buf[ (int)KeyCode::Right ] );
		Down.Update( Buf[ (int)KeyCode::Down ] );
		Insert.Update( Buf[ (int)KeyCode::Insert ] );
		Delete.Update( Buf[ (int)KeyCode::Delete ] );

		Minus.Update( Buf[ (int)KeyCode::Minus ] );
		Yen.Update( Buf[ (int)KeyCode::Yen ] );
		PrevTrack.Update( Buf[ (int)KeyCode::PrevTrack ] );
		Period.Update( Buf[ (int)KeyCode::Period ] );
		Slash.Update( Buf[ (int)KeyCode::Slash ] );
		LAlt.Update( Buf[ (int)KeyCode::LAlt ] );
		RAlt.Update( Buf[ (int)KeyCode::RAlt ] );
		Scroll.Update( Buf[ (int)KeyCode::Scroll ] );
		Semicolon.Update( Buf[ (int)KeyCode::Semicolon ] );
		Colon.Update( Buf[ (int)KeyCode::Colon ] );
		LBracket.Update( Buf[ (int)KeyCode::LBracket ] );
		RBracket.Update( Buf[ (int)KeyCode::RBracket ] );
		At.Update( Buf[ (int)KeyCode::At ] );
		Backslash.Update( Buf[ (int)KeyCode::Backslash ] );
		Comma.Update( Buf[ (int)KeyCode::Comma ] );
		Capslock.Update( Buf[ (int)KeyCode::Capslock ] );
		Pause.Update( Buf[ (int)KeyCode::Pause ] );

		Numpad0.Update( Buf[ (int)KeyCode::Numpad0 ] );
		Numpad1.Update( Buf[ (int)KeyCode::Numpad1 ] );
		Numpad2.Update( Buf[ (int)KeyCode::Numpad2 ] );
		Numpad3.Update( Buf[ (int)KeyCode::Numpad3 ] );
		Numpad4.Update( Buf[ (int)KeyCode::Numpad4 ] );
		Numpad5.Update( Buf[ (int)KeyCode::Numpad5 ] );
		Numpad6.Update( Buf[ (int)KeyCode::Numpad6 ] );
		Numpad7.Update( Buf[ (int)KeyCode::Numpad7 ] );
		Numpad8.Update( Buf[ (int)KeyCode::Numpad8 ] );
		Numpad9.Update( Buf[ (int)KeyCode::Numpad9 ] );
		Multiply.Update( Buf[ (int)KeyCode::Multiply ] );
		Add.Update( Buf[ (int)KeyCode::Add ] );
		Subtract.Update( Buf[ (int)KeyCode::Subtract ] );
		Decimal.Update( Buf[ (int)KeyCode::Decimal ] );
		Divide.Update( Buf[ (int)KeyCode::Divide ] );
		NUMPADEnter.Update( Buf[ (int)KeyCode::NUMPADEnter ] );

		F1.Update( Buf[ (int)KeyCode::F1 ] );
		F2.Update( Buf[ (int)KeyCode::F2 ] );
		F3.Update( Buf[ (int)KeyCode::F3 ] );
		F4.Update( Buf[ (int)KeyCode::F4 ] );
		F5.Update( Buf[ (int)KeyCode::F5 ] );
		F6.Update( Buf[ (int)KeyCode::F6 ] );
		F7.Update( Buf[ (int)KeyCode::F7 ] );
		F8.Update( Buf[ (int)KeyCode::F8 ] );
		F9.Update( Buf[ (int)KeyCode::F9 ] );
		F10.Update( Buf[ (int)KeyCode::F10 ] );
		F11.Update( Buf[ (int)KeyCode::F11 ] );
		F12.Update( Buf[ (int)KeyCode::F12 ] );

		A.Update( Buf[ (int)KeyCode::A ] );
		B.Update( Buf[ (int)KeyCode::B ] );
		C.Update( Buf[ (int)KeyCode::C ] );
		D.Update( Buf[ (int)KeyCode::D ] );
		E.Update( Buf[ (int)KeyCode::E ] );
		F.Update( Buf[ (int)KeyCode::F ] );
		G.Update( Buf[ (int)KeyCode::G ] );
		H.Update( Buf[ (int)KeyCode::H ] );
		I.Update( Buf[ (int)KeyCode::I ] );
		J.Update( Buf[ (int)KeyCode::J ] );
		K.Update( Buf[ (int)KeyCode::K ] );
		L.Update( Buf[ (int)KeyCode::L ] );
		M.Update( Buf[ (int)KeyCode::M ] );
		N.Update( Buf[ (int)KeyCode::N ] );
		O.Update( Buf[ (int)KeyCode::O ] );
		P.Update( Buf[ (int)KeyCode::P ] );
		Q.Update( Buf[ (int)KeyCode::Q ] );
		R.Update( Buf[ (int)KeyCode::R ] );
		S.Update( Buf[ (int)KeyCode::S ] );
		T.Update( Buf[ (int)KeyCode::T ] );
		U.Update( Buf[ (int)KeyCode::U ] );
		V.Update( Buf[ (int)KeyCode::V ] );
		W.Update( Buf[ (int)KeyCode::W ] );
		X.Update( Buf[ (int)KeyCode::X ] );
		Y.Update( Buf[ (int)KeyCode::Y ] );
		Z.Update( Buf[ (int)KeyCode::Z ] );
		_0.Update( Buf[ (int)KeyCode::_0 ] );
		_1.Update( Buf[ (int)KeyCode::_1 ] );
		_2.Update( Buf[ (int)KeyCode::_2 ] );
		_3.Update( Buf[ (int)KeyCode::_3 ] );
		_4.Update( Buf[ (int)KeyCode::_4 ] );
		_5.Update( Buf[ (int)KeyCode::_5 ] );
		_6.Update( Buf[ (int)KeyCode::_6 ] );
		_7.Update( Buf[ (int)KeyCode::_7 ] );
		_8.Update( Buf[ (int)KeyCode::_8 ] );
		_9.Update( Buf[ (int)KeyCode::_9 ] );
	}
	
	/** いずれかのキーが押されているか取得.*/
	static bool HoldAnyKey()
	{
		return !DxLib::CheckHitKeyAll();
	}
				
};
}