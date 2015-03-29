//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/GUIData.h>
#include <GUI/TmxToGUI.h>
#include "GUI_Factory.h"

namespace SDX
{
	/**tmxファイルとテンプレートからコードを生成する*/
	void TMXtoCode(const char* className, const char* tmxFile, const char* templateFile)
	{
		GUIData guiS = TMXtoGUI(tmxFile, GUI_Factory);//tmxファイルを変換するあれこれ

		std::string outputFile = className;
		outputFile += ".h";

		File file(templateFile, FileMode::Read);
		std::vector<std::string> strS = file.GetLineS();
		file.Close();

		File file2(outputFile.c_str(), FileMode::Write);

		bool isWrite = true;

		for (auto &it : strS)
		{
			if (it.find("CLASSNAME") != std::string::npos)
			{
				int num = it.find("CLASSNAME");
				it.erase(num, 9);
				it.insert(num, className);
				file2.AddLine(it);
			}
			else if (it.find("@Define") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				for (auto &it : guiS.dataS){ it->DefineCode(file2); }
			}
			else if (it.find("@Init") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				for (auto &it : guiS.dataS){ it->InitCode(file2); }
			}
			else if (it.find("@Final") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				for (auto &it : guiS.dataS){ it->FinalCode(file2); }
			}
			else if (it.find("@Update") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				for (auto &it : guiS.dataS){ it->UpdateCode(file2); }
			}
			else if (it.find("@Draw") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				for (auto &it : guiS.dataS){ it->DrawCode(file2); }
			}
			else if (it.find("@Load") != std::string::npos)
			{
				isWrite = false;
				file2.AddLine(it);
				int index = 0;
				file2.AddLine({ "\t\t\tGUIData guiData = TMXtoGUI(\"", tmxFile, "\", GUI_Factory);", });
				file2.AddLine("");
				for (auto &it : guiS.dataS)
				{
					file2.AddLine({ "\t\t\t", it->name, " = *dynamic_cast<", typeid(*it).name(), "*>(guiData.dataS[", index, "].get());" });
					++index;
				}
			}
			else if (it.find("@End") != std::string::npos)
			{
				isWrite = true;
				file2.AddLine(it);
			}
			else if (isWrite)
			{
				file2.AddLine(it);
			}

			//これに囲まれた区間は無視する
		}
	}
}