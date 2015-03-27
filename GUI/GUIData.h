//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/IGUI.h>

namespace SDX
{
	/** GUIオブジェクトのテンプレート.*/
	class GUIData
	{
	public:
		//全体のデータ

		//マップレイヤーのデータ

		//マップチップのデータ

		//IGUIの情報
		std::vector<std::shared_ptr<IGUI>> dataS;
	};
}