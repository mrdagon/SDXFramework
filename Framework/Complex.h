//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <Framework/IShape.h>
namespace SDX
{
	class Complex;
	class Point;
	class Line;
	class Circle;
	class Rect;

	class Camera;
	class Color;

	/** 複合図形を表すクラス.*/
	/** \include Shape.h*/
	class Complex : public IShape
	{
	public:
		std::vector<IShape*> shapes;//!<

		Complex(){};

		Complex(IShape *shape)
		{
			shapes.push_back(shape);
		}

		IShape* Clone(double x, double y) const
		{
			Complex *buf = new Complex();

			for (auto it : shapes)
			{
				buf->shapes.push_back(it);
			}

			return buf;
		}

		void SetPos(double X座標, double Y座標)
		{
			for (auto it : shapes)
			{
				it->SetPos(X座標, Y座標);
			}
		}

		void Move(double X移動量, double Y移動量)
		{
			for (auto it : shapes)
			{
				it->Move(X移動量, Y移動量);
			}
		}

		double GetX() const
		{
			return shapes[0]->GetX();
		}

		double GetY() const
		{
			return shapes[0]->GetY();
		}

		double GetW() const
		{
			return shapes[0]->GetW();
		}

		double GetH() const
		{
			return shapes[0]->GetH();
		}

		void MultiZoom(double X倍率, double Y倍率)
		{
			for (auto it : shapes)
			{
				it->MultiZoom(X倍率, Y倍率);
			}
			zoomX *= X倍率;
			zoomY *= Y倍率;
		}

		void Rotate(double 回転する角度)
		{
			for (auto it : shapes)
			{
				it->Rotate(回転する角度);
			}
		}

		void SetAngle(double 指定角度)
		{
			for (auto it : shapes)
			{
				it->SetAngle(指定角度);
			}
		}

		void Draw(const Color &描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

		bool Hit(const IShape *shape) const
		{
			return shape->Hit(this);
		}
		bool Hit(const Complex *complex) const
		{
			for (auto itA : this->shapes)
			{
				for (auto itB : this->shapes)
				{
					if (itA->Hit(itB)) return true;
				}
			}
			return false;
		}
		bool Hit(const Point *point) const;
		bool Hit(const Line *line) const;
		bool Hit(const Rect *rect) const;
		bool Hit(const Circle *circle) const;
	};
}