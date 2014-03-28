#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/IFont.h>
#include <Multimedia/SystemFont.h>
#include <Multimedia/Image.h>
#include <Multimedia/Window.h>

namespace SDX
{
/** フォントの種類.*/
enum class FontType
{
	Normal		   = DX_FONTTYPE_NORMAL,//!< 
	Edge		   = DX_FONTTYPE_EDGE,//!< 
	AntiAliase	   = DX_FONTTYPE_ANTIALIASING,//!< 
	AntiAliaseEdge = DX_FONTTYPE_ANTIALIASING_EDGE,//!< 
};


/** フォントデータを表すクラス.*/
/**	\include FontSample.h*/
class Font : public IFont
{
private:
	FontHandle handle = NULL_HANDLE;
	int size = 0;
	int thick = 0;
	int enterHeight = 0;
public:
	Font(){}
	
	Font(const char *フォント名,int 大きさ ,int 太さ = 1 , int 改行高さ = 0 , FontType フォントタイプ = FontType::Normal)
	{
		Font::Load( フォント名 , 大きさ , 太さ , 改行高さ , フォントタイプ);
	}

	/** メモリ上にフォントを作成する.*/
	/**	太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n
		改行高さは0の場合、改行後の文字が上下くっつく。
		SDLとDXLIBではフォント名の指定方法が違うので注意。
        SDLでは太さとフォントタイプが無効*/
	bool Load(const char *フォント名,int 大きさ ,int 太さ = 1 , int 改行高さ = 0, FontType フォントタイプ = FontType::Normal)
	{
		Release();
		this->size = 大きさ;
		this->enterHeight = 改行高さ + 大きさ;
		this->thick = 太さ;

		this->handle = DxLib::CreateFontToHandle(フォント名,大きさ,太さ,(int)フォントタイプ);
		return ( handle != -1 );
	}
			
	/** フォントをメモリから開放する.*/
	bool Release() const
	{
		if(handle != NULL_HANDLE) return false;
		return !DxLib::DeleteFontToHandle(this->handle);
	}
			
	/** フォントのハンドルを取得.*/
	FontHandle GetHandle() const
	{
		return handle;
	}
	
    /** フォントから画像を生成*/
    Image MakeImage(Color 文字色, bool 反転フラグ, VariadicStream 描画する文字列) const
    {
        Image image;
        int 幅   = GetDrawStringWidth(描画する文字列);
        int 高さ = ((int)描画する文字列.StringS.size()-1) * enterHeight + size;
        int Y座標 = 0;
        const int softImage = DxLib::MakeARGB8ColorSoftImage( 幅 , 高さ);
        DxLib::FillSoftImage(softImage, 0, 0, 0, 0);

        for (auto it : 描画する文字列.StringS)
        {
            //文字イメージの作成
            DxLib::BltStringSoftImageToHandle(0, Y座標, it.c_str(), softImage, -1, this->handle);
            Y座標 += this->enterHeight;
        }
        image.handle = CreateGraphFromSoftImage(softImage);
        image.width = 幅;
        image.height = 高さ;
        DxLib::DeleteSoftImage(softImage);

        return image;
    }

	/** 大きさを取得.*/
	int GetSize() const
	{
		return this->size;
	}
			
	/** 太さを取得.*/
	int Getthick() const
	{
		return this->thick;
	}
			
	/** 描画時の幅を取得[DXLIB].*/
	int GetDrawStringWidth( VariadicStream 幅を計算する文字列 ) const
	{
        int 幅 = 0;

        for (auto it : 幅を計算する文字列.StringS)
        {
            幅 = std::max( 幅 , DxLib::GetDrawStringWidthToHandle(it.c_str(), strlen(it.c_str()), this->handle) );
        }

        return 幅;
	}

	/** 文字を描画.*/
	bool Draw(int X座標, int Y座標, Color 色, VariadicStream 描画する文字列) const
	{
		for (auto it:描画する文字列.StringS)
		{
			DxLib::DrawStringToHandle(X座標, Y座標, it.c_str() , 色, handle);
			Y座標 += this->enterHeight;
		}

		return true;
	}
	/** 文字をマスク[DXLIB].*/
	bool ZMask(int X座標, int Y座標, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列 ) const
	{
		return false;
	}
	
    /** 文字を回転して描画.*/
    /** 呼び出す度に画像イメージを作成するので処理は重い*/
    bool DrawRotate(int X座標, int Y座標, double 拡大率, double 角度, Color 描画色 , bool 反転フラグ, VariadicStream 描画する文字列) const
    {
        Image 文字イメージ = MakeImage(描画色, 反転フラグ, 描画する文字列);
		文字イメージ.DrawRotate(X座標,Y座標,拡大率,角度,反転フラグ);
		文字イメージ.Release();
        return true;
    }

    /** 文字を回転してマスク[DXLIB].*/
    bool ZMaskRotate(int X座標, int Y座標, double 拡大率, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ, VariadicStream 描画する文字列) const
    {
        Image 文字イメージ = MakeImage(Color::White, 反転フラグ, 描画する文字列);
		文字イメージ.ZMaskRotate(X座標, Y座標, 拡大率, 角度, Zマスクタイプ, 反転フラグ);
		文字イメージ.Release();
        return true;
    }

	/** 拡大率を指定して文字を描画.*/
	bool DrawExtend(int X座標, int Y座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const
	{
		for( auto it:描画する文字列.StringS )
		{
			DxLib::DrawExtendStringToHandle(X座標,Y座標,X拡大率 , Y拡大率 , it.c_str() , 描画色, handle );
			Y座標 += int( this->enterHeight * Y拡大率 );
		}

		return true;
	}		
	/** 拡大率を指定して文字をマスク[DXLIB].*/
	bool ZMaskExtend(int X座標, int Y座標, double X拡大率, double Y拡大率, ZMaskType Zマスクタイプ, VariadicStream 描画する文字列) const
	{
		for( auto it : 描画する文字列.StringS )
		{
			DxLib::DrawExtendStringToHandleToZBuffer(X座標, Y座標, X拡大率, Y拡大率, it.c_str() , handle, (int)Zマスクタイプ);
			Y座標 += this->enterHeight;
		}
		return true;
	}
};
}