#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Input.h>

namespace SDX
{
/** 一時停止処理する関数群.*/
/**	\include WaitSample.h*/
class Wait
{
private:
	Wait();
	~Wait();
public:
	/** 指定ミリ秒実行を停止.*/
	static void Timer(int 停止ミリ秒)
	{
		DxLib::WaitTimer(停止ミリ秒);
	}
	
	/** 垂直同期信号を指定回数待つ[DXLIB].*/
	static bool VSync(int 信号回数)
	{
		return !DxLib::WaitVSync(信号回数);	
	}
	
	/** キーを入力を待つ.*/
	static void PushKey()
	{
		DxLib::WaitKey();
	}
};
}
