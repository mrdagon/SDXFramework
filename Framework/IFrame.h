#pragma once
#include <Framework/Shape.h>

namespace SDX
{
	/** �`��p�g�̃C���^�[�t�F�[�X.*/
	/** \include BmpFrame.h*/
	class IFrame
	{
	public:
		virtual void Draw(const Rect &�̈�) const = 0;
	};
}