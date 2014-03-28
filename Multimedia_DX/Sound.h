#pragma once//☀DXLIB
#include<Multimedia/SDX.h>

namespace SDX
{
/** 音声の再生方式.*/
enum class PlayType
{
	Normal = DX_PLAYTYPE_NORMAL,//!< 再生中、他の処理を止める
	Back = DX_PLAYTYPE_BACK,//!< 再生中、他の処理を止めない
	Loop = DX_PLAYTYPE_LOOP,//!< 他の処理を止めず、最初から
};

/** 効果音用音声を表すクラス.*/
/**	\include SoundSample.h*/
class Sound
{
private:
	SoundHandle handle;
public:

	Sound(){}

	/** 音声ファイルをメモリに読み込む.*/
	Sound(const char *ファイル名 , double 音量 = 1.0)
	{
		Load(ファイル名);
	}
		
	/** 音声ファイルをメモリに読み込む.*/
	int Load(const char *ファイル名 , double 音量 = 1.0)
	{
		if(this->handle != NULL_HANDLE ) DxLib::DeleteSoundMem(handle);
		DxLib::ChangeVolumeSoundMem(int(音量 * 255), this->handle);
		return this->handle = DxLib::LoadSoundMem(ファイル名);
	}

	/** 音声ファイルをメモリから開放.*/
	bool Release()
	{
		return !DxLib::DeleteSoundMem(handle);
	}

	/** ハンドルを取得.*/
	SoundHandle GetHandle() const
	{
		return this->handle;
	}
		
	/** 音声ファイルを再生.*/
	bool Play(PlayType 再生方法 = PlayType::Back , bool 先頭から再生 = true) const
	{
		return !DxLib::PlaySoundMem(this->handle, (int)再生方法, 先頭から再生);
	}
		
	/** 再生中か判定[DXLIB].*/
	bool Check() const
	{
		return !DxLib::CheckSoundMem(this->handle);
	}
		
	/** 再生を停止[DXLIB].*/
	bool Stop()
	{
		return !DxLib::StopSoundMem(this->handle);
	}
		
	/** 音声パンを設定[DXLIB].*/
	bool SetPan(int 音声パン)
	{
		return !DxLib::SetPanSoundMem(音声パン, this->handle);
	}
		
	/** 音量を0～1.0の範囲で設定.*/
	bool SetVolume(double 音量)
	{
		return !DxLib::ChangeVolumeSoundMem(int(音量 * 255), this->handle);
	}
		
	/** 再生周波数を設定[DXLIB].*/
	/** 単位はHzで範囲は100～100,000*/
	bool SetFrequency(int 再生周波数)
	{
		return !DxLib::SetFrequencySoundMem(再生周波数, this->handle);
	}
		
	/** ミリ秒単位でループ位置を設定[DXLIB].*/
	bool SetLoopPos(int ループ位置)
	{
        return !DxLib::SetLoopPosSoundMem(ループ位置, this->handle);
	}
		
	/** サンプリング周波数でループ位置を設定[DXLIB].*/
	/** 周期が44.1KHzの場合、44,100を渡すと1秒の位置でループする*/
	bool SetLoopSamplePos(int ループ周波数)
	{
		return !DxLib::SetLoopSamplePosSoundMem(ループ周波数, this->handle);
	}
};
}