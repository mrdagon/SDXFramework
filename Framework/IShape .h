//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>
#include <algorithm>

namespace SDX
{
class Complex;
class Point;
class Line;
class Circle;
class Rect;

class Camera;
class Color;
/** 位置情報を持つ図形の抽象クラス.*/
/**    \include ShapeSample.h */
class IShape
{
protected:
    double zoomX;
    double zoomY;

    /** 矩形の交差判定.*/
    static bool RectRect( double x1 , double y1 , double x2 , double y2 , double x3 , double y3 , double x4 , double y4)
    {
        //x座標をラフチェック
        if ( x1 >= x2)
        {
            if ((x1 < x3 && x1 < x4) || (x2 > x3 && x2 > x4))
            {
                return false;
            }
        }
        else
        {
            if ((x2 < x3 && x2 < x4) || (x1 > x3 && x1 > x4))
            {
                return false;
            }
        }
        //y座標をラフチェック
        if (y1 >= y2)
        {
            if ((y1 < y3 && y1 < y4) || (y2 > y3 && y2 > y4))
            {
                return false;
            }
        }
        else
        {
            if ((y2 < y3 && y2 < y4) || (y1 > y3 && y1 > y4))
            {
                return false;
            }
        }

        return true;
    }
    
    /** 線分の交差判定.*/
    static bool LineLine( double x1 , double y1 , double x2 , double y2 , double x3 , double y3 , double x4 , double y4)
    {
        //交差判定
        if ((double(x1 - x2) * (y3 - y1) + (y1 - y2) * (x1 - x3)) *
            (double(x1 - x2) * (y4 - y1) + (y1 - y2) * (x1 - x4)) > 0)
        {
            return false;
        }

        if ((double(x3 - x4) * (y1 - y3) + (y3 - y4) * (x3 - x1)) *
            (double(x3 - x4) * (y2 - y3) + (y3 - y4) * (x3 - x2)) > 0)
        {
            return false;
        }
        return true;

    }
            
    /** 二点間の距離を計算.*/
    static int PointPoint(double x1 , double y1 , double x2 , double y2)
    {
        return int((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }
            
public:
    IShape():
        zoomX(1),
        zoomY(1)
    {}
            
    /** 衝突判定.*/
    virtual bool Hit(const IShape *IShape) const = 0;
    virtual bool Hit(const Complex *complex) const = 0;
    virtual bool Hit(const Point *point) const = 0;
    virtual bool Hit(const Line *line) const = 0;
    virtual bool Hit(const Rect *rect) const = 0;
    virtual bool Hit(const Circle *circle) const = 0;
    
    /** 指定座標に移動.*/
    virtual void SetPos(double X座標 , double Y座標) = 0;
            
    /** 同じ形の図形を作る.*/
    virtual IShape* Clone(double x , double y) const = 0;

    /** 拡大率を設定.*/
    void SetZoom(double X拡大率 , double Y拡大率)
    {
        MultiZoom( X拡大率 / zoomX , Y拡大率 / zoomY);
    }
            
    /** 拡大率を掛け算する.*/
    void MultiZoom(double 倍率)
    {
        MultiZoom(倍率,倍率);
    }
            
    /** 縦横別で拡大率を掛け算する.*/
    virtual void MultiZoom(double X倍率 , double Y倍率) = 0;
            
    /** 相対座標で移動.*/
    virtual void Move(double X移動量 , double Y移動量) = 0;
            
    /** 極座標で移動.*/
    void MoveA(double 距離 , double 方向 )
    {
        Move( 距離 * cos(方向) , 距離 * sin(方向) );
    }
            
    /** 描画する.*/
    virtual void Draw(Color 描画色 , int 透過率 , Camera *座標変換Camera = nullptr) const = 0;
            
    /** 回転する.*/
    virtual void Rotate(double 回転する角度) = 0;
            
    /** 角度を指定する.*/
    virtual void SetAngle(double 指定角度) = 0;

    /** 対象との角度を取得.*/
    double GetDirect(IShape* 比較対象)
    {
        return atan2(比較対象->GetY() - this->GetY(), 比較対象->GetX() - this->GetX());
    }

    /** 対象との相対座標を取得.*/
    double GetDistance(IShape* 比較対象)
    {
        const double xd = this->GetX() - 比較対象->GetX();
        const double yd = this->GetY() - 比較対象->GetY();

        return sqrt( xd * xd + yd * yd );
    }
            
    /** X座標を取得.*/
    virtual double GetX() const = 0;

    /** Y座標を取得.*/
    virtual double  GetY() const = 0;

    /** 幅を取得.*/
    virtual double  GetW() const = 0;

    /** 高さを取得.*/
    virtual double  GetH() const = 0;
};
}