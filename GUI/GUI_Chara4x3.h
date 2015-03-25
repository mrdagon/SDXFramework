//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/*4方向3パターンアニメのGUI*/
	class GUI_Chara4x3 : public IGUI
	{
	private:
		int anime = 0;//0～2
		int timer = 0;//
	public:
		std::string imageName;//type
		Point point;

		int direct = 0;//0~3
		int speed = 0;

		GUI_Chara4x3() = default;

		GUI_Chara4x3(const char* name, const char* type, double x, double y, double w, double h , int direct = 0, int speed = 0) :
			IGUI(name),
			imageName(type),
			point(x,y),
			direct(direct),
			speed(speed)
		{}

		void SetProperty(std::string &プロパティ名, std::string &value) override
		{

		}

		void DefineCode(File& 書込先) override
		{
			書込先.AddLine
			(
			{ "GUI_Chara4x3 ", name, "= {\"", name, "\",\"", imageName, "\",", point.GetX(), ",", point.GetY(), ",", point.GetW(), ",", point.GetH(),
			",", direct, ",", speed, "};" }
			);

		}

		void UpdateCode(File& 書込先) override
		{
		
		}

		void DrawCode(File& 書込先) override
		{
		
		}
	};
}