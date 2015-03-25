//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/GUIData.h>
#include <GUI/TranceScene.h>
//#include <GUI/TranceCSV.h>
#include <vector>

namespace SDX
{
	/**コードを変換する関数の名前空間.*/
	namespace TranceCode
	{
		/** Tiledで作成したデータ(.tmx)を変換してGUIDataにする関数.*/
		/**@todo 実装中*/
		/** \include TranceCode.h*/
		GUIData TMXtoGUI(const char* ファイル名)
		{
			File file(ファイル名,FileMode::Read);
			auto strS = file.GetLineS();
			GUIData guiS;
			GUIType guiType = GUIType::Form;
			bool visible = false;

			for (auto &it : strS)
			{
				if (it.find("<map version") != std::string::npos)
				{
					//フォーム全体の情報
				}
				else if (it.find("<objectgroup") != std::string::npos)
				{
					//レイヤーの判定
					if (it.find("Button") != std::string::npos) { guiType = GUIType::Button; }
					else if (it.find("Frame") != std::string::npos) { guiType = GUIType::Frame; }
					else if (it.find("Image") != std::string::npos) { guiType = GUIType::Image; }
					else if (it.find("Text") != std::string::npos) { guiType = GUIType::Text; }
					else if (it.find("Chara4x3") != std::string::npos) { guiType = GUIType::Chara4x3; }
					else { guiType = GUIType::Unknown; }
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
						int b = it.find("type=") + 6;
						int c = it.find("x=") + 3;
						int d = it.find("y=") + 3;
						int e = it.find("width=") + 7;
						int f = it.find("height=") + 8;
						std::string name = it.substr(a, it.find("\"", a) - a);
						std::string type = it.substr(b, it.find("\"", b) - b);
						double x = std::atoi(it.substr(c, it.find("\"", c) - c).c_str());
						double y = std::atoi(it.substr(d, it.find("\"", d) - d).c_str());
						double w = std::atoi(it.substr(e, it.find("\"", e) - e).c_str());
						double h = std::atoi(it.substr(f, it.find("\"", f) - f).c_str());
						//rotationは無視する

						guiS.AddData(guiType, name.c_str(), type.c_str(), x, y, w, h);
						visible = true;
					}
				}
				else if (it.find("<property name=") != std::string::npos && visible)
				{
					//非表示の時はプロパティも無視する
					int a = it.find("name=") + 6;
					int b = it.find("value=") + 7;
					std::string name = it.substr(a,it.find("\"",a) - a );
					std::string value = it.substr(b, it.find("\"", b) - b);
					guiS.SetProperty(guiType,name, value);
				}
			}

			return guiS;
		}

		/** CLIフォームのコードを変換してSceneのコードとCSVファイルを出力.*/
		/** デバッグビルド時のみ有効、フォーム名には.hを含めない*/
		bool CLItoScene(std::string フォーム名)
		{
#ifdef _DEBUG
			//auto uiS = CLItoGUI( (フォーム名 + ".h").c_str() );
			//TranceCode::GUItoCSV((フォーム名 + ".csv").c_str(), uiS);
			//TranceCode::GUItoScene(フォーム名.c_str(), uiS);
			return true;
#endif
			return false;
		}
	}
}