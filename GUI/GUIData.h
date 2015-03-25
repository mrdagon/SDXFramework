//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>
#include <GUI/IGUI.h>
#include <GUI/GUI_Form.h>
#include <GUI/GUI_Button.h>
#include <GUI/GUI_Frame.h>
#include <GUI/GUI_Image.h>
#include <GUI/GUI_Text.h>
#include <GUI/GUI_Chara4x3.h>

namespace SDX
{
	/** GUIの種類.*/
	enum class GUIType
	{
		Form,
		Button,
		Frame,
		Image,
		Text,
		Chara4x3,
		Unknown
	};

	/** GUIデータを格納しておく.*/
	class GUIData
	{
	public:
		GUIData() = default;

		std::vector<std::shared_ptr<IGUI>> dataS;

		bool AddData( GUIType guiType , const char* name, const char* type, double x, double y, double w, double h)
		{
			switch (guiType)
			{
			case GUIType::Button:
				dataS.push_back(std::make_shared<GUI_Button>(name, type, x, y, w, h));
				break;
			case GUIType::Frame:
				dataS.push_back(std::make_shared<GUI_Frame>(name, type, x, y, w, h));
				break;
			case GUIType::Image:
				dataS.push_back(std::make_shared<GUI_Image>(name, type, x, y, w, h));
				break;
			case GUIType::Text:
				dataS.push_back(std::make_shared<GUI_Text>(name, type, x, y, w, h));
				break;
			case GUIType::Chara4x3:
				dataS.push_back(std::make_shared<GUI_Chara4x3>(name, type, x, y, w, h));
				break;
			case GUIType::Unknown:
				return false;
			}
			return true;
		}

		void SetProperty(GUIType guiType, std::string &name, std::string &value)
		{
			dataS.back()->SetProperty(name,value);
		}

		//宣言,定義文
		void DefineCode(File& 書込先)
		{
			for (auto &it : dataS)
			{
				it->DefineCode(書込先);
				//書込先.AddLine({ typeid(*it).name() , " " ,it->name, ";" });
			}
		}

		void UpdateCode(File& 書込先)
		{
			for (auto &it : dataS){ it->UpdateCode(書込先); }
		}

		void DrawCode(File& 書込先)
		{
			for (auto &it : dataS){ it->DrawCode(書込先); }	
		}

		void InitCode(File& 書込先)
		{
			for (auto &it : dataS){ it->InitCode(書込先); }	
		}

		void FinalCode(File& 書込先)
		{
			for (auto &it : dataS){ it->FinalCode(書込先); }
		}

		//代入文
		void CopyCode(File& 書込先)
		{
			int index = 0;
			for (auto &it : dataS)
			{
				書込先.AddLine({"\t\t\t", it->name, " = *dynamic_cast<", typeid(*it).name(), "*>(guiData.dataS[", index, "].get());" });
				++index;
			}
		}

	};
}