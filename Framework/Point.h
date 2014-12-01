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

	/** 点を表す図形クラス.*/
	/** \include Shape.h*/
	class Point : public IShape
	{
	public:
		double x;//!<
		double y;//!<

		Point() :
			x(0),
			y(0)
		{};

		Point(double X座標, double Y座標) :
			x(X座標),
			y(Y座標)
		{}

		template<class TA, class TB>
		Point(TA X座標, TB Y座標) :
			x(X座標),
			y(Y座標)
		{}

		IShape* Clone(double X座標, double Y座標) const
		{
			auto shape = new Point(X座標, Y座標);
			shape->zoomX = this->zoomX;
			shape->zoomY = this->zoomY;
			return shape;
		}

		void SetPos(double X座標, double Y座標)
		{
			this->x = X座標;
			this->y = Y座標;
		}

		void Move(double X移動量, double Y移動量)
		{
			this->x += X移動量;
			this->y += Y移動量;
		}

		double GetX() const
		{
			return x;
		}

		double GetY() const
		{
			return y;
		}

		double GetW() const
		{
			return 1;
		}

		double GetH() const
		{
			return 1;
		}

		void MultiZoom(double X倍率, double Y倍率)
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;
		}

		void Rotate(double 回転する角度){}

		void SetAngle(double 指定角度){}

		void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

		bool Hit(const IShape *shape) const
		{
			return shape->Hit(this);
		}
		bool Hit(const Complex *complex) const
		{
			for (auto it : complex->shapes)
			{
				if (it->Hit(this)) return true;
			}
			return false;
		}
		bool Hit(const Point *point) const
		{
			return (point->x == this->x && point->y == this->y);
		}
		bool Hit(const Line *line) const;
		bool Hit(const Rect *rect) const;
		bool Hit(const Circle *circle) const;
	};
}