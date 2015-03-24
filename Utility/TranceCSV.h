//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/File.h>
#include <Utility/GUIData.h>
#include <vector>

namespace SDX
{
	/**コードを変換する関数の名前空間.*/
	namespace TranceCode
	{
		/** CSV形式のファイルをGUIDataに変換する.*/
		/** \include TranceCode.h*/
		std::vector<GUIData> CSVtoGUI(const char* ファイル名)
		{
			File file(ファイル名,FileMode::Read);
			auto strS = file.GetCsvToString2();//2次元配列の文字列型
			std::vector<GUIData> uiS;
			int index = 0;

			for (auto && it : strS)
			{
				uiS.push_back(GUIData());
				uiS[index].name = it[0];
				uiS[index].text = it[1];
				uiS[index].tag = it[2];
				uiS[index].type = (GUIType)std::atoi(it[3].c_str());
				uiS[index].size.x = std::atoi(it[4].c_str());
				uiS[index].size.y = std::atoi(it[5].c_str());
				uiS[index].size.widthRight = std::atoi(it[6].c_str());
				uiS[index].size.heightDown = std::atoi(it[7].c_str());
				uiS[index].lineX = std::atoi(it[8].c_str());
				uiS[index].lineY = std::atoi(it[9].c_str());
				++index;
			}

			return uiS;
		}

		/** GUIDataをCSV形式のファイルに変換する.*/
		/** \include TranceCode.h*/
		bool GUItoCSV(const char* ファイル名 ,std::vector<GUIData> &GUIデータ)
		{			
			File file(ファイル名, FileMode::Write);

			std::string str;

			for (auto && it : GUIデータ)
			{
				str = it.name + "," + it.text + "," + it.tag + "," + std::to_string((int)it.type) + "," + std::to_string(it.size.x) + "," + std::to_string(it.size.y) + "," + std::to_string(it.size.widthRight) + "," + std::to_string(it.size.heightDown) + std::to_string(it.lineX) + std::to_string(it.lineY) + "\r\n";
				file.Write(str, false);
			}

			return true;
		}

	}
}