#pragma once//☀SDXFramework
//#include <Framework/Camera.h>
#include <vector>
#include <algorithm>

namespace SDX
{
class Shape;
class Complex;
class Point;
class Line;
class Circle;
class Rect;

class Camera;
class Color;
/** 位置情報を持つ図形の抽象クラス.*/
/**    \include ShapeSample.h */
class Shape
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
    Shape():
        zoomX(1),
        zoomY(1)
    {}
            
    /** 衝突判定.*/
    virtual bool Hit(const Shape *shape) const = 0;
    virtual bool Hit(const Complex *complex) const = 0;
    virtual bool Hit(const Point *point) const = 0;
    virtual bool Hit(const Line *line) const = 0;
    virtual bool Hit(const Rect *rect) const = 0;
    virtual bool Hit(const Circle *circle) const = 0;
    
    /** 指定座標に移動.*/
    virtual void SetPos(double X座標 , double Y座標) = 0;
            
    /** 同じ形の図形を作る.*/
    virtual Shape* Clone(double x , double y) const = 0;

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
    double GetDirect(Shape* 比較対象)
    {
        return atan2(比較対象->GetY() - this->GetY(), 比較対象->GetX() - this->GetX());
    }

    /** 対象との相対座標を取得.*/
    double GetDistance(Shape* 比較対象)
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
    
/** 複合図形を表すクラス.*/
/**    \include ShapeSample.h*/
class Complex : public Shape
{
public:
    std::vector<Shape*> shapes;

    Complex(){};

    Complex(Shape *shape)
    {
        shapes.push_back( shape );
    }
            
    Shape* Clone(double x,double y) const
    {
        Complex *buf = new Complex();

        for( auto it: shapes )
        {
            buf->shapes.push_back( it );
        }

        return buf;
    }
            
    void SetPos(double X座標 , double Y座標)
    {
        for( auto it: shapes )
        {
            it->SetPos( X座標 , Y座標 );
        }        
    }

