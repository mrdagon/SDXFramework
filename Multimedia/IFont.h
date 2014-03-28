#pragma once//☀SDL
#include <Multimedia/Color.h>
#include <Utility/VariadicStream.h>

namespace SDX
{
/** Font,BmpFont等のインターフェース.*/
/**    \include FontSample.h*/
class IFont
{
public:
    /** 文字を描画.*/
    virtual bool Draw(int X座標 , int Y座標 ,  Color 色 , VariadicStream 描画する文字列 ) const = 0;
    /** 文字をマスク[DXLIB].*/
    virtual bool ZMask(int X座標, int Y座標, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列) const = 0;
    
    /** 文字を回転して描画.*/
    virtual bool DrawRotate(int X座標, int Y座標, double 拡大率, double 角度 , Color 描画色 , bool 反転フラグ, VariadicStream 描画する文字列) const = 0;

    /** 文字を回転してマスク[DXLIB].*/
    virtual bool ZMaskRotate(int X座標, int Y座標, double 拡大率, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ, VariadicStream 描画する文字列) const = 0;

    /** 拡大率を指定して文字を描画.*/
    virtual bool DrawExtend(int X座標, int Y座標, double X軸拡大率, double Y軸拡大率, Color 色, VariadicStream 描画する文字列) const = 0;
    /** 拡大率を指定して文字をマスク[DXLIB].*/
    virtual bool ZMaskExtend(int X座標, int Y座標, double X軸拡大率, double Y軸拡大率, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列) const = 0;
};
}