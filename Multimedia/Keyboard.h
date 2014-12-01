//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Multimedia/InputEnum.h>

namespace SDX
{
	/** キーボードの状態を表すクラス.*/
	/** \include Input.h*/
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
			Back.Update(press[(int)KeyCode::Back]);
			Tab.Update(press[(int)KeyCode::Tab]);
			Return.Update(press[(int)KeyCode::Return]);
			LShift.Update(press[(int)KeyCode::LShift]);
			RShift.Update(press[(int)KeyCode::RShift]);
			LControl.Update(press[(int)KeyCode::LControl]);
			RControl.Update(press[(int)KeyCode::RControl]);
			Escape.Update(press[(int)KeyCode::Escape]);
			Space.Update(press[(int)KeyCode::Space]);
			PageUp.Update(press[(int)KeyCode::PageUp]);
			PageDown.Update(press[(int)KeyCode::PageDown]);
			End.Update(press[(int)KeyCode::End]);
			Home.Update(press[(int)KeyCode::Home]);
			Left.Update(press[(int)KeyCode::Left]);
			Up.Update(press[(int)KeyCode::Up]);
			Right.Update(press[(int)KeyCode::Right]);
			Down.Update(press[(int)KeyCode::Down]);
			Insert.Update(press[(int)KeyCode::Insert]);
			Delete.Update(press[(int)KeyCode::Delete]);

			Minus.Update(press[(int)KeyCode::Minus]);
			Yen.Update(press[(int)KeyCode::Yen]);
			PrevTrack.Update(press[(int)KeyCode::PrevTrack]);
			Period.Update(press[(int)KeyCode::Period]);
			Slash.Update(press[(int)KeyCode::Slash]);
			LAlt.Update(press[(int)KeyCode::LAlt]);
			RAlt.Update(press[(int)KeyCode::RAlt]);
			Scroll.Update(press[(int)KeyCode::Scroll]);
			Semicolon.Update(press[(int)KeyCode::Semicolon]);
			Colon.Update(press[(int)KeyCode::Colon]);
			LBracket.Update(press[(int)KeyCode::LBracket]);
			RBracket.Update(press[(int)KeyCode::RBracket]);
			At.Update(press[(int)KeyCode::At]);
			Backslash.Update(press[(int)KeyCode::Backslash]);
			Comma.Update(press[(int)KeyCode::Comma]);
			Capslock.Update(press[(int)KeyCode::Capslock]);
			Pause.Update(press[(int)KeyCode::Pause]);

			Numpad0.Update(press[(int)KeyCode::Numpad0]);
			Numpad1.Update(press[(int)KeyCode::Numpad1]);
			Numpad2.Update(press[(int)KeyCode::Numpad2]);
			Numpad3.Update(press[(int)KeyCode::Numpad3]);
			Numpad4.Update(press[(int)KeyCode::Numpad4]);
			Numpad5.Update(press[(int)KeyCode::Numpad5]);
			Numpad6.Update(press[(int)KeyCode::Numpad6]);
			Numpad7.Update(press[(int)KeyCode::Numpad7]);
			Numpad8.Update(press[(int)KeyCode::Numpad8]);
			Numpad9.Update(press[(int)KeyCode::Numpad9]);
			Multiply.Update(press[(int)KeyCode::Multiply]);
			Add.Update(press[(int)KeyCode::Add]);
			Subtract.Update(press[(int)KeyCode::Subtract]);
			Decimal.Update(press[(int)KeyCode::Decimal]);
			Divide.Update(press[(int)KeyCode::Divide]);
			NUMPADEnter.Update(press[(int)KeyCode::NUMPADEnter]);

			F1.Update(press[(int)KeyCode::F1]);
			F2.Update(press[(int)KeyCode::F2]);
			F3.Update(press[(int)KeyCode::F3]);
			F4.Update(press[(int)KeyCode::F4]);
			F5.Update(press[(int)KeyCode::F5]);
			F6.Update(press[(int)KeyCode::F6]);
			F7.Update(press[(int)KeyCode::F7]);
			F8.Update(press[(int)KeyCode::F8]);
			F9.Update(press[(int)KeyCode::F9]);
			F10.Update(press[(int)KeyCode::F10]);
			F11.Update(press[(int)KeyCode::F11]);
			F12.Update(press[(int)KeyCode::F12]);

