#pragma once//☀DXLIB
#include<Multimedia/SDX.h>
#include<Multimedia/Image.h>

namespace SDX
{
/** 動画を表すクラス[DXLIB].*/
/**	\include MovieSample.h*/
class Movie
{
private:
	std::string fileName;
public:
	
	/** 動画ファイルの登録.*/
	Movie(const char *ファイル名)
	{
		this->fileName = ファイル名;
	}
	
	/** 動画ファイルの登録.*/
	/** メモリには読み込まれない。*/
	bool Load(const char *ファイル名)
	{
		this->fileName = ファイル名;
		return true;
	}

	/** 動画を再生.*/
	/** 拡大は整数倍のみ\n
		途中キャンセルフラグがtrueの場合、再生中に入力すると途中で再生を中断する*/
	void Play(int 拡大率 , bool 途中キャンセルフラグ)
	{
		if( 途中キャンセルフラグ )
		{
			PlayMovie( fileName.c_str() , 拡大率 , DX_MOVIEPLAYTYPE_BCANCEL ) ;
		}else{
			PlayMovie( fileName.c_str() , 拡大率 , DX_MOVIEPLAYTYPE_NORMAL ) ;
		}
	}
};
	
/** Imageクラスの動画版[DXLIB].*/
/**	\include*/
class MovieImage
{
private:
	int handle;
	bool isTrans;
	MovieImage(const MovieImage &movie);
	MovieImage& operator =(const MovieImage &movie);
	int width;
	int height;
public:
	MovieImage():
		isTrans(false)
	{}
	
	/** ファイルの読込.*/
	MovieImage(const char *ファイル名)
	{
		Load(ファイル名);
	}

	/** ファイルの読込.*/
	/** 動画ファイルをメモリに読み込む。*/
	bool Load(const char *ファイル名)
	{
		if(this->handle != NULL_HANDLE) DxLib::DeleteGraph(this->handle);
		this->handle = DxLib::LoadGraph(ファイル名);
		return (this->handle != -1);
	}

	/** ファイルの開放.*/
	/** 動画ファイルをメモリから開放する。*/
	bool Release()
	{
		return !DxLib::DeleteGraph(this->handle);
	}

	/** ハンドルの取得.*/
	int GetHandle()
	{
		return this->handle;
	}
	
	/** 動画の再生.*/
	bool Play()
	{
		return !DxLib::PlayMovieToGraph( this->handle );
	}
	
	/** 動画の停止.*/
	bool Pause()
	{
		return !DxLib::PauseMovieToGraph( this->handle ) ;
	}
	
	/** 動画の再生位置を設定.*/
	int Seek(int 再生位置)
	{
		return DxLib::SeekMovieToGraph( this->handle , 再生位置 ) ;
	}
	
	/** 動画の再生位置を取得.*/
	int Tell()
	{
		return DxLib::TellMovieToGraph( this->handle ) ;
	}
	
	/** 動画が再生中か取得.*/
	bool Check()
	{
		return (DxLib::GetMovieStateToGraph( this->handle ) == 1);
	}
	
	/** 指定座標に描画.*/
	bool Draw(int X座標,int Y座標 , bool 反転フラグ = false)
	{
		if (反転フラグ) return !DxLib::DrawTurnGraph(X座標, Y座標, this->handle, this->isTrans);
		else		 return !DxLib::DrawGraph(X座標, Y座標, this->handle, this->isTrans);
	}

	/** 指定矩形内に描画.*/
	bool DrawExtend(int X座標A, int Y座標A, int X座標B, int Y座標B)
	{
		return !DxLib::DrawExtendGraph(X座標A, Y座標A, X座標B, Y座標B, this->handle, this->isTrans);
	}

	/** 角度、拡大率を指定して描画.*/
	bool DrawRotate(int X座標, int Y座標, double 拡大率, double 角度, bool 反転フラグ = false)
	{
		return !DxLib::DrawRotaGraph(X座標, Y座標, 拡大率, 角度, this->handle, this->isTrans, 反転フラグ);
	}
	
	/** 角度、拡大率を指定して描画.*/
	bool DrawRotateAxis(int X座標, int Y座標, int X軸, int Y軸, double 拡大率, double 角度, bool 反転フラグ = false)
	{
		return !DxLib::DrawRotaGraph2(X座標, Y座標, X軸, Y軸, 拡大率, 角度, this->GetHandle(), this->isTrans, 反転フラグ);
	}
	
	/** 四角形に変形描画.*/
	bool DrawModify(int X頂点A, int Y頂点A, int X頂点B, int Y頂点B, int X頂点C, int Y頂点C, int X頂点D, int Y頂点D) const
	{
		return !DxLib::DrawModiGraph( X頂点A, Y頂点A, X頂点B, Y頂点B, X頂点C, Y頂点C, X頂点D, Y頂点D, this->handle, this->isTrans);
	}

	/** 一部を指定して描画.*/
	bool DrawPart(int destX,int destY,int srcX, int srcY, int width, int height, bool isTurn)
	{
		return !DxLib::DrawRectGraph( destX , destY , srcX , srcY , width , height , this->handle , this->isTrans , isTurn );
	}
	
	/** 幅を取得.*/
	int GetWidth()
	{
		return width;
	}
	
	/** 高さを取得.*/
	int GetHeight()
	{			
		return height;
	}

};
}