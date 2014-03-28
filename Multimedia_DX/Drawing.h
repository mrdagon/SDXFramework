#pragma once//☀DXLIB
#include<Multimedia/SDX.h>
#include<Multimedia/Color.h>
#include<Multimedia/Image.h>
#include<Multimedia/Font.h>
#include<Utility/VariadicStream.h>

namespace SDX
{
/** リソースを読み込まずに描画を行う関数群.*/
/**	\include DrawingSample.h*/
class Drawing
{
private:
	Drawing();
	~Drawing();

public:

    /** デフォルトのフォントを設定する.*/
    static void SetDefaultFont( const char* フォント名 , int 大きさ)
    {
        DxLib::ChangeFont( フォント名 );    
        DxLib::SetFontSize( 大きさ );
    }

	/** 始点と終点を結ぶ直線を描画.*/
    /** SDLは太さ指定不可*/
	static bool Line(int 始点X, int 始点Y, int 終点X, int 終点Y, Color 色, int 太さ)
	{
		return !DxLib::DrawLine( 始点X , 始点Y , 終点X , 終点Y , 色 , 太さ );
	}

	/** 左上の座標と大きさを指定して矩形を描画.*/
	static bool Rect(int 座標X, int 座標Y, int 幅, int 高さ, Color 色, bool 塗りつぶしフラグ)
	{
		return !DxLib::DrawBox( 座標X , 座標Y , 座標X + 幅 , 座標Y + 高さ , 色 , 塗りつぶしフラグ );
	}
	/** 左上の座標と大きさを指定して矩形をマスク[DXLIB].*/
	static bool RectZMask(int 座標X, int 座標Y, int 幅, int 高さ, ZMaskType マスクタイプ, bool 塗りつぶしフラグ)
	{
		return !DxLib::DrawBoxToZBuffer( 座標X, 座標Y, 座標X + 幅, 座標Y + 高さ, 塗りつぶしフラグ, (int)マスクタイプ);
	}

	/** 中心と半径を指定して円を描画.*/
    /** SDLは仮実装*/
	static bool Circle(int 中心X, int 中心Y, int 半径, Color 色, bool 塗りつぶしフラグ)
	{
		return !DxLib::DrawCircle( 中心X , 中心Y , 半径 , 色 , 塗りつぶしフラグ );
	}

	/** 中心と半径を指定して円をマスク[DXLIB].*/
	static bool CircleZMask(int 中心X, int 中心Y, int 半径, Color 色, bool 塗りつぶしフラグ)
	{
		return !DxLib::DrawCircleToZBuffer( 中心X , 中心Y , 半径 , 塗りつぶしフラグ , DX_ZWRITE_MASK );			
	}

	/** 中心と外接する四角形の大きさを指定して楕円を描画[DXLIB].*/
    /** SDLは仮実装*/
	static bool Oval( int 中心X , int 中心Y , int 幅 , int 高さ , Color 色 , bool 塗りつぶしフラグ )
	{
		return !DxLib::DrawOval( 中心X , 中心Y , 幅 , 高さ , 色 , 塗りつぶしフラグ );
	}

	/** 頂点を３つ指定して三角形を描画.*/
    /** SDLは塗りつぶし不可*/
	static bool Triangle(int 頂点aX, int 頂点aY, int 頂点bX, int 頂点bY, int 頂点cX, int 頂点cY, Color 色, bool 塗りつぶしフラグ)
	{
		return !DxLib::DrawTriangle( 頂点aX , 頂点aY , 頂点bX , 頂点bY , 頂点cX , 頂点cY , 色 , 塗りつぶしフラグ);
	}

	/** 指定座標に点を描画.*/
	static bool Pixel(int 座標X, int 座標Y, Color 色)
	{
		return !DxLib::DrawPixel( 座標X , 座標Y , 色 );
	}

	/** 指定座標の色を取得[DXLIB].*/
	static ColorData GetPixel( int 座標X , int 座標Y )
	{
		return DxLib::GetPixel( 座標X , 座標Y );
	}

	/** 画像を一時的にメモリに読み込んで描画.*/
	/** この処理は重いので、通常はImageクラスを利用する*/
	static bool ImageFile( int 座標X , int 座標Y , const char *ファイル名 , bool 透過フラグ = true )
	{
		return !DxLib::LoadGraphScreen( 座標X , 座標Y , ファイル名 , 透過フラグ);
	}

	/** 文字を描画.*/
	/** フォントはデフォルトでゴシック体*/
	static void String(int X座標, int Y座標, Color 色, VariadicStream 描画する文字列)
	{
		for(auto it : 描画する文字列.StringS)
		{
			DxLib::DrawString( X座標 , Y座標 , it.c_str() , 色 );
			Y座標 += 20;
		}
	}
	/** 文字をマスク[DXLIB].*/
	static void StringZMask( int X座標 , int Y座標 , ZMaskType Zマスク , VariadicStream 描画する文字列 )
	{
		for (auto it : 描画する文字列.StringS)
		{
			DxLib::DrawStringToZBuffer( X座標 , Y座標 , it.c_str() , (int)Zマスク);
			Y座標 += 20;
		}

	}
};
}