//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Color.h>
#include <Utility/VariadicStream.h>

namespace SDX
{
	/** Font,BmpFont等のインターフェース.*/
	/**    \include FontSample.h*/
	class IFont
	{
	public:
		/** 文字を描画.*/
		virtual bool Draw(const Point &座標, Color 色, VariadicStream 描画する文字列) const = 0;

		/** 文字を回転して描画.*/
		virtual bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const = 0;

		/** 拡大率を指定して文字を描画.*/
		virtual bool DrawExtend(const Point &座標, double X軸拡大率, double Y軸拡大率, Color 色, VariadicStream 描画する文字列) const = 0;
	};
}