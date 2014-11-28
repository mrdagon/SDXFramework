//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
	/** 効果音用音声を表すクラス.*/
	/** \include SoundSample.h*/
	class Sound
	{
	private:
		Mix_Chunk* handle;//!<
		int leftPan = 255;//!<
		int rightPan = 255;//!<

		int angle = 0;
		int distance = -1;
	public:

		Sound(){}

		/** 音声ファイルをメモリに読み込む.*/
		Sound(const char *ファイル名, double 音量 = 1.0)
		{
			Load(ファイル名);
		}

		/** 音声ファイルをメモリに読み込む.*/
		int Load(const char *ファイル名, double 音量 = 1.0)
		{
			handle = Mix_LoadWAV(ファイル名);
			if (!handle){ return false; }

			Mix_VolumeChunk(handle, int(音量 * 128));
			return true;
		}

		/** 音声ファイルをメモリから開放.*/
		bool Release()
		{
			Mix_FreeChunk(handle);
			return true;
		}

		/** ハンドルを取得.*/
		Mix_Chunk* GetHandle() const
		{
			return this->handle;
		}

		/** 音声ファイルを再生.*/
		bool Play() const
		{
			//static int channel = 0;
			//channel = (++channel) % 2;
			Mix_PlayChannel(0, handle, 0);

			if (distance != -1)
			{
				Mix_SetPosition(0, angle, distance);
			}
			else if (leftPan < 255 || rightPan < 255)
			{
				Mix_SetPanning(0, leftPan, rightPan);
			}

			return true;
		}

		/** 音量を0～1.0の範囲で設定.*/
		bool SetVolume(double 音量)
		{
			Mix_VolumeChunk(handle, int(音量 * 128));
			return true;
		}

		/** 音声パンを設定.*/
		/** スピーカー左右の音量を変える、0.0～1.0*/
		void SetPanning(double 左パン, double 右パン)
		{
			leftPan = std::min(int(左パン*255),255);
			rightPan = std::min(int(右パン*255),255);
		}

		/** 3D音声再生効果を付ける.*/
		/** 距離は[近]0～1.0[遠]、角度は[正面]0[左]-PAI/2[右]PAI/2で指定*/
		/** 距離を-1以下にすると無効になる*/
		/** SetPanよりこっちが優先される*/
		void Set3DEffect(double 距離, double 角度 = 0)
		{
			distance = std::min((int)距離*255,255);
			angle = int(角度 * 180 / PAI);//℃に変換
			if (angle < 0)
			{
				angle = 360 -(std::abs(angle) % 360);
			}
		}

	};
}