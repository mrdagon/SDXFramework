#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Keyboard.h>
#include <Multimedia/Mouse.h>
#include <Multimedia/Joypad.h>
#include <Multimedia/Touch.h>
#include <Multimedia/Window.h>

namespace SDX
{
/** キーやマウスによる入力をまとめて管理するクラス.*/
/**	\include InputSample.h*/
class Input
{
private:
	Input(){}
	~Input();
	static int handle;

public:

	static Joypad pad;
	static Mouse mouse;
	static Keyboard key;
    static Touch touch[10];
    static Gesture gesture;

	/** 状態をリセット.*/
	static void Reset()
	{
		Input::pad.Reset();
		Input::mouse.Reset();
		Input::key.Reset();
	}
	
	/** 状態を更新.*/
	static void Update()
	{
        //SDL_JoystickUpdate();
		Input::pad.Update();
		Input::mouse.Update();
		Input::key.Update();
	}

	/** 処理を停止してキーボードから文字を入力[DXLIB].*/
	static bool Text(int X座標,int Y座標,int 最大文字数, char *初期文字列 ,bool Escキャンセルフラグ ,bool １バイト文字限定フラグ = false)
	{
		if (１バイト文字限定フラグ)
		{
			return (DxLib::KeyInputString(X座標, Y座標, 最大文字数, 初期文字列, Escキャンセルフラグ) == 1);
		}
		else{
			return (DxLib::KeyInputSingleCharString(X座標, Y座標, 最大文字数, 初期文字列, Escキャンセルフラグ) == 1);
		}
	}
	
	/** キーボードから数字を入力[DXLIB].*/
	/** 数値入力ウィンドウを表示する\n
		入力中は全ての処理が停止する\n
		入力した値を返す、失敗した場合、範囲外の数値を返す*/
	static int Number(int X座標, int Y座標, int 最小値, int 最大値, int Escキャンセルフラグ)
	{
		return DxLib::KeyInputNumber(X座標, Y座標, 最大値, 最小値, Escキャンセルフラグ);
	}
	
	/** テキスト入力モードの開始[DXLIB].*/
	/** 他の処理を止めずに文字入力を行う*/
	static bool StartTextMode( int 最大文字数 , bool ESCキャンセル可能フラグ , bool 半角文字限定フラグ , bool 数値入力限定フラグ )
	{
		if (handle != NULL_HANDLE)
		{
			handle = DxLib::MakeKeyInput(最大文字数, ESCキャンセル可能フラグ, 半角文字限定フラグ, 数値入力限定フラグ);
		}
		DxLib::SetActiveKeyInput( handle );
	}
	
	/** テキスト入力モードの確認[DXLIB].*/
	static int CheckText()
	{
		return DxLib::CheckKeyInput( handle );
	}
	
	/** テキストの描画[DXLIB].*/
	static bool DrawText(int X座標 , int Y座標 )
	{
		DxLib::DrawKeyInputString( X座標 , Y座標 , handle );
	}
	
	/** テキストの設定[DXLIB].*/
	static bool SetText( const char* 文字列 )
	{
		DxLib::SetKeyInputString(文字列, handle);
	}
	/** テキストの設定[DXLIB].*/
	static bool SetText( int 数値 )
	{
		DxLib::SetKeyInputNumber(数値, handle);
	}

	/** テキストの取得[DXLIB].*/
	static bool GetText( char* 出力バッファ )
	{
		return !GetKeyInputString(出力バッファ, handle);
	}


	/** キーボード入力時の表示色設定[DXLIB].*/
	static int SetKeyColor(
		int 入力文字色 ,
		int IME非使用時カーソル色 ,
		int IME使用時文字色 ,
		int IME使用時カーソル色 ,
		int 変換時下線色 ,
		int IME使用時変換候補色 ,
		int 入力モード名色 ,
		int 入力文字縁色 ,
		int 変換候補縁色 ,
		int 入力モード名縁色 ,
		int 変換候補ウィンドウ縁色 ,
		int 変換候補ウィンドウ色 ) 
	{
		return DxLib::SetKeyInputStringColor
			(
			入力文字色,
			IME非使用時カーソル色,
			IME使用時文字色,
			IME使用時カーソル色,
			変換時下線色,
			IME使用時変換候補色,
			入力モード名色,
			入力文字縁色,
			変換候補縁色,
			入力モード名縁色,
			変換候補ウィンドウ縁色,
			変換候補ウィンドウ色
			);
	}

};

}