//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Rect.h>

namespace SDX
{
	/** GUIオブジェクトのテンプレート.*/
	class IGUI
	{
	public:
		IGUI(int id, const Rect& rect):
			id(id),
			rect(rect)
		{}

		int id;
		Rect rect;

		virtual void Init(){};
		virtual void Final(){};
		virtual void Draw(){};
		virtual void Update(){};
	};
}