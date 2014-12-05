//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	/**移動パターンのポリシー.*/
	/** \include Motion.h */
	namespace MOTION
	{
		/**移動方法のインターフェース.*/
		/**ジェネリックな設計なら継承不要.*/
		template <class TShape>
		class IMotion
		{
		public:
			virtual ~IMotion() = default;

			/** Motion終了時はfalseを返す.*/
			virtual bool Update(TShape* 移動対象) = 0;
		};
	}
}