//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** 画面構成の全体.*/
	class GUI_Form : public IGUI
	{
	public:
		//typeは無視
		Rect rect;

		GUI_Form() = default;

		GUI_Form(const char* name, const char* type, double x, double y, double w, double h):
			IGUI(name),
			rect(x,y,w,h)
		{}

		void SetProperty(std::string &プロパティ名, std::string &value) override
		{

		}

		void DefineCode(File& 書込先) override
		{
			書込先.AddLine({ "GUI_Form ", name, ";" });

			書込先.AddLine
				(
			{ "GUI_Form ", name, "= {\"", name, "\",\" \",", rect.GetX(), ",", rect.GetY(), ",", rect.GetW(), ",", rect.GetH(), "};" }
			);
		}

		void UpdateCode(File& 書込先) override
		{}
		void DrawCode(File& 書込先) override
		{}
		void InitCode(File& 書込先) override
		{}
		void FinalCode(File& 書込先) override
		{}
	};
}