//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Sound.h>
#include <chrono>

namespace SDX
{
	/** BGM用音声を表すクラス.*/
	/** \include Music.h*/
	/**@todo 中途再生周りのテスト*/
	class Music
	{
		friend class System;
	private:
		static Music *active;//!< 現在再生中のMusic
		Mix_Music* handle = nullptr;//!<音楽リソースのハンドル
		std::string fileName;//!<音声ファイル名
		int volume;//!<再生音量

		int fadeinTime = 0;//!< フェードイン時間
		bool isStop = false;//!< 途中終了フラグ

		std::chrono::system_clock::time_point startTime;//再生開始時刻
		double restartPosition = 0;//!< 再生再開位置
	public:
		Music(){};
		~Music()
		{
		}

		/** 音声ファイルを登録.*/
		Music(const char *ファイル名, double 音量 = 1.0)
		{
			Music::Load(ファイル名, 音量);
		}

		/** 音声ファイルを登録.*/
		/** 音量は 0～1.0で指定、ファイルはメモリには読み込まない。*/
		bool Load(const char *ファイル名, double 音量 = 1.0)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名, 音量); });
				return true;
			}

			if (handle != nullptr){ return false; }

			this->fileName = ファイル名;
			handle = Mix_LoadMUS(ファイル名);
			volume = int(音量 * 255);

			return true;
		}

		/** 音声ファイルを解放.*/
		bool Destroy()
		{
			if (handle == nullptr){ return false; }

			Mix_FreeMusic(handle);
			return true;
		}

		/** 音声ファイルを再生.*/
		/** Musicファイルは複数同時に再生する事は出来ない。\n*/
		/**	現在再生中の音声は停止する。*/
		bool Play( bool ループ再生フラグ = true )
		{
			if (handle == nullptr){ return false; }

			int isLoop = ( 1 - ループ再生フラグ * 2);

			isStop = false;

			if (fadeinTime <= 0)
			{
				Mix_PlayMusic(handle, isLoop );
			}
			else			
			{
				Mix_FadeInMusic(handle, isLoop , fadeinTime);
			}

			startTime = std::chrono::system_clock::now();
			Mix_VolumeMusic(volume / 2);
			active = this;

			return true;
		}

		/** 前回停止した位置から再生.*/
		/** Musicファイルは複数同時に再生する事は出来ない。\n*/
		/**	現在再生中の音声は停止する。*/
		bool Restart(bool ループ再生フラグ = true)
		{
			if (handle == nullptr){ return false; }

			isStop = false;

			int isLoop = ( 1 - ループ再生フラグ * 2);

			if (fadeinTime <= 0)
			{
				Mix_PlayMusic(handle, isLoop);
				if (restartPosition > 0)
				{
					Mix_SetMusicPosition(restartPosition);
				}
			}
			else
			{
				if (restartPosition > 0)
				{
					Mix_FadeInMusicPos(handle, isLoop, fadeinTime, restartPosition);
				}
				else
				{
					Mix_FadeInMusic(handle, isLoop, fadeinTime);
				}
			}

			startTime = std::chrono::system_clock::now();
			Mix_VolumeMusic(volume / 2);
			active = this;

			Mix_HookMusicFinished(Finished);

			return true;
		}

		/**0～1.0で音量を設定.*/
		void SetVolume(double 音量)
		{
			volume = int(音量 * 255);
		}

		/** 再生時のフェードイン時間を設定[ミリ秒].*/
		/** 指定ミリ秒かけて徐々に音量を上げる*/
		void SetFadeinTime(int フェードイン時間)
		{
			fadeinTime = フェードイン時間;
		}

		/** 再生中か確認.*/
		/** いずれかのMusicが再生中ならtureを返す*/
		static bool Check()
		{
			return !Mix_PlayingMusic();
		}

		/** 再生中のMusicを停止.*/
		/** フェードアウト時間[mm秒]が1以上の場合、徐々に音量を下げて停止する*/
		static bool Stop(int フェードアウト時間 = 0)
		{
			active->isStop = true;

			if (フェードアウト時間 <= 0)
			{
				Mix_HaltMusic();
			}
			else
			{
				Mix_FadeOutMusic(フェードアウト時間);

			}

			return true;
		}

		/** 再生中の音量を変更.*/
		/** いずれかのMusicが再生中なら音量を変更*/
		static void ChangeVolume(double 音量)
		{
			Mix_VolumeMusic(int(音量 * 255));
		}

		/** 停止時のコールバック専用関数.*/
		/** 普通に呼び出してはいけない*/
		static void Finished()
		{
			//途中で終了した場合
			auto diff = std::chrono::system_clock::now() - active->startTime;
			active->restartPosition += (double)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / 1000;
			
			//フェードイン終了の次に再生するBGMがある場合の処理

		}
	};
}