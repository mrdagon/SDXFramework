//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/File.h>
#include <Framework/Rect.h>
#include <Framework/Point.h>

namespace SDX
{
	/** GUIオブジェクトのテンプレート.*/
	class IGUI
	{
	public:
		IGUI() = default;

		IGUI(const char* name):
			name(name)
		{}

		std::string name;

		virtual void DefineCode(File& 書込先) = 0;

		virtual void UpdateCode(File& 書込先){};
		virtual void DrawCode(File& 書込先){};
		virtual void InitCode(File& 書込先){};
		virtual void FinalCode(File& 書込先){};

		virtual void SetProperty(std::string &プロパティ名 , std::string &value){}
		virtual void WriteCSV(File& 書込先){};
	};
}