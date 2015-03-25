//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** ボタンのUI.*/
	class GUI_Button : public IGUI
	{
	public:
		std::string frameName;//type
		Rect rect;

		std::string fontName;
		std::string imageName;//中央に画像表示する場合
		std::string text;//中央に文字を表示する場合

		GUI_Button() = default;

		GUI_Button(const char* name, const char* type, double x, double y, double w, double h ,
				   const char* fontName = "", const char* imageName = "",const char* text = "") :
			IGUI(name),
			frameName(type),
			rect(x,y,w,h),
			fontName(fontName),
			imageName(imageName),
			text(text)
		{}

		void SetProperty(std::string &プロパティ名, std::string &value) override
		{
			if (プロパティ名.find("fontName") != std::string::npos)
			{
				fontName = value;
			}
			else if (プロパティ名.find("imageName") != std::string::npos)
			{
				imageName = value;
			}
			else if(プロパティ名.find("text") != std::string::npos)
			{
				text = value;
			}
		}
		
		void DefineCode(File& 書込先) override
		{
			書込先.AddLine
				(
			{ "GUI_Button ", name, "= {\"", name, "\",\"", frameName, "\",", rect.GetX(), ",", rect.GetY(), ",", rect.GetW(), ",", rect.GetH(),
			",\"", fontName, "\",\"", imageName, "\",\"", text, "\"};" }
			);
		}

		void UpdateCode(File& 書込先) override
		{
			書込先.AddLine({ "if( ",name,".rect.Hit(&pt) ){"});
			書込先.AddLine({ "" });
			書込先.AddLine({ "}" });
		}
		
		void DrawCode(File& 書込先) override
		{

		}

	};
}