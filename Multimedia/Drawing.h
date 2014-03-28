#pragma once//☀SDL
#include<Multimedia/SDX.h>
#include<Multimedia/Color.h>
#include<Multimedia/Image.h>
#include<Multimedia/Font.h>
#include<Utility/VariadicStream.h>

namespace SDX
{
/** リソースを読み込まずに描画を行う関数群.*/
/** \include DrawingSample.h*/
class Drawing
{
private:
    Drawing();
    ~Drawing();

    static Font defaultFont;//!< SDL用のフォントハンドル

    /**透過状態を計算する[SDL].*/
    static void RGBACulculate(int 赤 , int 緑 , int 青)
    {
        SDL_SetRenderDrawBlendMode(Screen::GetHandle(), (SDL_BlendMode)Screen::Single().nowBlendMode);
        SDL_SetRenderDrawColor
            (
                Screen::GetHandle(),
                Screen::Single().rgba.GetRed() * 赤 / 255,
                Screen::Single().rgba.GetGreen() * 緑 / 255,
                Screen::Single().rgba.GetBlue() * 青 / 255,
                Screen::Single().blendParam
            );
    }
    /**円のデータを作成する.*/
    static Image& circleTexture( bool 塗りつぶしフラグ)
    {
        static Image circleA;
        static Image circleB;

        if (circleA.handle == nullptr)
        {
            Font font;
            font.Load(SystemFont::Gothic, 1000);

            SDL_Surface* surfaceA = TTF_RenderUTF8_Blended( font.GetHandle(), "●", {255,255,255,255});
            circleA.handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), surfaceA);
            circleA.part.w = surfaceA->w;
            circleA.part.h = surfaceA->h;
            SDL_FreeSurface(surfaceA);

            SDL_Surface* surfaceB = TTF_RenderUTF8_Blended(font.GetHandle(), "○", { 255, 255, 255, 255 });
            circleB.handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), surfaceB);
            circleB.part.w = surfaceB->w;
            circleB.part.h = surfaceB->h;
            SDL_FreeSurface(surfaceB);

            font.Release();
        }

        if (塗りつぶしフラグ)
        {
            return circleA;
        }
        else
        {
            return circleB;
        }
    }

public:

    /** デフォルトのフォントを取得する[SDL].*/
    static Font& GetFont()
    {
        return defaultFont;
    }

    /** デフォルトのフォントを設定する.*/
    static void SetDefaultFont( const char* フォント名 , int 大きさ)
    {
        GetFont().Load(フォント名, 大きさ);
    }

    /** 始点と終点を結ぶ直線を描画.*/
    /** SDLは太さ指定不可*/
    static bool Line(int 始点X, int 始点Y, int 終点X, int 終点Y, Color 色, int 太さ)
    {
        RGBACulculate(色.GetRed() , 色.GetGreen() , 色.GetBlue() );
        return !SDL_RenderDrawLine(Screen::GetHandle(), 始点X, 始点Y, 終点X, 終点Y);
    }

    /** 左上の座標と大きさを指定して矩形を描画.*/
    static bool Rect(int 座標X, int 座標Y, int 幅, int 高さ, Color 色, bool 塗りつぶしフラグ)
    {
        SDL_Rect buf = { 座標X, 座標Y, 幅, 高さ };
        RGBACulculate(色.GetRed() , 色.GetGreen() , 色.GetBlue() );
        if (塗りつぶしフラグ)
        {
            return !SDL_RenderFillRect(Screen::GetHandle(), &buf);
        }else{
            return !SDL_RenderDrawRect(Screen::GetHandle(), &buf);
        }
    }
    /** 左上の座標と大きさを指定して矩形をマスク[DXLIB].*/
    static bool RectZMask(int 座標X, int 座標Y, int 幅, int 高さ, ZMaskType マスクタイプ, bool 塗りつぶしフラグ)
    {
        return false;
    }

    /** 中心と半径を指定して円を描画.*/
    /** SDLは仮実装*/
    static bool Circle(int 中心X, int 中心Y, int 半径, Color 色, bool 塗りつぶしフラグ)
    {
        SDL_SetRenderDrawColor(Screen::GetHandle(), 色.GetRed(), 色.GetGreen(), 色.GetBlue(), 0);
        circleTexture(塗りつぶしフラグ).DrawExtend(中心X - 半径, 中心Y - 半径, 中心X + 半径, 中心Y + 半径);
        return true;
    }

    /** 中心と半径を指定して円をマスク[DXLIB].*/
    static bool CircleZMask(int 中心X, int 中心Y, int 半径, Color 色, bool 塗りつぶしフラグ)
    {
        return false;
    }

    /** 中心と外接する四角形の大きさを指定して楕円を描画[DXLIB].*/
    /** SDLは仮実装*/
    static bool Oval( int 中心X , int 中心Y , int 幅 , int 高さ , Color 色 , bool 塗りつぶしフラグ )
    {
        SDL_SetRenderDrawColor(Screen::GetHandle(), 色.GetRed(), 色.GetGreen(), 色.GetBlue(), 0);
        circleTexture(塗りつぶしフラグ).DrawExtend(中心X - 幅/2, 中心Y - 高さ/2, 中心X + 幅/2, 中心Y + 高さ/2);
        return true;
    }

    /** 頂点を３つ指定して三角形を描画.*/
    /** SDLは塗りつぶし不可*/
    static bool Triangle(int 頂点aX, int 頂点aY, int 頂点bX, int 頂点bY, int 頂点cX, int 頂点cY, Color 色, bool 塗りつぶしフラグ)
    {
        RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
        SDL_RenderDrawLine(Screen::GetHandle(), 頂点aX , 頂点aY, 頂点bX, 頂点bY);
        SDL_RenderDrawLine(Screen::GetHandle(), 頂点bX, 頂点bY, 頂点cX, 頂点cY);
        SDL_RenderDrawLine(Screen::GetHandle(), 頂点cX, 頂点cY, 頂点aX, 頂点aY);
        return true;
    }

    /** 指定座標に点を描画.*/
    static bool Pixel(int 座標X, int 座標Y, Color 色)
    {
        RGBACulculate(色.GetRed() , 色.GetGreen() , 色.GetBlue() );
        SDL_RenderDrawPoint(Screen::GetHandle() ,座標X, 座標Y);
        return false;
    }

    /** 指定座標の色を取得[DXLIB].*/
    static ColorData GetPixel( int 座標X , int 座標Y )
    {
        return SDL_Color{ 0, 0, 0 };
    }

    /** 画像を一時的にメモリに読み込んで描画.*/
    /** この処理は重いので、通常はImageクラスを利用する*/
    static bool ImageFile( int 座標X , int 座標Y , const char *ファイル名 , bool 透過フラグ = true )
    {
        Image buf(ファイル名);
        buf.Draw(座標X , 座標Y , false);
        buf.Release();
        return true;
    }

    /** 文字を描画.*/
    /** フォントはデフォルトでゴシック体*/
    static void String(int X座標, int Y座標, Color 色, VariadicStream 描画する文字列)
    {
        defaultFont.Draw(X座標,Y座標,色 , 描画する文字列 );
    }
    /** 文字をマスク[DXLIB].*/
    static void StringZMask( int X座標 , int Y座標 , ZMaskType Zマスク , VariadicStream 描画する文字列 )
    {
        for (auto it : 描画する文字列.StringS)
        {
            Y座標 += 20;
        }
    }
};
}