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
		//int id;
		//Rect rect;

		virtual void Init(){};
		virtual void Final(){};
		virtual void Draw(){};
		virtual void Update(){};
	};
}