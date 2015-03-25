//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** 文字のUI.*/
	class GUI_Text : public IGUI
	{
	public:
		std::string frameName;//type
		Rect rect;

		bool isCenter = false;

		GUI_Text() = default;

		GUI_Text(const char* name, const char* type, double x, double y, double w, double h,
				 bool isCenter = false):
			IGUI(name),
			frameName(type),
			rect(x,y,w,h),
			isCenter(isCenter)
		{}

		void SetProperty(std::string &プロパティ名, std::string &value) override
		{
			
		}

		void DefineCode(File& 書込先) override
		{
			書込先.AddLine
				(
			{ "		GUI_Text ", name, " = {\"", name, "\",\"", frameName, "\",", rect.GetX(), ",", rect.GetY(), ",", rect.GetW(), ",", rect.GetH(),
			",", isCenter, "};" }
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