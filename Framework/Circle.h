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

	/** 円を表す図形クラス.*/
	/** \include Shape.h*/
	class Circle : public IShape
	{
	public:
		double x;//!<
		double y;//!<
		double radius;//!<

		Circle(double X座標, double Y座標, double 半径) :
			x(X座標),
			y(Y座標),
			radius(半径)
		{}

		IShape* Clone(double X座標, double Y座標) const
		{
			auto shape = new Circle(X座標, Y座標, this->radius);
			shape->zoomX = this->zoomX;
			shape->zoomY = this->zoomY;
			return shape;
		}

		void SetPos(double X座標, double Y座標)
		{
			this->x = X座標;
			this->y = Y座標;
		}

		void MultiZoom(double 倍率X, double 倍率Y)
		{
			this->radius *= 倍率X;

			zoomX *= 倍率X;
			zoomY *= 倍率Y;
		}

		void Rotate(double 回転する角度){}

		void SetAngle(double 指定角度){}

		void Move(double X移動量, double Y移動量)
		{
			this->x += X移動量;
			this->y += Y移動量;
		}

		double GetX() const
		{
			return int(x);
		}

		double GetY() const
		{
			return int(y);
		}

		double GetW() const
		{
			return int(radius * 2);
		}

		double GetH() const
		{
			return int(radius * 2);
		}

		void Draw(const Color &描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

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
			return
				(
				(point->x - this->x) * (point->x - this->x) + (point->y - this->y) * (point->y - this->y)
				<=
				(this->radius * this->radius)
				);
		}
		bool Hit(const Line *line) const
		{
			return line->LinePoint(x, y, (line->GetThickHarf() + radius));
		}
		bool Hit(const Circle *circle) const
		{
			return
				(
				(this->x - circle->x) * (this->x - circle->x) + (this->y - circle->y) * (this->y - circle->y)
				<=
				(this->radius + circle->radius) * (this->radius + circle->radius)
				);
		}
		bool Hit(const Rect *rect) const
		{
			return
				(
				(
				(
				(
				this->x + this->radius >= rect->GetLeft()
				) && (
				this->x - this->radius <= rect->GetRight()
				)
				) && (
				(
				this->y >= rect->GetTop()
				) && (
				this->y <= rect->GetBottom()
				)
				)
				) || (
				(
				(
				this->x >= rect->GetLeft()
				) && (
				this->x <= rect->GetRight()
				)
				) && (
				(
				this->y + this->radius >= rect->GetTop()
				) && (
				this->y - this->radius <= rect->GetBottom()
				)
				)
				) || (//四角形の四隅と円の判定
				(this->x - rect->GetLeft()) * (this->x - rect->GetLeft()) + (this->y - rect->GetTop()) * (this->y - rect->GetTop()) <= (this->radius * this->radius)
				) || (
				(this->x - rect->GetRight()) * (this->x - rect->GetRight()) + (this->y - rect->GetTop()) * (this->y - rect->GetTop()) <= (this->radius * this->radius)
				) || (
				(this->x - rect->GetLeft()) * (this->x - rect->GetLeft()) + (this->y - rect->GetBottom()) * (this->y - rect->GetBottom()) <= (this->radius * this->radius)
				) || (
				(this->x - rect->GetRight()) * (this->x - rect->GetRight()) + (this->y - rect->GetBottom()) * (this->y - rect->GetBottom()) <= (this->radius * this->radius)
				)
				);
		}
	};
}