#pragma once
#include <Framework/Shape.h>

namespace SDX
{
	/** 描画用枠のインターフェース.*/
	/** \include BmpFrame.h*/
	class IFrame
	{
	public:
		virtual void Draw(const Rect &領域) const = 0;
	};
}