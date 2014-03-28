#pragma once//☀DXLIB
#include<Multimedia/SDX.h>
#include<Multimedia/Screen.h>

namespace SDX
{
/** Zマスクの種類.*/
enum class ZMaskType
{
	Clear,//!< マスクを切り取る
	Mask,//!< マスクする
};

/** 説明.*/
enum class RGBA
{
	SrcR,
	SrcG,

	SrcB,
	SrcA,
	BlendR,
	BlendG,
	BlendB,
	BlendA,
};

/** 説明.*/
enum class ClipType
{
	Less   ,
	Greater,
};

/** 画像データを表すクラス.*/
/**	\include ImageSample.h*/
class Image
{
	friend class Anime;
	friend class ImagePack;
    friend class Font;
    friend class Drawing;
private:
	bool isScreen = false;
	bool isAlphaChannel = false;
	bool isTrans = true;//png等の透過フラグ

	int width = 0;
	int height = 0;

	ImageHandle handle = 0;

public:
	Image(){}

	Image(const char *ファイル名)
	{
		Load(ファイル名);
	}

	Image(Image& コピー元, int X頂点, int Y頂点, int 幅, int 高さ)
	{
		Copy(コピー元, X頂点, Y頂点, 幅, 高さ);
	}

	/** 空のイメージを作成.*/
	Image(int 幅 ,int 高さ  , bool スクリーン用フラグ , bool αチャンネルフラグ = true, bool 透過フラグ = true)
	{
		Make(幅, 高さ, スクリーン用フラグ, αチャンネルフラグ, 透過フラグ);
	}

	/** 画像をメモリへ読み込む.*/
	bool Load(const char *ファイル名)
	{
		if (this->handle != NULL_HANDLE) DxLib::DeleteGraph(this->handle);
		this->handle = DxLib::LoadGraph(ファイル名);
		this->isTrans = true;
		this->isScreen = false;

		DxLib::GetGraphSize( this->GetHandle() , &width , &height );
		return ( this->handle != -1 );
	}

	/** イメージをメモリから開放.*/
	bool Release()
	{
		return !DxLib::DeleteGraph(this->handle);
	}
	//bool 透過フラグ, bool スクリーン用フラグ, bool αチャンネルフラグ )

	/** 空のイメージを作成.*/			
	ImageHandle Make(int 幅, int 高さ, bool スクリーン用フラグ = false, bool αチャンネルフラグ = true, bool 透過フラグ = true)
	{
		Release();

		if (スクリーン用フラグ)
		{
			handle = DxLib::MakeScreen(幅, 高さ, αチャンネルフラグ);
		}else{
			handle = DxLib::MakeGraph(幅, 高さ);
		}
		DxLib::GetGraphSize( GetHandle() , &width , &height );

		isTrans = 透過フラグ;
		isScreen = スクリーン用フラグ;
		isAlphaChannel = αチャンネルフラグ;

		return handle;
	}

	/** 元イメージの一部をコピーして、別イメージを作成.*/
	ImageHandle Copy(const Image& 元イメージ, int X原点, int Y原点, int 幅, int 高さ)
	{
		this->handle = DxLib::DerivationGraph( X原点, Y原点, 幅, 高さ, 元イメージ.handle);
		this->width = 幅;
		this->height = 高さ;

		this->isTrans = 元イメージ.isTrans;
		this->isScreen = false;
		this->isAlphaChannel = false;

		return handle;
	}

	/** ハンドルを取得.*/
	ImageHandle GetHandle() const
	{
		return handle;
	}
	
	/** 指定座標に描画.*/
	bool Draw(int X座標,int Y座標 , bool 反転フラグ = false) const
	{
		if( 反転フラグ )
		{
			return !DxLib::DrawTurnGraph( X座標 , Y座標 , this->GetHandle() , this->isTrans );
		}else{					
			return !DxLib::DrawGraph( X座標 , Y座標 , this->GetHandle() , this->isTrans );
		}
	}
	/** 指定座標にマスク[DXLIB].*/
	bool ZMask(int X座標,int Y座標 , ZMaskType Zマスクタイプ ,  bool 反転フラグ = false) const
	{
		if (反転フラグ)
		{
			return !DxLib::DrawTurnGraphToZBuffer( X座標 , Y座標 , this->GetHandle() , (int)Zマスクタイプ );
		}
		else{
			return !DxLib::DrawGraphToZBuffer(X座標, Y座標, this->GetHandle(), (int)Zマスクタイプ);
		}
	}

	/** 指定矩形内に描画.*/
	bool DrawExtend(int X座標A,int Y座標A,int X座標B,int Y座標B ) const
	{
		return !DxLib::DrawExtendGraph(X座標A, Y座標A, X座標B, Y座標B, this->GetHandle(), this->isTrans);
	}
	/** 指定矩形内にマスク[DXLIB].*/
	bool ZMaskExtend(int X座標A,int Y座標A,int X座標B,int Y座標B  , ZMaskType Zマスクタイプ) const
	{
		return !DxLib::DrawExtendGraphToZBuffer(X座標A, Y座標A, X座標B, Y座標B, this->GetHandle(), (int)Zマスクタイプ);
	}
		
