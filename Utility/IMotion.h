//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	class IModel;
	/**移動パターンのポリシー.*/
	/** \include Motion.h */
	namespace MOTION
	{
		/**移動方法のインターフェース.*/
		/**ジェネリックな設計なら継承不要.*/
		class IMotion
		{
		public:
			virtual ~IMotion() = default;

			/** Motion終了時はfalseを返す.*/
			virtual bool Update(IShape* 移動対象) = 0;

			virtual bool Update(IModel* 移動対象);
		};
	}
}