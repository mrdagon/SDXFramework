//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once

namespace SDX
{
/** 色を表すクラス.*/
/** \include ColorSample.h*/
class Color
{
private:
    ColorData data;
public :
    /** RGB値から色に変換.*/
    /** 赤、緑、青の各要素は0～255で指定する*/
    Color(int 赤,int 緑,int 青 , int 透過率 = 255)
    {
        SetColor(赤,緑,青,透過率);
    }

    void SetColor(int 赤, int 緑, int 青, int 透過率 = 255)
    {
        data = { (Uint8)赤, (Uint8)緑, (Uint8)青, (Uint8)透過率 };
    }

    /** 赤の要素を取得.*/
    int GetRed() const
    {
        return data.r;
    }

    /** 緑の要素を取得.*/
    int GetGreen() const
    {
        return data.g;
    }

    /** 青の要素を取得.*/
    int GetBlue() const
    {
        return data.b;
    }

    /** 透明度を取得.*/
    int GetAlpha() const
    {
        return data.a;
    }

    operator ColorData()
    {
        return data;
    }

    bool operator==(Color 比較色) {
        return (
            GetRed() == 比較色.GetRed() &&
            GetBlue() == 比較色.GetBlue() &&
            GetGreen() == 比較色.GetGreen() &&
            GetAlpha() == 比較色.GetAlpha()
            );
    }

    static const Color Black;
    static const Color Dilver;
    static const Color Gray;
    static const Color White;
    static const Color Maroon;
    static const Color Red;
    static const Color Purple;
    static const Color Fuchsia;
    static const Color Green;
    static const Color Lime;
    static const Color Olive;
    static const Color Yellow;
    static const Color Navy;
    static const Color Blue;
    static const Color Teal;
    static const Color Aqua;
};

}