	/** 角度、拡大率を指定して描画.*/
	bool DrawRotate(int X座標, int Y座標, double 拡大率, double 角度, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraph(X座標, Y座標, 拡大率, 角度, this->GetHandle(), this->isTrans, 反転フラグ);
	}
	/** 角度、拡大率を指定してマスク[DXLIB].*/
	bool ZMaskRotate(int X座標, int Y座標, double 拡大率, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraphToZBuffer(X座標, Y座標, 拡大率, 角度, this->GetHandle(), (int)Zマスクタイプ, 反転フラグ);
	}

	/** 回転軸、角度、拡大率を指定して描画.*/
	bool DrawRotateAxis(int X座標, int Y座標, int X軸, int Y軸, double 拡大率, double 角度, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraph2(X座標, Y座標, X軸, Y軸, 拡大率, 角度, this->GetHandle(), this->isTrans, 反転フラグ);
	}
	/** 回転軸、角度、拡大率を指定してマスク[DXLIB].*/
	bool ZMaskRotateAxis(int X座標, int Y座標, int X軸, int Y軸, double 拡大率, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraph2ToZBuffer(X座標, Y座標, X軸, Y軸, 拡大率, 角度, this->GetHandle(), (int)Zマスクタイプ, 反転フラグ);
	}

	/** 回転軸、角度、拡大率を縦横別に指定して描画.*/
	bool DrawRotateAxis(int X座標, int Y座標, int X軸, int Y軸, double 拡大率X, double 拡大率Y, double 角度, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraph3(X座標, Y座標, X軸, Y軸, 拡大率X, 拡大率Y, 角度, this->GetHandle(), this->isTrans, 反転フラグ);
	}
	/** 回転軸、角度、拡大率を縦横別に指定してマスク[DXLIB].*/
	bool ZMaskRotateAxis(int X座標, int Y座標, int X軸, int Y軸, double 拡大率X, double 拡大率Y, double 角度, ZMaskType Zマスクタイプ, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRotaGraph3ToZBuffer(X座標, Y座標, X軸, Y軸, 拡大率X, 拡大率Y, 角度, this->GetHandle(), (int)Zマスクタイプ, 反転フラグ);
	}

	/** 四角形に変形描画[DXLIB].*/
	bool DrawModify(int 頂点aX, int 頂点aY, int 頂点bX, int 頂点bY, int 頂点cX, int 頂点cY, int 頂点dX, int 頂点dY) const
	{
		return !DxLib::DrawModiGraph(頂点aX, 頂点aY, 頂点bX, 頂点bY, 頂点cX, 頂点cY, 頂点dX, 頂点dY, this->GetHandle(), this->isTrans);
	}
	/** 四角形に変形マスク[DXLIB].*/
	bool ZMaskModify(int 頂点aX, int 頂点aY, int 頂点bX, int 頂点bY, int 頂点cX, int 頂点cY, int 頂点dX, int 頂点dY, ZMaskType Zマスクタイプ) const
	{
		return !DxLib::DrawModiGraphToZBuffer(頂点aX, 頂点aY, 頂点bX, 頂点bY, 頂点cX, 頂点cY, 頂点dX, 頂点dY, this->GetHandle(), (int)Zマスクタイプ);
	}

	/** 一部を指定して描画.*/
	bool DrawPart(int 描画先X座標, int 描画先Y座標, int 描画元X原点, int 描画元Y原点, int 幅, int 高さ, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRectGraph(描画先X座標, 描画先Y座標, 描画元X原点, 描画元Y原点, 幅, 高さ, this->GetHandle(), this->isTrans, 反転フラグ);
	}
	/** 一部を指定してマスク[DXLIB].*/
	bool ZMaskPart(int 描画先X座標, int 描画先Y座標, int 描画元X原点, int 描画元Y原点, int 幅, int 高さ, ZMaskType Zマスクタイプ, bool 反転フラグ = false) const
	{
		return !DxLib::DrawRectGraph(描画先X座標, 描画先Y座標, 描画元X原点, 描画元Y原点, 幅, 高さ, this->GetHandle(), (int)Zマスクタイプ, 反転フラグ);
	}

	/** スクリーンの一部をイメージに取り込む[DXLIB].*/
	/** 指定した座標を右上にして、スクリーンからImageと同じ大きさコピーする*/
	int LoadScreen(int X座標,int Y座標)
	{
		int w, h;
		DxLib::GetGraphSize( this->GetHandle() , &w , &h );
		return DxLib::GetDrawScreenGraph( X座標 , Y座標 , X座標 + w , Y座標 + h , this->GetHandle() );
	}

	/** 幅を取得.*/
	int GetWidth() const
	{
		return width;
	}
			
	/** 高さを取得.*/
	int GetHeight() const
	{
		return height;
	}

	/** 説明.*/
	bool GetIsScreen() const
	{
		return this->isScreen;
	}

	/** αチャンネルフラグを取得.*/
	bool GetIsAlphaChannel() const
	{
		return this->isAlphaChannel;
	}
			
	/** 透過フラグを取得.*/
	bool GetIsTrans() const
	{
		return this->isTrans;
	}
	
	/** 描画先にこのイメージに指定[未実装].*/
	/** Image::Makeでスクリーンフラグをtrueにした場合成功。*/
	bool SetDrawScreen()
	{
		return false;
	}
};
}