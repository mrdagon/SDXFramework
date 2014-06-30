#pragma once//☀SDL
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Framework/Shape.h>

namespace SDX
{
/** 補完の方法.*/
enum class DrawMode
{
    Nearest,//!< ニアレストネイバー法
    Bilinear,//!< バイリニア法
};
    
/** ブレンドモード.*/
enum class BlendMode
{
    NoBlend = SDL_BLENDMODE_NONE,
    Alpha = SDL_BLENDMODE_BLEND,
    Add = SDL_BLENDMODE_ADD,
    Sub,
    Mula = SDL_BLENDMODE_MOD,
    Invsrc
};

class Image;
/** 描画先を表すクラス.*/
/**    \include ScreenSample.h*/
class Screen
{
private:
    Screen(){};
    ~Screen(){};
    ScreenHandle handle = 0;
public:

    BlendMode nowBlendMode = BlendMode::NoBlend;
    int          blendParam = 0;
    Color clearColor = Color(0, 0, 0);//消去時の色
    Color rgba = Color(255, 255, 255, 0);//描画輝度と透明度

    /** シングルトンなインスタンスを取得.*/
    static Screen& Single()
    {
        static Screen single;
        return single;
    }

    /** スクリーンハンドルを取得.*/
    static ScreenHandle GetHandle()
    {
        return Single().handle;
    }

    /** スクリーンハンドルを設定.*/
    static void SetRenderer(ScreenHandle handle)
    {
        Single().handle = handle;
    }

    /** 描画範囲を設定する、設定範囲外には描画されない[DXLIB].*/
    static bool SetArea(const Rect &描画領域)
    {
        return false;
    }
    
    /** 作成する画像のビット深度を設定[DXLIB].*/
    /** 画像を読み込む時のビット深度を下げると、画質が下がる代わりに\n
        使用するメモリが減少します\n
        この関数は、Image::Load等で画像を読み込む前に呼ぶ必要がある*/
    static bool SetCreateGraphColorBitDepth(int ビット深度)
    {
        return false;
    }
    
    /** スクリーン用Imageのチャンネル数を設定[DXLIB].*/
    /**    チャンネル数は1,2,4のいずれかを指定\n
        スクリーン用Imageが指定したチャンネル数で作成されるようになる\n
        Image::Make関数を呼ぶ前に、この関数を呼ぶ必要がある*/
    static bool SetCreateValidGraphChannelNum(int チャンネル数)
    {
        return false;
    }
    
    /** 描画先の設定[DXLIB].*/
    /**    Image::Draw等の描画先を裏画面にする。\n
        SetImageを使用してから戻す時に使う*/
    static bool SetBack()
    {
        return false;
    }
    
    /** Screen::Clear後の色を設定.*/
    static bool SetBackColor( Color 背景色 )
    {
        Single().clearColor.SetColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue());

        return true;
    }
    
    /** 描画内容を反映.*/
    static bool Flip()
    {
        SDL_RenderPresent(GetHandle());
        return true;
    }
    
    /** 裏画面の内容を、表画面にコピー.*/
    static bool Copy()
    {
        SDL_RenderPresent(GetHandle());
        return true;
    }
    
    /** 画面を消去する.*/
    static bool Clear()
    {
        SDL_SetRenderDrawColor
        (
            Screen::GetHandle(),
            Single().clearColor.GetRed(),
            Single().clearColor.GetGreen(),
            Single().clearColor.GetBlue(),
            0
        );
        SDL_RenderClear(GetHandle());
        return true;
    }
    
    /** 拡大描画の補完方法を設定[DXLIB].*/
    static bool SetMode(DrawMode 補完モード)
    {
        return false;
    }
    
    /** ブレンド描画のモードを設定.*/
    static bool SetBlendMode(BlendMode ブレンドモード,int 設定値)
    {
        Single().nowBlendMode = ブレンドモード;
        if(設定値 > 255)      Single().blendParam = 255;
        else if(設定値 < 0)      Single().blendParam = 0;
        else                   Single().blendParam = 設定値;

        return true;
    }
    
    /** 描画対象になっている画面の一部をBMP形式で保存[DXLIB].*/
    static bool SaveBmp(const Rect &領域 , const char *ファイル名 )
    {
        return false;
    }

    /** 描画輝度を設定.*/
    static bool SetBright( Color 輝度 )
    {
        Single().rgba.SetColor(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
        return true;
    }

    /** 透過色を設定[DXLIB].*/
    static bool SetTransColor(Color 輝度)
    {
        return false;
    }
    
    /** Zバッファ使用フラグを設定[DXLIB].*/
    static void SetZUse(bool 使用フラグ )
    {
        return;
    }
        
    /** Zバッファ描画フラグを設定[DXLIB].*/
    static void SetZWrite(bool 使用フラグ )
    {
        return;
    }

    /** Z描画深度0.0～1.0の範囲で設定[DXLIB].*/
    static void SetZDepth(double Z深度)
    {
        return;
    }
};
}