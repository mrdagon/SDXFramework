//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Image.h>
#include <Framework/ImagePack.h>

namespace SDX
{
	/** 次コマの移動先.*/
	/** 0以上の場合は、そのコマにジャンプする*/
	enum class NextFrame
	{
		Normal = -10000,//!< 次のコマに進む
		ToFront,//!< コマの進む向きをプラスにしてから進む
		ToBack,//!< コマの進む向きをマイナスにしてから進む
		End,//!< このコマでアニメーションを停止する
	};

	/** アニメの再生方法.*/
	enum class AnimeType
	{
		Normal,//!< 最後まで再生するとまた最初からループ再生
		Reverse,//!< 最後まで再生すると、再生方向を反転
		End//!< 最終フレームで再生を停止
	};

	/** Imageをまとめてコマ送りアニメとして表すクラス.*/
	/**    \include AnimeSample.h */
	class Anime : public ImagePack
	{
	private:
		std::vector<unsigned int> times;//!< コマのフレーム数
		std::vector<int> nexts;//!< 各コマの次フレーム
	public:
		/** Animeの再生情報を管理するクラス.*/
		class Player
		{
		private:
			const Anime* anime;//対応アニメ
			int direct = 1;//進行方向
			int frameNumber = 0;//現在のコマ
			double timer = 0;//経過時間
		public:

			Player(const Anime* 親アニメ) :
				anime(親アニメ)
			{}

			/** カウンタの更新.*/
			bool Update(double 経過フレーム = 1)
			{
				timer += 経過フレーム;

				if (timer > anime->times[frameNumber])
				{
					timer -= anime->times[frameNumber];
					switch (anime->nexts[frameNumber])
					{
					case (int)NextFrame::Normal:
						frameNumber += direct;
						break;
					case (int)NextFrame::ToFront:
						direct = 1;
						frameNumber += direct;
						break;
					case (int)NextFrame::ToBack:
						direct = -1;
						frameNumber += direct;
						break;
					case (int)NextFrame::End:
						return false;
						break;
					default:
						frameNumber = anime->nexts[frameNumber];
						break;
					}

					if ((unsigned int)frameNumber >= anime->images.size()) frameNumber = 0;
					if (frameNumber < 0)    frameNumber = (int)anime->images.size() - 1;
				}

				return true;
			}

			/** 現在のコマ番号を取得.*/
			Image* GetFrame()
			{
				return anime[0][frameNumber];
			}

			/** コマの位置を設定.*/
			void SetFrame(int コマ数)
			{
				this->frameNumber = コマ数;
				timer = 0;
			}
		};

		Anime(){};

		Anime(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦, int 再生フレーム数 = 1) :
			ImagePack(ファイル名, 総コマ数, コマ割り横, コマ割り縦)
		{
			for (unsigned int a = 0; a < times.size(); ++a)
			{
				times.push_back(再生フレーム数);
				nexts.push_back((int)NextFrame::Normal);
			}
		}

		/** 画像ファイルを分割してメモリへ読み込む.*/
		bool Load(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦, int 再生フレーム数 = 1)
		{
			ImagePack::Load(ファイル名, 総コマ数, コマ割り横, コマ割り縦);

			for (int a = 0; a < 総コマ数; ++a)
			{
				times.push_back(再生フレーム数);
				nexts.push_back((int)NextFrame::Normal);
			}

			return true;
		}

		/** 連番ファイルを一括して読み込む.*/
		bool Load(const char* ファイル名, const char *拡張子, int 総コマ数, int 再生フレーム数 = 1)
		{
			for (int a = 0; a < 総コマ数; ++a)
			{
				char fileBuf[8];
				sprintf_s(fileBuf, 8, "%03d.", a);
				std::string fileName = ファイル名;
				fileName += fileBuf;
				fileName += 拡張子;

				this->Add(new Image(fileName.c_str()), 再生フレーム数);
			}

			return true;
		}

		/** 末尾にImageを追加する。.*/
		void Add(Image *追加イメージ, int 再生フレーム数 = 1)
		{
			ImagePack::Add(追加イメージ);
			times.push_back(再生フレーム数);
			nexts.push_back((int)NextFrame::Normal);
		}
		void Add(const char *ファイル名, int 再生フレーム数 = 1)
		{
			Add(new Image(ファイル名), 再生フレーム数);
		}

		/** Imageを開放し初期化する.*/
		void Release() override
		{
			ImagePack::Release();
			times.clear();
			nexts.clear();
		}

		/** 各コマのフレーム数を設定する.*/
		/** 先頭コマのフレーム数を配列で渡す*/
		void SetFrameTime(int フレーム時間[])
		{
			for (unsigned int a = 0; a < times.size(); ++a)
			{
				times[a] = フレーム時間[a];
			}
		}

		/** アニメの再生方法を指定する.*/
		void SetType(AnimeType 再生方法)
		{
			switch (再生方法)
			{
			case AnimeType::Normal:
				nexts[nexts.size() - 1] = (int)NextFrame::Normal;
				break;
			case AnimeType::Reverse:
				nexts[0] = (int)NextFrame::ToFront;
				nexts[nexts.size() - 1] = (int)NextFrame::ToBack;
				break;
			case AnimeType::End:
				nexts[nexts.size() - 1] = (int)NextFrame::End;
				break;
			}
		}

		/** 指定コマの次フレームを設定する.*/
		void SetType(int コマ番号, int 次フレーム)
		{
			nexts[コマ番号] = 次フレーム;
		}
		void SetType(int コマ番号, NextFrame 次フレーム)
		{
			nexts[コマ番号] = (int)次フレーム;
		}

		/** 全コマの合計フレーム時間を返す.*/
		int GetAnimeTime() const
		{
			int totalTime = 0;

			for (auto it : times)
			{
				totalTime += it;
			}

			return totalTime;
		}

		Image* operator[](int index) const
		{
			return images[index];
		}
	};
}