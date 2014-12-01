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
}