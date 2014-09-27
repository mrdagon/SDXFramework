//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] GNU Affero General Public License, version 3
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Framework/Shape.h>

namespace SDX
{

/** ブレンドモード.*/
enum class BlendMode
{
    NoBlend = SDL_BLENDMODE_NONE,
    Alpha = SDL_BLENDMODE_BLEND,
    Add = SDL_BLENDMODE_ADD,
    Mula = SDL_BLENDMODE_MOD
};

class Image;

/** 描画先を表すクラス.*/
/** 実装中.*/
/** \include ScreenSample.*/
class Renderer
{
private:
	RendererHandle handle = 0;
public:
	/*描画ハンドルを取得*/
	RendererHandle GetHandle()
	{
		return handle;
	}

	~Renderer()
	{
		Destroy();
	}

	/*Rendererを生成*/
	void Create(WindowHandle 元Window)
	{
		handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC);
	}

	/*Rendererを削除*/
	bool Destroy()
	{
		if (handle == 0) return false;
		SDL_DestroyRenderer(handle);
		return true;
	}
};

/** 描画先を表すクラス.*/
/** \include ScreenSample.h*/
class Screen
{
private:
    Screen(){};
    ~Screen(){};
	RendererHandle handle = 0;//現在の描画先

public:
    BlendMode nowBlendMode = BlendMode::NoBlend;
    int blendParam = 0;
    Color clearColor = Color(0, 0, 0);//消去時の色
    Color rgba = Color(255, 255, 255, 0);//描画輝度と透明度

    /** シングルトンなインスタンスを取得.*/
    static Screen& Single()
    {
        static Screen single;
        return single;
    }

    /** スクリーンハンドルを取得.*/
	static RendererHandle GetHandle()
    {
        return Single().handle;
    }

    /** スクリーンハンドルを設定.*/
	static void SetRenderer(Renderer &描画先Renderer)
    {
        Single().handle = 描画先Renderer.GetHandle();
    }

    /** 描画範囲を設定する、設定範囲外には描画されない[未実装].*/
    static bool SetArea(const Rect &描画領域)
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
        
    /** ブレンド描画のモードを設定.*/
    static bool SetBlendMode(BlendMode ブレンドモード,int 設定値)
    {
        Single().nowBlendMode = ブレンドモード;
        if(設定値 > 255)      Single().blendParam = 255;
        else if(設定値 < 0)      Single().blendParam = 0;
        else                   Single().blendParam = 設定値;

        return true;
    }
    
    /** 描画対象になっている画面の一部をBMP形式で保存[未実装].*/
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

    /** 透過色を設定[未実装].*/
    static bool SetTransColor(Color 輝度)
    {
        return false;
    }

};
}