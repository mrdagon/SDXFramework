//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>
#include <Framework/ImagePack.h>
#include <vector>

namespace SDX
{
	/** tmxファイルのタイルセット情報を読み込むクラス.*/
	/** @todo tsxファイルにカスタムプロパティが使われている場合は想定していない*/
	/** ImagePack型に機能追加で良さそう*/
	class TileSet
	{
	public:
		std::vector<Image*> imageS;

		void LoadTmx(const char* tmxファイル名)
		{
			File file(tmxファイル名, FileMode::Read);
			auto strS = file.GetLineS();

			if (strS[2].find("tile id") == std::string::npos)
			{
				//分割タイル
				int tw = strS[1].find("width=") + 7;//各タイルの大きさ
				int th = strS[1].find("height=") + 8;
				tw = std::atoi(strS[1].substr(tw, strS[1].find("\"", tw) - tw).c_str());
				th = std::atoi(strS[1].substr(th, strS[1].find("\"", th) - th).c_str());

				int source = strS[2].find("source=") + 8;//ファイル名
				int w = strS[2].find("width=") + 7;//全体の大きさ
				int h = strS[2].find("height=") + 8;
				w = std::atoi(strS[2].substr(w, strS[2].find("\"", w) - w).c_str()) / tw;
				h = std::atoi(strS[2].substr(w, strS[2].find("\"", h) - h).c_str()) / th;

				ImagePack ip;
				ip.Load(strS[2].substr(source, strS[2].find("\"", source) - source).c_str(), w*h, w, h);

				for (auto &it : ip)
				{
					imageS.push_back(it);
				}
			}
			else
			{
				//大きさバラバラ
				for (auto &it : strS)
				{
					if (it.find("<image width") != std::string::npos)
					{
						int source = strS[2].find("source=") + 8;//ファイル名
						imageS.push_back(new Image(it.substr(source, it.find("\"", source) - source).c_str()));
					}
				}
			}
		}

		/** オペレータ.*/
		Image* operator[](int index)
		{
			return imageS[index];
		}

		/** オペレータ.*/
		Image* operator[](int index) const
		{
			return imageS[index];
		}

		/** イテレータ用.*/
		auto begin() ->decltype(imageS.begin())
		{
			return imageS.begin();
		}

		/** イテレータ用.*/
		auto end() ->decltype(imageS.end())
		{
			return imageS.end();
		}

		/** イテレータ用.*/
		auto begin() const ->decltype(imageS.begin())
		{
			return imageS.begin();
		}

		/** イテレータ用.*/
		auto end() const ->decltype(imageS.end())
		{
			return imageS.end();
		};
	};
}