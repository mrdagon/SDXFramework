//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] GNU Affero General Public License, version 3
#pragma once
namespace SDX
{
    bool Complex::Hit(const Point *point) const
    {
        return point->Hit( this );
    }
    bool Complex::Hit(const Line *line) const
    {
        return line->Hit( this );
    }
    bool Complex::Hit(const Rect *rect) const
    {
        return rect->Hit( this );
    }
    bool Complex::Hit(const Circle *circle) const
    {
        return circle->Hit( this );
    }
    bool Point::Hit(const Line *line) const
    {
        return line->Hit( this );
    }
    bool Point::Hit(const Rect *rect) const
    {
        return rect->Hit( this );
    }
    bool Point::Hit(const Circle *circle) const
    {
        return circle->Hit( this );
    }

    bool Line::Hit(const Rect *rect) const
    {
        return rect->Hit( this );
    }
    bool Line::Hit(const Circle *circle) const
    {
        return circle->Hit( this );
    }
    
    bool Rect::Hit(const Circle *circle) const
    {
        return circle->Hit( this );
    }
}