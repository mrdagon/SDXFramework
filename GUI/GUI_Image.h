//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** 画像のUI.*/
	class GUI_Image : public IGUI
	{
	public:
		std::string imageName;//type
		Point point;

		double size = 1;//表示倍率

		GUI_Image(const char* name, const char* type, double x, double y, double w, double h) :
			IGUI(name),
			imageName(type),
			point(x + w/2,y + h/2)
		{}

		void SetProperty(std::string &プロパティ名, std::string &value) override
		{

		}

		void DefineCode(File& 書込先) override
		{
			書込先.AddLine
				(
			{ "GUI_Image ", name, "= {\"", name, "\",\"", imageName, "\",", point.GetX(), ",", point.GetY(), ",", point.GetW(), ",", point.GetH(),
			",", size, "};" }
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