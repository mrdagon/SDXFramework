﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <Multimedia/SDX.h>

namespace SDX
{
	/** リソースの非同期読み込み支援関数.*/
	/** Image,Font,Sound,Music,Movieで有効*/
	/** \include Loading.h*/
	class Loading
	{
		friend class Image;
		friend class ImagePack;
		friend class Font;
		friend class MixFont;
		friend class Sound;
		friend class Music;
		friend class Movie;
	private:
		Loading(void) = default;
		~Loading(void) = default;

		static bool isLoading;
		static int loadingCount;
		static int succesCount;
		static std::mutex mtx;

		static std::vector<std::function<void(void)>> funcS;

		static void AddLoading(std::function<void(void)> &&読み込み関数)
		{
			std::lock_guard<std::mutex> lock(mtx);
			funcS.push_back(読み込み関数);
			++loadingCount;
		}
	public:

		/** 非同期読み込みするResorceを登録開始.*/
		static void Start()
		{
			loadingCount = 0;
			succesCount = 0;
			isLoading = true;
		}

		/** 非同期読み込みするResorceの読込開始.*/
		static void End()
		{
			isLoading = false;

			std::thread
			(
				[&]
				{
					for (auto it : funcS)
					{
						it();
						++succesCount;
					}
					funcS.clear();
				}
			).detach();
		}

		/** 読み込み中と読み込んだリソース数を取得.*/
		static int GetLoadingCount()
		{
			std::lock_guard<std::mutex> lock(mtx);
			return loadingCount;
		}

		/** 読み込んだリソース数を取得.*/
		static int GetSuccesCount()
		{
			std::lock_guard<std::mutex> lock(mtx);
			return succesCount;
		}
	};
}