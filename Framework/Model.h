//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include<Framework/IModel.h>
namespace SDX
{
	/**Modelの基本クラス.*/
	/** \include Model.h*/
	template <class TShape, class TSprite>
	class Model : public IModel
	{
	public:
		TShape shape;//!< 対応Shape
		TSprite sprite;//!< 対応Sprite

		/**コンストラクタ.*/
		Model(TShape &&図形と位置, TSprite &&描画方法) :
			IModel(shape, sprite),
			shape(図形と位置),
			sprite(描画方法)
		{}
	};
}