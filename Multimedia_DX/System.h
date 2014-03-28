#pragma once//☀DXLIB
#include<Multimedia/SDX.h>
#include<Multimedia/Window.h>
#include<Multimedia/Screen.h>
#include<Multimedia/Input.h>
#include<Multimedia/Font.h>

namespace SDX
{
/** ライブラリの初期化やシステム的な処理を行う関数群.*/
/**	\include SystemSample.h*/
class System
{
private:
	System();
	~System();
    static bool isEnd;
public:
	/** ライブラリの初期化.*/
	/**	初期化に失敗した場合、ソフトを強制的に終了する。\n
		一部の設定関数は初期化前に呼び出す必要がある。*/
	static void Initialise( const char* ウィンドウ名 , int 幅 , int 高さ )
	{
		Window::SetTitle(const_cast<char*>(ウィンドウ名));
		DxLib::SetGraphMode(幅, 高さ, 32);
	#ifndef DEBUG
		SetUseDirectInputFlag(FALSE);//DebugビルドではDirectInputが重いので停止。
	#endif

		if( !Window::Single().isFullScreen )
		{
			DxLib::ChangeWindowMode( true );
		}

		if( DxLib::DxLib_Init() == -1 ) exit(1);

		DxLib::SetDrawScreen( DX_SCREEN_BACK ); 
	}

	/** ライブラリの終了処理.*/
	/** この関数を使用した後は速やかにプログラムを終了させなければならない。*/
	static bool End()
	{
		return !DxLib::DxLib_End();
	}

	/** 各種更新処理をまとめて行う.*/
	static bool Update(bool 描画更新フラグ = true)
	{
		if (描画更新フラグ)
		{
			Screen::Flip();
			Screen::Clear();
		}
		bool result = System::ProcessMessage();
		Input::Update();
		return result;
	}

	/** OSのメッセージ処理を行う.*/
	/**	目安として1/60秒に一回程度、この関数を呼び出す必要があり。
		falseを返した場合、速やかにプログラムを終了させなければならない。*/	
	static bool ProcessMessage()
	{
		return !DxLib::ProcessMessage();
	}

	/** ログ出力の有無を設定[DXLIB].*/
	/**	DXライブラリのデバッグ情報ログ・ファイル『App.log』を出力設定する。
		この関数は、Initialise前に呼び出す必要がある。*/
	static bool SetOutputLog( bool 出力フラグ)
	{
		return !DxLib::SetOutApplicationLogValidFlag(出力フラグ);
	}

	/** ビデオRAM使用を設定[DXLIB].*/
	/**	この関数は、Initialise前に呼び出す必要がある。*/
	static bool SetMemToVram( bool VRAM使用フラグ)
	{
		return !SetScreenMemToVramFlag(VRAM使用フラグ);
	}

	/** 非アクティブ時も処理を続行するか設定[DXLIB].*/
	/** デフォルトで非アクティブ時は処理を停止する。*/
	static bool SetAlwaysRun( bool 常時処理フラグ )
	{
		return !DxLib::SetAlwaysRunFlag(常時処理フラグ);
	}
};
}

