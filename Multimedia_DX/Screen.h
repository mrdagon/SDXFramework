﻿#pragma once//☀DXLIB
#include<Multimedia/SDX.h>
#include<Multimedia/Color.h>

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
	NoBlend,//!< ブレンドしない
	Alpha,//!< αブレンド
	Add,//!< 加算ブレンド
	Sub,//!< 
	Mula,//!< 
	Invsrc//!< 
};

class Image;
/** 描画先を表すクラス.*/
/**	\include ScreenSample.h*/
class Screen
{
private:
	Screen(){};
	~Screen(){};
	ScreenHandle handle = 0;
public:

	BlendMode nowBlendMode = BlendMode::NoBlend;
	int		  blendParam = 0;
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
	static bool SetArea(int 座標X , int 座標Y , int 幅 , int 高さ)
	{
		return !DxLib::SetDrawArea( 座標X , 座標Y, 座標X + 幅, 座標Y + 高さ);
	}
	
	/** 作成する画像のビット深度を設定[DXLIB].*/
	/** 画像を読み込む時のビット深度を下げると、画質が下がる代わりに\n
		使用するメモリが減少します\n
		この関数は、Image::Load等で画像を読み込む前に呼ぶ必要がある*/
	static bool SetCreateGraphColorBitDepth(int ビット深度)
	{
		return !DxLib::SetCreateGraphColorBitDepth(ビット深度);
	}
	
	/** スクリーン用Imageのチャンネル数を設定[DXLIB].*/
	/**	チャンネル数は1,2,4のいずれかを指定\n
		スクリーン用Imageが指定したチャンネル数で作成されるようになる\n
		Image::Make関数を呼ぶ前に、この関数を呼ぶ必要がある*/
	static bool SetCreateValidGraphChannelNum(int チャンネル数)
	{
		return !DxLib::SetCreateDrawValidGraphChannelNum(チャンネル数);
	}
	
	/** 描画先の設定[DXLIB].*/
	/**	Image::Draw等の描画先を裏画面にする。\n
		SetImageを使用してから戻す時に使う*/
	static bool SetBack()
	{
		return !DxLib::SetDrawScreen(DX_SCREEN_BACK);
	}
	
	/** Screen::Clear後の色を設定.*/
	static bool SetBackColor( Color 背景色 )
	{
		Single().clearColor.SetColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue());

		return !DxLib::SetBackgroundColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue() );
	}
	
	/** 描画内容を反映.*/
	static bool Flip()
	{
		return !DxLib::ScreenFlip();
	}
	
	/** 裏画面の内容を、表画面にコピー.*/
	static bool Copy()
	{
		return !DxLib::ScreenCopy();
	}
	
	/** 画面を消去する.*/
	static bool Clear()
	{
		return !DxLib::ClearDrawScreen();
	}
	
	/** 拡大描画の補完方法を設定[DXLIB].*/
	static bool SetMode(DrawMode 補完モード)
	{
		return !DxLib::SetDrawMode((int)補完モード);
	}
	
	/** ブレンド描画のモードを設定.*/
	static bool SetBlendMode(BlendMode ブレンドモード,int 設定値)
	{
		Single().nowBlendMode = ブレンドモード;
		if(設定値 > 255)	  Single().blendParam = 255;
		else if(設定値 < 0)	  Single().blendParam = 0;
		else 				  Single().blendParam = 設定値;

		return !DxLib::SetDrawBlendMode((int)ブレンドモード, 設定値);
	}
	
	/** 描画対象になっている画面の一部をBMP形式で保存[DXLIB].*/
	static bool SaveBmp(int 座標X, int 座標Y , int 幅 , int 高さ , const char *ファイル名 )
	{
		return !DxLib::SaveDrawScreen(座標X, 座標Y, 幅, 高さ, ファイル名);
	}

	/** 描画輝度を設定.*/
	static bool SetBright( Color 輝度 )
	{
		return !DxLib::SetDrawBright(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
	}

	/** 透過色を設定[DXLIB].*/
	static bool SetTransColor(Color 輝度)
	{
		return !DxLib::SetTransColor(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
	}
	
	/** Zバッファ使用フラグを設定[DXLIB].*/
	static void SetZUse(bool 使用フラグ )
	{
		DxLib::SetUseZBufferFlag(使用フラグ);
	}
		
	/** Zバッファ描画フラグを設定[DXLIB].*/
	static void SetZWrite(bool 使用フラグ )
	{
		DxLib::SetWriteZBufferFlag(使用フラグ);
	}

	/** Z描画深度0.0～1.0の範囲で設定[DXLIB].*/
	static void SetZDepth(double Z深度)
	{
		DxLib::SetDrawZ((float)Z深度);
	}
};
}