//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Rect.h>
#include <Utility/ISpeed.h>
#include <string>
#include <Multimedia/Color.h>

namespace SDX
{
	/** GUIの種類.*/
	enum class GUIType
	{
		Client,
		Label,
		Picture,
		Button,
		Unknown
	};

	/**GUIオブジェクトのデータ型.*/
	struct GUIData
	{
		//c++/cliフォームの場合は以下
		//tiledではTypeに相当する箇所が無くカスタム設定が必要
		Rect size;
		GUIType type;
		std::string name;
		std::string text;
		std::string tag;		
		int lineX = 1;
		int lineY = 1;
		bool isVisible = true;

		Point& GetPoint()
		{
			size.GetPoint();
		}

		Point& GetCenter()
		{
			//size.GetCenter();
		}
	};

}