    void Move(double X移動量 , double Y移動量)
    {
        for( auto it: shapes )
        {
            it->Move( X移動量 , Y移動量 );
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

    void MultiZoom(double X倍率 , double Y倍率)
    {
        for( auto it: shapes )
        {
            it->MultiZoom(X倍率, Y倍率);
        }
        zoomX *= X倍率;
        zoomY *= Y倍率;
    }

    void Rotate(double 回転する角度)
    {
        for( auto it: shapes )
        {
            it->Rotate( 回転する角度 );
        }
    }

    void SetAngle(double 指定角度)
    {
        for( auto it: shapes )
        {
            it->SetAngle( 指定角度 );
        }
    }

    void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;
        
    bool Hit(const Shape *shape) const
    {
        return shape->Hit( this );
    }
    bool Hit(const Complex *complex) const
    {
        for( auto itA : this->shapes )
        {
            for( auto itB : this->shapes )
            {
                if( itA->Hit(itB) ) return true;
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
/**    \include ShapeSample.h*/
class Point : public Shape
{
public:
    double x;
    double y;

    Point() :
        x(0),
        y(0)
    {};
            
    Point(double X座標 , double Y座標):
        x(X座標),
        y(Y座標)
    {}

    Shape* Clone(double X座標,double Y座標) const
    {
        auto shape = new Point( X座標 , Y座標 );
        shape->zoomX = this->zoomX;
        shape->zoomY = this->zoomY;
        return shape;
    }

    void SetPos(double X座標 , double Y座標)
    {
        this->x = X座標;
        this->y = Y座標;            
    }

    void Move(double X移動量 , double Y移動量)
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
    
    void MultiZoom(double X倍率 , double Y倍率)
    {
        zoomX *= X倍率;
        zoomY *= Y倍率;
    }

    void Rotate(double 回転する角度){}

    void SetAngle(double 指定角度){}

    void Draw(Color 描画色, int 透過率, Camera *座標変換Camera = nullptr) const;
            
    bool Hit(const Shape *shape) const
    {
        return shape->Hit( this );
    }
    bool Hit(const Complex *complex) const
    {
        for( auto it : complex->shapes )
        {
            if( it->Hit( this ) ) return true;
        }
        return false;
    }
    bool Hit(const Point *point) const
    {
        return ( point->x == this->x && point->y == this->y );
    }
    bool Hit(const Line *line) const;
    bool Hit(const Rect *rect) const;
    bool Hit(const Circle *circle) const;
};
    
/** 太さのある線を表す図形クラス.*/
/**    \include ShapeSample.h*/
class Line : public Shape
{
private:
    virtual void CulParam()
    {
        CulLine();
    }

    void CulLine()
    {
        this->xA = x + cos( angle ) * lengthA;
        this->yA = y + sin( angle ) * lengthA;
        this->xB = x - cos( angle ) * lengthB;
        this->yB = y - sin( angle ) * lengthB;
        this->width = abs(this->xB - this->xA);
        this->height =    abs(this->yB - this->yA);
        this->thickHarf = this->thick / 2;
        this->thickPow = this->thick * this->thick / 4;
        this->minX = std::min( xA , xB );
        this->maxX = std::max( xA , xB );
        this->minY = std::min( yA , yB );
        this->maxY = std::max( yA , yB );
    }

    double x;
    double y;
    double xA;
    double yA;
    double xB;
    double yB;
    double thick;//半径

    double angle;//角度

    double lengthA;
    double lengthB;

    double width;
    double height;
    double thickHarf;//半径の二条
    double thickPow;
    double minX;
    double minY;
    double maxX;
    double maxY;

public:

    Line( double X中心座標 , double Y中心座標 , double 角度 , double 長さ , double 太さ):
        x(X中心座標),
        y(Y中心座標),
        angle( 角度 ),
        lengthA( 長さ/2 ),
        lengthB( 長さ/2 ),
        thick( 太さ )
    {
        this->CulLine();
    }

    Line(double X中心座標, double Y中心座標, double 角度, double 前方長さ , double 後方長さ , double 太さ) :
        x(X中心座標),
        y(Y中心座標),
        angle(角度),
        lengthA(前方長さ),
        lengthB(後方長さ),
        thick(太さ)
    {
        this->CulLine();
    }

    virtual Shape* Clone(double X座標,double Y座標) const
    {
        auto shape = new Line( X座標 , Y座標 , this->angle , this->lengthA , this->thick);
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

    void SetPos(double X座標 , double Y座標 )
    {
        this->x = X座標;
        this->y = Y座標;
        this->CulParam();
    }
    
    void MultiZoom(double X倍率 , double Y倍率)
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

    void Move(double X移動量 , double Y移動量 )
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

    bool Hit(const Shape *shape) const
    {
        return shape->Hit( this );
    }
    bool Hit(const Complex *complex) const
    {
        for( auto it : complex->shapes )
        {
            if( it->Hit( this ) ) return true;
        }
        return false;
    }
    bool Hit(const Point *point) const
    {
        return LinePoint( point->GetX() , point->GetY() , this->GetThick() );
    }
    bool Hit(const Line *line) const
    {
            //四角形でラフチェック
            if( RectRect(this->GetXA() - this->GetThickHarf() ,this->GetYA() - this->GetThickHarf() , this->GetXB() - line->GetThickHarf() , this->GetYB() - line->GetThickHarf() ,
                            line->GetXA() - this->GetThickHarf() ,line->GetYA() - this->GetThickHarf() , line->GetXB() - line->GetThickHarf() , line->GetYB() - line->GetThickHarf() ) )
            {
                return true;
            }
            //交差チェック
            if( LineLine(this->GetXA() ,this->GetYA() ,this->GetXB() ,this->GetYB() ,line->GetXA(),line->GetYA(),line->GetXB(),line->GetYB() ) )
            {
                return true;
            }
            //線と端のチェック
            //線が点になっているかで分ける
            if( this->GetLength() != 0)
            {
                if( this->LinePoint( line->GetXA() , line->GetYA() , this->GetThickHarf() + line->GetThickHarf() ) ) return true;
                if( this->LinePoint( line->GetXB() , line->GetYB() , this->GetThickHarf() + line->GetThickHarf() ) ) return true;    
            }
            if( line->GetLength() != 0 )
            {
                if( line->LinePoint( this->GetXA() , this->GetYA() , this->GetThickHarf() + line->GetThickHarf() ) ) return true;
                if( line->LinePoint( this->GetXB() , this->GetYB() , this->GetThickHarf() + line->GetThickHarf() ) ) return true;    
            }

            return false;
    }
    bool Hit(const Rect *rect) const;
    bool Hit(const Circle *circle) const;
    
    /** 線と点の当たり判定.*/
    bool LinePoint(double px , double py , double range ) const
    {
        //点同士の距離
        const double dx = GetXB() - GetXA();
        const double dy = GetYB() - GetYA();

        const double a = dx * dx + dy * dy;
        const double b = dx *(GetXA() - px) + dy *(GetYA() - py);

        //点の場合
        if (a == 0)
        {
            if( 
                ( GetXA() - px ) *( GetXA() - px ) +
                ( GetYA() - py ) *( GetYA() - py )
                < range * range ) return true;
            return false;
        }

        const double t = -b / a;

        const double tx = GetXA() + dx*t;
        const double ty = GetYA() + dy*t;

        //線分上の点が範囲内かチェック
        if ( tx < minX || tx > maxX || ty < minY ||    ty > maxY)
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
/**    \include ShapeSample.h*/
class Rect : public Shape
{
public:
    double x;
    double y;

    double widthLeft;
    double widthRight;

    double heightUp;
    double heightDown;

    /*座標と大きさを指定*/
    /*デフォルト引数だと左上座標と大きさを指定*/
    /*横幅A=横幅B,高さA=高さBとすると中心座標指定になる*/
    Rect(double X座標,double Y座標,double 横幅A ,double 高さA, double 横幅B = 0 , double 高さB = 0):
        x(X座標),
        y(Y座標),
        heightUp( 高さB ),
        heightDown( 高さA ),
        widthLeft( 横幅B ),
        widthRight( 横幅A )
    {}

    virtual Shape* Clone(double X座標,double Y座標) const
    {
        auto shape = new Rect( X座標 , Y座標 , widthRight , heightDown , widthLeft , heightUp );
        shape->zoomX = this->zoomX;
        shape->zoomY = this->zoomY;
        return shape;
    }
            
    void SetPos(double X座標 , double Y座標)
    {
        this->x = X座標;
        this->y = Y座標;
    }

    void Move(double X移動量 , double Y移動量 )
    {
        this->x += X移動量;
        this->y += Y移動量;
    }

    void MultiZoom(double X倍率 , double Y倍率)
    {
        widthLeft *= X倍率;
        widthRight *= X倍率;

        heightUp *= Y倍率;
        heightDown *= Y倍率;
    }

    void Rotate(double 回転する角度){}

    void SetAngle(double 指定角度){}

    void Draw( Color 描画色 , int 透過率 , Camera *座標変換Camera = nullptr) const;

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
            
    bool Hit(const Shape *shape) const
    {
        return shape->Hit( this );
    }
    bool Hit(const Complex *complex) const
    {
        for( auto it : complex->shapes )
        {
            if( it->Hit( this ) ) return true;
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
        if( LineLine( line->GetXA() , line->GetYA() , line->GetXB() , line->GetYB()
                    ,  this->GetLeft() - int(line->GetThickHarf() * 0.7) , this->GetTop() - int(line->GetThickHarf() * 0.7) , this->GetRight() + int(line->GetThickHarf() * 0.7) , this->GetBottom() + int(line->GetThickHarf() * 0.7)  ))
        {
            return true;
        }

        if( LineLine( line->GetXA() , line->GetYA() , line->GetXB() , line->GetYB()
                    , this->GetRight() + int(line->GetThickHarf() * 0.7)  , this->GetTop() - int(line->GetThickHarf() * 0.7) , this->GetLeft() - int(line->GetThickHarf() * 0.7) , this->GetBottom() + int(line->GetThickHarf() * 0.7) ))
        {
            return true;
        }

        //端の丸い所以外判定
        if( 
            line->GetXA() + line->GetThickHarf() > this->GetLeft() && line->GetXA() - line->GetThickHarf() < this->GetRight() &&
            line->GetYA() + line->GetThickHarf() > this->GetTop() && line->GetYA() - line->GetThickHarf() < this->GetBottom() 
            )
        {
                //端の丸い所判定
                if(          line->GetXA() < this->GetLeft()                && line->GetYA() < this->GetTop() )
                {//左上
                    
                    if( (line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
                        (line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow() ) return true;
                    
                }
                else if( line->GetXA() > this->GetRight() && line->GetYA() < this->GetTop() )
                {//右上
                    
                    if( (line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
                        (line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow() ) return true;

                }
                else if( line->GetXA() < this->GetLeft()                && line->GetYA() > this->GetBottom() )
                {//左下
                    
                    if( (line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
                        (line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow() ) return true;
                    
                }
                else if( line->GetXA() > this->GetRight() && line->GetYA() > this->GetBottom() )
                {//右下

                    if( (line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
                        (line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow() ) return true;
                    
                }
                else
                {    
                    return true;
                }
        }

        if( 
            line->GetXB() + line->GetThickHarf()  > this->GetLeft() && line->GetXB() - line->GetThickHarf() < this->GetRight() &&
            line->GetYB() + line->GetThickHarf()  > this->GetTop() && line->GetYB() - line->GetThickHarf() < this->GetBottom()
            )
        {
            //端の丸い所判定
            if(          line->GetXB() < this->GetLeft()                && line->GetYB() < this->GetTop() )
            {//左上
                if( (line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
                    (line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow() ) return true;
                    
            }
            else if( line->GetXB() > this->GetRight() && line->GetYB() < this->GetTop() )
            {//右上
                    
                if( (line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
                    (line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow() ) return true;

            }
            else if( line->GetXB() < this->GetLeft()                && line->GetYB() > this->GetBottom() )
            {//左下
                    
                if( (line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
                    (line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow() ) return true;
                    
            }
            else if( line->GetXB() > this->GetRight() && line->GetYB() > this->GetBottom() )
            {//右下
                if( (line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
                    (line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow() ) return true;
                    
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
        return !(GetRight() < rect->GetLeft() || GetLeft() > rect->GetRight() || GetBottom() < rect->GetTop() || GetTop() > rect->GetBottom() );
    }
    bool Hit(const Circle *circle) const;
};

/** 円を表す図形クラス.*/
/**    \include ShapeSample.h*/
class Circle : public Shape
{
public:
    double x;
    double y;
    double radius;

    Circle( double X座標 , double Y座標 , double 半径):
        x(X座標),
        y(Y座標),
        radius(半径)
    {}

    Shape* Clone(double X座標,double Y座標) const
    {
        auto shape = new Circle( X座標 , Y座標 , this->radius );
        shape->zoomX = this->zoomX;
        shape->zoomY = this->zoomY;
        return shape;
    }

    void SetPos(double X座標 , double Y座標 )
    {
        this->x = X座標;
        this->y = Y座標;
    }

    void MultiZoom(double 倍率X , double 倍率Y)
    {
        this->radius *= 倍率X;

        zoomX *= 倍率X;
        zoomY *= 倍率Y;
    }

    void Rotate(double 回転する角度){}

    void SetAngle(double 指定角度){}

    void Move(double X移動量 , double Y移動量 )
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
        return int(radius*2);
    }

    double GetH() const
    {
        return int(radius*2);
    }

    void Draw( Color 描画色 , int 透過率 , Camera *座標変換Camera = nullptr) const;
            
    bool Hit(const Shape *shape) const
    {
        return shape->Hit( this );
    }
    bool Hit(const Complex *complex) const
    {
        for( auto it : complex->shapes )
        {
            if( it->Hit( this ) ) return true;
        }
        return false;
    }
    bool Hit(const Point *point) const
    {
        return
        (
            ( point->x - this->x ) * ( point->x - this->x )  +
            ( point->y - this->y ) * ( point->y - this->y )
            <=
            ( this->radius * this->radius )
        );
    }
    bool Hit(const Line *line) const
    {
        return line->LinePoint( x , y , (line->GetThickHarf() + radius) );
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
                    )&&(
                        this->x - this->radius <= rect->GetRight()
                    )
                )&&(
                    (
                        this->y >= rect->GetTop()
                    )&&(
                        this->y <= rect->GetBottom()
                    )
                )
            ) || (
                (
                    (
                        this->x >= rect->GetLeft()
                    )&&(
                        this->x <= rect->GetRight()
                    )                                    
                )&&(
                    (
                        this->y + this->radius >= rect->GetTop()
                    )&&(
                        this->y - this->radius <= rect->GetBottom()
                    )
                )
            ) || (//四角形の四隅と円の判定
                (this->x - rect->GetLeft() ) * (this->x - rect->GetLeft() ) +
                (this->y - rect->GetTop() ) * (this->y - rect->GetTop() ) <=
                (this->radius * this->radius )
            ) || (
                (this->x - rect->GetRight()) * (this->x - rect->GetRight()) +
                (this->y - rect->GetTop() ) * (this->y - rect->GetTop() ) <=
                (this->radius * this->radius )
            ) || (
                (this->x - rect->GetLeft()) * (this->x - rect->GetLeft()) +
                (this->y - rect->GetBottom()) * (this->y -rect->GetBottom()) <=
                (this->radius * this->radius )
            ) || (
                (this->x - rect->GetRight()) * (this->x - rect->GetRight()) +
                (this->y - rect->GetBottom()) * (this->y - rect->GetBottom()) <=
                (this->radius * this->radius )
            )
        );
    }
};
}