//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Drawing.h>

namespace SDX
{
	void Complex::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
	{
		for (auto it : shapes)
		{
			it->Draw(描画色, 透過率, 座標変換Camera);
		}
	}

	void Point::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
	{
		Screen::SetBlendMode(BlendMode::Alpha, 透過率);
		if (座標変換Camera)
		{
			Drawing::Pixel(座標変換Camera->Trans({ x, y }), 描画色);
		}
		else
		{
			Drawing::Pixel({ x, y }, 描画色);
		}
		Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
	}

	void Line::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
	{
		Screen::SetBlendMode(BlendMode::Alpha, 透過率);
		if (座標変換Camera)
		{
			Drawing::Line(座標変換Camera->Trans({ xA, yA }), 座標変換Camera->Trans({ xB, yB }), 描画色, (int)(座標変換Camera->GetZoom()));
			Drawing::Circle({ 座標変換Camera->TransX(xA), 座標変換Camera->TransY(yA), thickHarf*座標変換Camera->GetZoom() }, 描画色, true);
			Drawing::Circle({ 座標変換Camera->TransX(xB), 座標変換Camera->TransY(yB), thickHarf*座標変換Camera->GetZoom() }, 描画色, true);
		}
		else
		{
			Drawing::Line({ xA, yA }, { xB, yB }, 描画色, (int)thick);
			Drawing::Circle({ xA, yA, thickHarf }, 描画色, true);
			Drawing::Circle({ xB, yB, thickHarf }, 描画色, true);
		}
		Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
	}

	void Rect::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
	{
		Screen::SetBlendMode(BlendMode::Alpha, 透過率);
		if (座標変換Camera)
		{
			Drawing::Rect
				(
			{
				座標変換Camera->TransX(x - widthLeft),
				座標変換Camera->TransY(y - heightUp),
				座標変換Camera->GetZoom() * GetW(),
				座標変換Camera->GetZoom() * GetH()
			},
			描画色,
			true
			);
		}
		else
		{
			Drawing::Rect
				(
			{
				x - widthLeft,
				y - heightUp,
				GetW(),
				GetH()
			},
			描画色,
			true
			);
		}
		Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
	}

	void Circle::Draw(Color 描画色, int 透過率, Camera *座標変換Camera) const
	{
		Screen::SetBlendMode(BlendMode::Alpha, 透過率);
		if (座標変換Camera)
		{
			Drawing::Circle({ 座標変換Camera->TransX(x), 座標変換Camera->TransY(y), radius * 座標変換Camera->GetZoom() }, 描画色, true);
		}
		else
		{
			Drawing::Circle({ x, y, radius }, 描画色, true);
		}
		Screen::SetBlendMode(BlendMode::NoBlend, 透過率);
	}
};