			A.Update(press[(int)KeyCode::A]);
			B.Update(press[(int)KeyCode::B]);
			C.Update(press[(int)KeyCode::C]);
			D.Update(press[(int)KeyCode::D]);
			E.Update(press[(int)KeyCode::E]);
			F.Update(press[(int)KeyCode::F]);
			G.Update(press[(int)KeyCode::G]);
			H.Update(press[(int)KeyCode::H]);
			I.Update(press[(int)KeyCode::I]);
			J.Update(press[(int)KeyCode::J]);
			K.Update(press[(int)KeyCode::K]);
			L.Update(press[(int)KeyCode::L]);
			M.Update(press[(int)KeyCode::M]);
			N.Update(press[(int)KeyCode::N]);
			O.Update(press[(int)KeyCode::O]);
			P.Update(press[(int)KeyCode::P]);
			Q.Update(press[(int)KeyCode::Q]);
			R.Update(press[(int)KeyCode::R]);
			S.Update(press[(int)KeyCode::S]);
			T.Update(press[(int)KeyCode::T]);
			U.Update(press[(int)KeyCode::U]);
			V.Update(press[(int)KeyCode::V]);
			W.Update(press[(int)KeyCode::W]);
			X.Update(press[(int)KeyCode::X]);
			Y.Update(press[(int)KeyCode::Y]);
			Z.Update(press[(int)KeyCode::Z]);
			_0.Update(press[(int)KeyCode::_0]);
			_1.Update(press[(int)KeyCode::_1]);
			_2.Update(press[(int)KeyCode::_2]);
			_3.Update(press[(int)KeyCode::_3]);
			_4.Update(press[(int)KeyCode::_4]);
			_5.Update(press[(int)KeyCode::_5]);
			_6.Update(press[(int)KeyCode::_6]);
			_7.Update(press[(int)KeyCode::_7]);
			_8.Update(press[(int)KeyCode::_8]);
			_9.Update(press[(int)KeyCode::_9]);
		}

		/** いずれかのキーが押されているか取得.*/
		static bool HoldAnyKey()
		{
			const Uint8 *press = SDL_GetKeyboardState(NULL);

			return(
				press[(int)KeyCode::Back] ||
				press[(int)KeyCode::Tab] ||
				press[(int)KeyCode::Return] ||
				press[(int)KeyCode::LShift] ||
				press[(int)KeyCode::RShift] ||
				press[(int)KeyCode::LControl] ||
				press[(int)KeyCode::RControl] ||
				press[(int)KeyCode::Escape] ||
				press[(int)KeyCode::Space] ||
				press[(int)KeyCode::PageUp] ||
				press[(int)KeyCode::PageDown] ||
				press[(int)KeyCode::End] ||
				press[(int)KeyCode::Home] ||
				press[(int)KeyCode::Left] ||
				press[(int)KeyCode::Up] ||
				press[(int)KeyCode::Right] ||
				press[(int)KeyCode::Down] ||
				press[(int)KeyCode::Insert] ||
				press[(int)KeyCode::Delete] ||

				press[(int)KeyCode::Minus] ||
				press[(int)KeyCode::Yen] ||
				press[(int)KeyCode::PrevTrack] ||
				press[(int)KeyCode::Period] ||
				press[(int)KeyCode::Slash] ||
				press[(int)KeyCode::LAlt] ||
				press[(int)KeyCode::RAlt] ||
				press[(int)KeyCode::Scroll] ||
				press[(int)KeyCode::Semicolon] ||
				press[(int)KeyCode::Colon] ||
				press[(int)KeyCode::LBracket] ||
				press[(int)KeyCode::RBracket] ||
				press[(int)KeyCode::At] ||
				press[(int)KeyCode::Backslash] ||
				press[(int)KeyCode::Comma] ||
				press[(int)KeyCode::Capslock] ||
				press[(int)KeyCode::Pause] ||

				press[(int)KeyCode::Numpad0] ||
				press[(int)KeyCode::Numpad1] ||
				press[(int)KeyCode::Numpad2] ||
				press[(int)KeyCode::Numpad3] ||
				press[(int)KeyCode::Numpad4] ||
				press[(int)KeyCode::Numpad5] ||
				press[(int)KeyCode::Numpad6] ||
				press[(int)KeyCode::Numpad7] ||
				press[(int)KeyCode::Numpad8] ||
				press[(int)KeyCode::Numpad9] ||
				press[(int)KeyCode::Multiply] ||
				press[(int)KeyCode::Add] ||
				press[(int)KeyCode::Subtract] ||
				press[(int)KeyCode::Decimal] ||
				press[(int)KeyCode::Divide] ||
				press[(int)KeyCode::NUMPADEnter] ||

				press[(int)KeyCode::F1] ||
				press[(int)KeyCode::F2] ||
				press[(int)KeyCode::F3] ||
				press[(int)KeyCode::F4] ||
				press[(int)KeyCode::F5] ||
				press[(int)KeyCode::F6] ||
				press[(int)KeyCode::F7] ||
				press[(int)KeyCode::F8] ||
				press[(int)KeyCode::F9] ||
				press[(int)KeyCode::F10] ||
				press[(int)KeyCode::F11] ||
				press[(int)KeyCode::F12] ||

				press[(int)KeyCode::A] ||
				press[(int)KeyCode::B] ||
				press[(int)KeyCode::C] ||
				press[(int)KeyCode::D] ||
				press[(int)KeyCode::E] ||
				press[(int)KeyCode::F] ||
				press[(int)KeyCode::G] ||
				press[(int)KeyCode::H] ||
				press[(int)KeyCode::I] ||
				press[(int)KeyCode::J] ||
				press[(int)KeyCode::K] ||
				press[(int)KeyCode::L] ||
				press[(int)KeyCode::M] ||
				press[(int)KeyCode::N] ||
				press[(int)KeyCode::O] ||
				press[(int)KeyCode::P] ||
				press[(int)KeyCode::Q] ||
				press[(int)KeyCode::R] ||
				press[(int)KeyCode::S] ||
				press[(int)KeyCode::T] ||
				press[(int)KeyCode::U] ||
				press[(int)KeyCode::V] ||
				press[(int)KeyCode::W] ||
				press[(int)KeyCode::X] ||
				press[(int)KeyCode::Y] ||
				press[(int)KeyCode::Z] ||
				press[(int)KeyCode::_0] ||
				press[(int)KeyCode::_1] ||
				press[(int)KeyCode::_2] ||
				press[(int)KeyCode::_3] ||
				press[(int)KeyCode::_4] ||
				press[(int)KeyCode::_5] ||
				press[(int)KeyCode::_6] ||
				press[(int)KeyCode::_7] ||
				press[(int)KeyCode::_8] ||
				press[(int)KeyCode::_9]);
			return false;
		}
	};
}