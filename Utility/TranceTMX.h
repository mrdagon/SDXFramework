//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/File.h>
#include <Utility/GUIData.h>
#include <Utility/TranceScene.h>
#include <Utility/TranceCSV.h>
#include <vector>

namespace SDX
{
	/**コードを変換する関数の名前空間.*/
	namespace TranceCode
	{
		/** Tiledで作成したデータ(.tmx)を変換してGUIDataにする関数.*/
		/**@todo 実装中*/
		/** \include TranceCode.h*/
		std::vector<GUIData> TMXtoGUI(const char* ファイル名)
		{
			File file(ファイル名,FileMode::Read);
			auto strS = file.GetLineS();
			std::vector<GUIData> uiS;

			uiS.push_back(GUIData());
			uiS[0].type = GUIType::Client;
			
			int index = 0;
			int a, b, c;
			GUIType nowType = GUIType::Client;

			//内部はxml形式
			//一行目はverとエンコーディング
			//二行目はMapの設定
			//以降データ
			//<layer name = "レイヤー名" , width="64" height="48">
			//<data encoding =csv>
			//ここにデータ
			//<data>
			//</layer>
			//<objectgroup color="#f9f9ff" name="オブジェクト・レイヤー 1" opacity="0.9">
			//<object id="26" name="ああああ" type="abcd" x="379" y="161" width="151" height="126"/>
			//<properties>
			//<property name = "拡大率" value = "2" / >
			//< / properties>
			//</objectgroup>
			//</map>
			//と言った感じ nameとtypeは省略される場合もある
			//layer毎にpicture,label,buttonを対応させれば良さそう
			for (auto &it : strS)
			{
				if (it.find("<objectgroup") != std::string::npos)
				{
					//Typeの判別
					uiS.push_back(GUIData());
					if (it.find("Button") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Button; }
					else if (it.find("PictureBox") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Picture; }
					else if (it.find("Label") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Label; }
					else { uiS[uiS.size() - 1].type = GUIType::Unknown; }
				}
				else if (it.find("<object") != std::string::npos)
				{
					++index;
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].size.x = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].size.y = std::atoi(it.substr(b + 1, c - b).c_str());
				}
				else if (it.find("</objectgroup") != std::string::npos)
				{
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].lineX = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].lineY = std::atoi(it.substr(b + 1, c - b).c_str());
				}
				else if (it.find("<property name = ") != std::string::npos)
				{
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].lineX = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].lineY = std::atoi(it.substr(b + 1, c - b).c_str());
				}
			}

			std::vector<GUIData>::iterator it;

			it = uiS.begin();
			while (it != uiS.end()) {
				if ( it->isVisible == false)
				{
					it = uiS.erase(it);
					continue;
				}

				++it;
			}

			return uiS;
		}

		/** CLIフォームのコードを変換してSceneのコードとCSVファイルを出力.*/
		/** デバッグビルド時のみ有効、フォーム名には.hを含めない*/
		bool CLItoScene(std::string フォーム名)
		{
#ifdef _DEBUG
			auto uiS = CLItoGUI( (フォーム名 + ".h").c_str() );
			TranceCode::GUItoCSV((フォーム名 + ".csv").c_str(), uiS);
			TranceCode::GUItoScene(フォーム名.c_str(), uiS);
			return true;
#endif
			return false;
		}
	}
}