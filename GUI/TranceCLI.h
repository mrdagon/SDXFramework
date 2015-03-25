//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/File.h>
#include <GUI/GUIData.h>
#include <GUI/TranceScene.h>
#include <GUI/TranceCSV.h>
#include <vector>

namespace SDX
{
	/**コードを変換する関数の名前空間.*/
	namespace TranceCode
	{
		/** CLIフォームのコードを変換してGUIDataにする関数.*/
		/** \include TranceCode.h*/
		std::vector<GUIData> CLItoGUI(const char* ファイル名)
		{
			File file(ファイル名,FileMode::Read);
			auto strS = file.GetLineS();
			std::vector<GUIData> uiS;

			uiS.push_back(GUIData());
			uiS[0].type = GUIType::Client;

			int index = 0;
			int a, b, c;

			for (auto &it : strS)
			{
				//->を誤検索用に付けている
				if (it.find("private: System::Windows::Forms::") != std::string::npos)
				{
					//Typeの判別
					uiS.push_back(GUIData());
					if (it.find("Button") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Button; }
					else if (it.find("PictureBox") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Picture; }
					else if (it.find("Label") != std::string::npos) { uiS[uiS.size() - 1].type = GUIType::Label; }
					else { uiS[uiS.size() - 1].type = GUIType::Unknown; }
				}
				else if (it.find("->Location") != std::string::npos)
				{
					++index;
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].size.x = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].size.y = std::atoi(it.substr(b + 1, c - b).c_str());
				}
				else if (it.find("->MinimumSize") != std::string::npos)
				{
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].lineX = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].lineY = std::atoi(it.substr(b + 1, c - b).c_str());
				}
				else if (it.find("->Name") != std::string::npos)
				{
					a = it.find_first_of("\"");
					b = it.find_last_of("\"");
					uiS[index].name = it.substr(a + 1, b - a - 1).c_str();
				}
				else if (it.find("->Size") != std::string::npos)
				{
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[index].size.widthRight = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[index].size.heightDown = std::atoi(it.substr(b + 1, c - b).c_str());
				}
				else if (it.find("->Text") != std::string::npos)
				{
					a = it.find_first_of("\"");
					b = it.find_last_of("\"");
					uiS[index].text = it.substr(a + 1, b - a - 1).c_str();
				}
				else if (it.find("->ClientSize") != std::string::npos)
				{
					//フォーム全体の大きさ
					a = it.find_first_of("(");
					b = it.find_first_of(",");
					c = it.find_first_of(")");
					uiS[0].size = { 0, 0, 0, 0 };
					uiS[0].size.widthRight = std::atoi(it.substr(a + 1, b - a).c_str());
					uiS[0].size.heightDown = std::atoi(it.substr(b + 1, c - b).c_str());
					index = 0;//以降は全てクライアントの値になる
				}
				else if (it.find("->Tag") != std::string::npos)
				{
					a = it.find_first_of("\"");
					b = it.find_last_of("\"");
					uiS[index].tag = it.substr(a + 1, b - a - 1).c_str();
				}
				else if (it.find("->Visible") != std::string::npos)
				{
					uiS[index].isVisible = false;
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