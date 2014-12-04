//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	/**Modelの移動パターンのポリシー.*/
	/** \include Motion.h */
	namespace MOTION
	{
		/**Modelの移動方法.*/
		/**ジェネリックな設計なら継承不要.*/
		template <class TModel>
		class IMotion
		{
		public:
			/** Motion終了時はfalseを返す.*/
			virtual bool Update(TModel* 移動対象) = 0;
		};
	}
}