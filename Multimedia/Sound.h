//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
	/*! 音声の再生方式.*/
	enum class PlayType
	{
		Normal = 0,//!< 再生中、他の処理を止める
		Back = 0,//!< 再生中、他の処理を止めない
		Loop = -1,//!< 他の処理を止めず、繰り返す
	};

	/*! 効果音用音声を表すクラス.*/
	/*!    \include SoundSample.h*/
	class Sound
	{
	private:
		SoundHandle handle;
	public:

		Sound(){}

		/*! 音声ファイルをメモリに読み込む.*/
		Sound(const char *ファイル名, double 音量 = 1.0)
		{
			Load(ファイル名);
		}

		/*! 音声ファイルをメモリに読み込む.*/
		int Load(const char *ファイル名, double 音量 = 1.0)
		{
			handle = Mix_LoadWAV(ファイル名);
			if (!handle) return false;

			Mix_VolumeChunk(handle, int(音量 * 128));
			return true;
		}

		/*! 音声ファイルをメモリから開放.*/
		bool Release()
		{
			Mix_FreeChunk(handle);
			return true;
		}

		/*! ハンドルを取得.*/
		SoundHandle GetHandle() const
		{
			return this->handle;
		}

		/*! 音声ファイルを再生.*/
		bool Play(PlayType 再生方法 = PlayType::Back, bool 先頭から再生 = true) const
		{
			static int channel = 0;
			Mix_PlayChannel(0, handle, (int)再生方法);
			channel = (++channel) % 2;
			return true;
		}

		/*! 再生中か判定[未実装].*/
		bool Check() const
		{
			return false;
		}

		/*! 再生を停止[未実装].*/
		bool Stop()
		{
			return false;
		}

		/*! 音声パンを設定[未実装].*/
		bool SetPan(int 音声パン)
		{
			return false;
		}

		/*! 音量を0～1.0の範囲で設定.*/
		bool SetVolume(double 音量)
		{
			Mix_VolumeChunk(handle, int(音量 * 128));
			return true;
		}

		/*! 再生周波数を設定[未実装].*/
		/*! 単位はHzで範囲は100～100,000*/
		bool SetFrequency(int 再生周波数)
		{
			return false;
		}

		/*! ミリ秒単位でループ位置を設定[未実装].*/
		bool SetLoopPos(int ループ位置)
		{
			return false;
		}

		/*! サンプリング周波数でループ位置を設定[未実装].*/
		/*! 周期が44.1KHzの場合、44,100を渡すと1秒の位置でループする*/
		bool SetLoopSamplePos(int ループ周波数)
		{
			return false;
		}
	};
}