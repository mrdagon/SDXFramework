//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>
#include <GUI/GUIData.h>
#include <vector>

namespace SDX
{
	/** Tiledで作成したデータ(.tmx)を変換してGUIDataにする関数.*/
	/**@todo 実装中*/
	/** \include TranceCode.h*/
	GUIData TMXtoGUI(const char* tmxファイル名 , const char* シーン名, std::function<void(GUIData& data, std::string& layerName, const char* name, const char* type, int gid, Rect rect, double r, std::vector<std::string>& properties)> Factory関数)
	{
		File file(tmxファイル名, FileMode::Read);
		auto strS = file.GetLineS();
		GUIData guiS;
		bool visible = false;

		std::string layerName = "";
		std::string name = "";
		std::string type = "";
		int gid = 0;
		Rect rect;
		double r = 0;
		std::vector<std::string> properties;
		int index = 0;

		for (auto &it : strS)
		{
			if (it.find("<map") != std::string::npos)
			{
				//フォーム全体の情報
			}
			else if (it.find("<objectgroup") != std::string::npos)
			{
				//レイヤー名を取得
				int a = it.find("name=") + 6;
				layerName = it.substr(a, it.find("\"", a) - a);
			}
			else if (it.find("<object") != std::string::npos)
			{
				//nameとtypeが無い場合と非表示の場合は追加しない
				if (it.find("name=") == std::string::npos || it.find("type=") == std::string::npos || it.find("visible=\"0\"") != std::string::npos)
				{
					visible = false;
				}
				else
				{
					int a = it.find("name=") + 6;
					if (a > 6){ name = it.substr(a, it.find("\"", a) - a); }
					else { name = ""; }

					int b = it.find("type=") + 6;
					if (b > 6){ type = it.substr(b, it.find("\"", b) - b); }
					else { type = ""; }

					int c = it.find("x=") + 3;
					if (c > 3){ rect.x = std::atoi(it.substr(c, it.find("\"", c) - c).c_str()); }

					int d = it.find("y=") + 3;
					if (d > 3){ rect.y = std::atoi(it.substr(d, it.find("\"", d) - d).c_str()); }

					int e = it.find("width=") + 7;
					if (e > 7){ rect.widthRight = std::atoi(it.substr(e, it.find("\"", e) - e).c_str()); }
					else { rect.widthRight = 0; }

					int f = it.find("height=") + 8;
					if (f > 8){ rect.heightDown = std::atoi(it.substr(f, it.find("\"", f) - f).c_str()); }
					else { rect.heightDown = 0; }

					int g = it.find("gid=") + 5;
					if (g > 5){ gid = std::atoi(it.substr(g, it.find("\"", g) - g).c_str()); }
					else { gid = 0; }

					int h = it.find("rotation=") + 10;
					if (h > 10){ r = std::atof(it.substr(h, it.find("\"", h) - h).c_str()); }
					else { r = 0; }

					properties.clear();
					visible = true;
					//次の行がpropertiesでは無いなら追加
					if (strS[index + 1].find("<properties>") == std::string::npos)
					{
						Factory関数(guiS, layerName, name.c_str(), type.c_str(), gid, rect, r, properties);
					}
				}
			}
			else if (it.find("<property") != std::string::npos && visible)
			{
				//非表示の時はプロパティも無視する
				int b = it.find("value=") + 7;
				properties.push_back(it.substr(b, it.find("\"", b) - b));
			}
			else if (it.find("</object>") != std::string::npos && visible)
			{
				//追加処理
				Factory関数(guiS, layerName, name.c_str(), type.c_str(), gid, rect, r, properties);
			}
			++index;
		}

		return guiS;
	}
}