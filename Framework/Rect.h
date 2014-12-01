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

	/** 矩形を表す図形クラス.*/
	/** \include Shape.h*/
	class Rect : public IShape
	{
	public:
		double x;//!<
		double y;//!<

		double widthLeft;//!<
		double widthRight;//!<

		double heightUp;//!<
		double heightDown;//!<

		/*座標と大きさを指定*/
		/*デフォルト引数だと左上座標と大きさを指定*/
		/*横幅A=横幅B,高さA=高さBとすると中心座標指定になる*/
		Rect(double X座標, double Y座標, double 横幅A, double 高さA, double 横幅B = 0, double 高さB = 0) :
			x(X座標),
			y(Y座標),
			heightUp(高さB),
			heightDown(高さA),
			widthLeft(横幅B),
			widthRight(横幅A)
		{}

		template <class T>
		Rect(T X座標, T Y座標, T 横幅A, T 高さA, T 横幅B = 0, T 高さB = 0) :
			x((double)X座標),
			y((double)Y座標),
			heightUp((double)高さB),
			heightDown((double)高さA),
			widthLeft((double)横幅B),
			widthRight((double)横幅A)
		{}

		virtual IShape* Clone(double X座標, double Y座標) const
		{
			auto shape = new Rect(X座標, Y座標, widthRight, heightDown, widthLeft, heightUp);
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

		void MultiZoom(double X倍率, double Y倍率)
		{
			widthLeft *= X倍率;
			widthRight *= X倍率;

			heightUp *= Y倍率;
			heightDown *= Y倍率;
		}

		void Rotate(double 回転する角度){}

		void SetAngle(double 指定角度){}

		void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

		inline double GetX() const
		{
			return x;
		}

		inline double GetY() const
		{
			return y;
		}

		inline double GetW() const
		{
			return widthLeft + widthRight;
		}

		inline double GetH() const
		{
			return heightUp + heightDown;
		}

		inline double GetLeft() const
		{
			return x - widthLeft;
		}

		inline double GetTop() const
		{
			return y - heightUp;
		}

		inline double GetRight() const
		{
			return x + widthRight;
		}

		inline double GetBottom() const
		{
			return y + heightDown;
		}

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
			return (
				(
				point->x < this->GetRight()
				) && (
				point->x > this->GetLeft()
				) && (
				point->y < this->GetBottom()
				) && (
				point->y > this->GetTop()
				)
				);
		}
		bool Hit(const Line *line) const
		{
			if (
				!(
				line->GetMaxX() + line->GetThickHarf() < this->GetLeft() ||
				line->GetMinX() - line->GetThickHarf() > this->GetTop() ||
				line->GetMaxY() + line->GetThickHarf() < this->GetRight() ||
				line->GetMinY() - line->GetThickHarf() > this->GetBottom()
				)
				)
			{
				return false;
			}

			//√２/2≒0.7
			if (LineLine(line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB()
				, this->GetLeft() - int(line->GetThickHarf() * 0.7), this->GetTop() - int(line->GetThickHarf() * 0.7), this->GetRight() + int(line->GetThickHarf() * 0.7), this->GetBottom() + int(line->GetThickHarf() * 0.7)))
			{
				return true;
			}

			if (LineLine(line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB()
				, this->GetRight() + int(line->GetThickHarf() * 0.7), this->GetTop() - int(line->GetThickHarf() * 0.7), this->GetLeft() - int(line->GetThickHarf() * 0.7), this->GetBottom() + int(line->GetThickHarf() * 0.7)))
			{
				return true;
			}

			//端の丸い所以外判定
			if (
				line->GetXA() + line->GetThickHarf() > this->GetLeft() && line->GetXA() - line->GetThickHarf() < this->GetRight() &&
				line->GetYA() + line->GetThickHarf() > this->GetTop() && line->GetYA() - line->GetThickHarf() < this->GetBottom()
				)
			{
				//端の丸い所判定
				if (line->GetXA() < this->GetLeft() && line->GetYA() < this->GetTop())
				{//左上
					if ((line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
						(line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() > this->GetRight() && line->GetYA() < this->GetTop())
				{//右上
					if ((line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
						(line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() < this->GetLeft() && line->GetYA() > this->GetBottom())
				{//左下
					if ((line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
						(line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() > this->GetRight() && line->GetYA() > this->GetBottom())
				{//右下
					if ((line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
						(line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else
				{
					return true;
				}
			}

			if (
				line->GetXB() + line->GetThickHarf() > this->GetLeft() && line->GetXB() - line->GetThickHarf() < this->GetRight() &&
				line->GetYB() + line->GetThickHarf() > this->GetTop() && line->GetYB() - line->GetThickHarf() < this->GetBottom()
				)
			{
				//端の丸い所判定
				if (line->GetXB() < this->GetLeft() && line->GetYB() < this->GetTop())
				{//左上
					if ((line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
						(line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() > this->GetRight() && line->GetYB() < this->GetTop())
				{//右上
					if ((line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
						(line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() < this->GetLeft() && line->GetYB() > this->GetBottom())
				{//左下
					if ((line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
						(line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() > this->GetRight() && line->GetYB() > this->GetBottom())
				{//右下
					if ((line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
						(line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else
				{
					return true;
				}
			}

			return false;
		}
		bool Hit(const Rect *rect) const
		{
			return !(GetRight() < rect->GetLeft() || GetLeft() > rect->GetRight() || GetBottom() < rect->GetTop() || GetTop() > rect->GetBottom());
		}
		bool Hit(const Circle *circle) const;
	};
}