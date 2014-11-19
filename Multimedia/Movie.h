﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Image.h>

namespace SDX
{
	/** 動画を表すクラス[未実装].*/
	/**    \include MovieSample.h*/
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
		void Play(int 拡大率, bool 途中キャンセルフラグ)
		{
		}
	};

	/** Imageクラスの動画版[未実装].*/
	/**    \include*/
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
		MovieImage() :
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
			return false;
		}

		/** ファイルの開放.*/
		/** 動画ファイルをメモリから開放する。*/
		bool Release()
		{
			return false;
		}

		/** ハンドルの取得.*/
		int GetHandle()
		{
			return this->handle;
		}

		/** 動画の再生.*/
		bool Play()
		{
			return false;
		}

		/** 動画の停止.*/
		bool Pause()
		{
			return false;
		}

		/** 動画の再生位置を設定.*/
		int Seek(int 再生位置)
		{
			return false;
		}

		/** 動画の再生位置を取得.*/
		int Tell()
		{
			return false;
		}

		/** 動画が再生中か取得.*/
		bool Check()
		{
			return false;
		}

		/** 指定座標に描画.*/
		bool Draw(const Point &座標, bool 反転フラグ = false)
		{
			return false;
		}

		/** 指定矩形内に描画.*/
		bool DrawExtend(const Rect &領域)
		{
			return false;
		}

		/** 角度、拡大率を指定して描画.*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, bool 反転フラグ = false)
		{
			return false;
		}

		/** 角度、拡大率を指定して描画.*/
		bool DrawRotateAxis(const Point &座標, int X軸, int Y軸, double 拡大率, double 角度, bool 反転フラグ = false)
		{
			return false;
		}

		/** 四角形に変形描画.*/
		bool DrawModify(const Point &頂点A, const Point &頂点B, const Point &頂点C, const Point &頂点D) const
		{
			return false;
		}

		/** 一部を指定して描画.*/
		bool DrawPart(const Point &描画座標, const Rect &元領域, bool 反転フラグ)
		{
			return false;
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