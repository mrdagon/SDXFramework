//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** GUI.*/
	class GUI_NAME : public IGUI
	{
	public:
		//@メンバー宣言

		//@コンストラクタ

		void DefineCode(File& 書込先) override
		{
			//@DefineCode
		}

		void UpdateCode(File& 書込先) override
		{
		}
		
		void DrawCode(File& 書込先) override
		{
		}

		void InitCode(File& 書込先) override
		{
		}

		void FinalCode(File& 書込先) override
		{
		}

	};
}