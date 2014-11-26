//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/IShape .h>

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
	/** \include ShapeSample.h*/
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

		void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

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

	/** 点を表す図形クラス.*/
	/** \include ShapeSample.h*/
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

	/** 太さのある線を表す図形クラス.*/
	/** \include ShapeSample.h*/
	class Line : public IShape
	{
	private:
		virtual void CulParam()
		{
			CulLine();
		}

		void CulLine()
		{
			this->xA = x + cos(angle) * lengthA;
			this->yA = y + sin(angle) * lengthA;
			this->xB = x - cos(angle) * lengthB;
			this->yB = y - sin(angle) * lengthB;
			this->width = abs(this->xB - this->xA);
			this->height = abs(this->yB - this->yA);
			this->thickHarf = this->thick / 2;
			this->thickPow = this->thick * this->thick / 4;
			this->minX = std::min(xA, xB);
			this->maxX = std::max(xA, xB);
			this->minY = std::min(yA, yB);
			this->maxY = std::max(yA, yB);
		}

		double x;//!<
		double y;//!<
		double xA;//!<
		double yA;//!<
		double xB;//!<
		double yB;//!<
		double thick;//!<半径

		double angle;//!<角度

		double lengthA;//!<
		double lengthB;//!<

		double width;//!<
		double height;//!<
		double thickHarf;//!<半径の二条
		double thickPow;//!<
		double minX;//!<
		double minY;//!<
		double maxX;//!<
		double maxY;//!<

	public:

		Line(double X中心座標, double Y中心座標, double 角度, double 長さ, double 太さ) :
			x(X中心座標),
			y(Y中心座標),
			angle(角度),
			lengthA(長さ / 2),
			lengthB(長さ / 2),
			thick(太さ)
		{
			this->CulLine();
		}

		Line(double X中心座標, double Y中心座標, double 角度, double 前方長さ, double 後方長さ, double 太さ) :
			x(X中心座標),
			y(Y中心座標),
			angle(角度),
			lengthA(前方長さ),
			lengthB(後方長さ),
			thick(太さ)
		{
			this->CulLine();
		}

		virtual IShape* Clone(double X座標, double Y座標) const
		{
			auto shape = new Line(X座標, Y座標, this->angle, this->lengthA, this->thick);
			shape->zoomX = this->zoomX;
			shape->zoomY = this->zoomY;
			return shape;
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
			return int(xA - xB);
		}

		double GetH() const
		{
			return int(yA - yB);
		}

		void SetPos(double X座標, double Y座標)
		{
			this->x = X座標;
			this->y = Y座標;
			this->CulParam();
		}

		void MultiZoom(double X倍率, double Y倍率)
		{
			this->lengthA *= X倍率;
			this->lengthB *= Y倍率;
			this->thick *= X倍率;

			this->CulParam();

			zoomX *= X倍率;
			zoomY *= Y倍率;
		}

		void Rotate(double 回転する角度)
		{
			this->angle += 回転する角度;
			this->CulParam();
		}

		void SetAngle(double 指定角度)
		{
			this->angle = 指定角度;
			this->CulParam();
		}

		void Move(double X移動量, double Y移動量)
		{
			this->x += X移動量;
			this->y += Y移動量;
			this->xA += X移動量;
			this->yA += Y移動量;
			this->xB += X移動量;
			this->yB += Y移動量;

			this->minX += X移動量;
			this->minY += Y移動量;
			this->maxX += X移動量;
			this->maxY += Y移動量;
		}

		void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;

		double GetXA() const
		{
			return xA;
		}

		double GetYA() const
		{
			return yA;
		}

		double GetXB() const
		{
			return xB;
		}

		double GetYB() const
		{
			return yB;
		}

		double GetThick() const
		{
			return thick;
		}

		void SetThick(double 太さ)
		{
			thick = 太さ;
			thickHarf = int(thick / 2);
			thickPow = int(thick * thick / 4);
		}

		double GetAngle() const
		{
			return this->angle;
		}

		double GetLength() const
		{
			return this->lengthA + this->lengthB;
		}

		double GetThickHarf() const
		{
			return this->thickHarf;
		}

		double GetThickPow() const
		{
			return this->thickPow;
		}

		double GetMinX() const
		{
			return minX;
		}

		double GetMinY() const
		{
			return minY;
		}

		double GetMaxX() const
		{
			return maxX;
		}

		double GetMaxY() const
		{
			return maxY;
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
			return LinePoint(point->GetX(), point->GetY(), this->GetThick());
		}
		bool Hit(const Line *line) const
		{
			//四角形でラフチェック
			if (RectRect(this->GetXA() - this->GetThickHarf(), this->GetYA() - this->GetThickHarf(), this->GetXB() - line->GetThickHarf(), this->GetYB() - line->GetThickHarf(),
				line->GetXA() - this->GetThickHarf(), line->GetYA() - this->GetThickHarf(), line->GetXB() - line->GetThickHarf(), line->GetYB() - line->GetThickHarf()))
			{
				return true;
			}
			//交差チェック
			if (LineLine(this->GetXA(), this->GetYA(), this->GetXB(), this->GetYB(), line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB()))
			{
				return true;
			}
			//線と端のチェック
			//線が点になっているかで分ける
			if (this->GetLength() != 0)
			{
				if (this->LinePoint(line->GetXA(), line->GetYA(), this->GetThickHarf() + line->GetThickHarf())) return true;
				if (this->LinePoint(line->GetXB(), line->GetYB(), this->GetThickHarf() + line->GetThickHarf())) return true;
			}
			if (line->GetLength() != 0)
			{
				if (line->LinePoint(this->GetXA(), this->GetYA(), this->GetThickHarf() + line->GetThickHarf())) return true;
				if (line->LinePoint(this->GetXB(), this->GetYB(), this->GetThickHarf() + line->GetThickHarf())) return true;
			}

			return false;
		}
		bool Hit(const Rect *rect) const;
		bool Hit(const Circle *circle) const;

		/** 線と点の当たり判定.*/
		bool LinePoint(double px, double py, double range) const
		{
			//点同士の距離
			const double dx = GetXB() - GetXA();
			const double dy = GetYB() - GetYA();

			const double a = dx * dx + dy * dy;
			const double b = dx *(GetXA() - px) + dy *(GetYA() - py);

			//点の場合
			if (a == 0)
			{
				if (
					(GetXA() - px) *(GetXA() - px) +
					(GetYA() - py) *(GetYA() - py)
					< range * range) return true;
				return false;
			}

			const double t = -b / a;

			const double tx = GetXA() + dx*t;
			const double ty = GetYA() + dy*t;

			//線分上の点が範囲内かチェック
			if (tx < minX || tx > maxX || ty < minY || ty > maxY)
			{
				if (
					(xA - px) * (xA - px) + (yA - py) * (yA - py) > range * range &&
					(xB - px) * (xB - px) + (yB - py) * (yB - py) > range * range
					)
				{
					return false;
				}
			}

			const double d = (px - tx)*(px - tx) + (py - ty) * (py - ty);

			return (d < range * range);
		}
	};

	/** 矩形を表す図形クラス.*/
	/** \include ShapeSample.h*/
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

	/** 円を表す図形クラス.*/
	/** \include ShapeSample.h*/
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
			return
				(
				(point->x - this->x) * (point->x - this->x) +
				(point->y - this->y) * (point->y - this->y)
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
			return(
				(this->x - circle->x) * (this->x - circle->x) +
				(this->y - circle->y) * (this->y - circle->y)
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
				(this->x - rect->GetLeft()) * (this->x - rect->GetLeft()) +
				(this->y - rect->GetTop()) * (this->y - rect->GetTop()) <=
				(this->radius * this->radius)
				) || (
				(this->x - rect->GetRight()) * (this->x - rect->GetRight()) +
				(this->y - rect->GetTop()) * (this->y - rect->GetTop()) <=
				(this->radius * this->radius)
				) || (
				(this->x - rect->GetLeft()) * (this->x - rect->GetLeft()) +
				(this->y - rect->GetBottom()) * (this->y - rect->GetBottom()) <=
				(this->radius * this->radius)
				) || (
				(this->x - rect->GetRight()) * (this->x - rect->GetRight()) +
				(this->y - rect->GetBottom()) * (this->y - rect->GetBottom()) <=
				(this->radius * this->radius)
				)
				);
		}
	};
}