//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Framework/Shape.h>

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
		Less,
		Greater,
	};

	/** 画像データを表すクラス.*/
	/**    \include ImageSample.h*/
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

		SDL_Rect part;

		ImageHandle handle = 0;

		// 透過状態を計算する
		void RGBACulculate() const
		{
			if (Screen::Single().nowBlendMode == BlendMode::NoBlend)
			{
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)BlendMode::Alpha);
				SDL_SetTextureAlphaMod(handle, 255);
			}
			else{
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)Screen::Single().nowBlendMode);
				SDL_SetTextureAlphaMod(handle, Screen::Single().blendParam);
			}

			SDL_SetTextureColorMod
				(
				handle,
				Screen::Single().rgba.GetRed(),
				Screen::Single().rgba.GetGreen(),
				Screen::Single().rgba.GetBlue()
				);
		}

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
		Image(int 幅, int 高さ, bool スクリーン用フラグ, bool αチャンネルフラグ = true, bool 透過フラグ = true)
		{
			Make(幅, 高さ, スクリーン用フラグ, αチャンネルフラグ, 透過フラグ);
		}

		/** 画像をメモリへ読み込む.*/
		bool Load(const char *ファイル名)
		{
			Release();
			SDL_Surface* temp = IMG_Load(ファイル名);

			if (temp == nullptr) return false;

			handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), temp);

			part.x = 0;
			part.y = 0;
			part.w = temp->w;
			part.h = temp->h;

			SDL_FreeSurface(temp);
			return (handle != nullptr);
		}

		/** イメージをメモリから開放.*/
		bool Release()
		{
			if (this->handle != nullptr)
			{
				SDL_DestroyTexture(handle);
				return true;
			}
			return false;
		}

		/** 空のイメージを作成.*/
		ImageHandle Make(int 幅, int 高さ, bool スクリーン用フラグ = false, bool αチャンネルフラグ = true, bool 透過フラグ = true)
		{
			Release();

			handle = SDL_CreateTexture(Screen::GetHandle(), SDL_TEXTUREACCESS_TARGET * スクリーン用フラグ, 0, 幅, 高さ);
			part.x = 0;
			part.y = 0;
			part.w = 幅;
			part.h = 高さ;

			isTrans = 透過フラグ;
			isScreen = スクリーン用フラグ;
			isAlphaChannel = αチャンネルフラグ;

			return handle;
		}

		/** 元イメージの一部をコピーして、別イメージを作成.*/
		ImageHandle Copy(const Image& 元イメージ, int X原点, int Y原点, int 幅, int 高さ)
		{
			this->handle = 元イメージ.handle;
			part.x = X原点;
			part.y = Y原点;
			part.w = 幅;
			part.h = 高さ;

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
		bool Draw(const Point &座標, bool 反転フラグ = false) const
		{
			SDL_Rect temp = { (int)座標.x, (int)座標.y, part.w, part.h };
			RGBACulculate();
			if (反転フラグ)
			{
				static SDL_Point point = { 0, 0 };
				return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, &point, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
			}
			else{
				return !SDL_RenderCopy(Screen::GetHandle(), handle, &part, &temp);
			}
		}

		/** 指定矩形内に描画.*/
		bool DrawExtend(const Point &座標A, const Point &座標B) const
		{
			SDL_Rect temp = { (int)座標A.x, (int)座標A.y, (int)(座標B.x - 座標A.x), (int)(座標B.y - 座標A.y) };
			RGBACulculate();
			return !SDL_RenderCopy(Screen::GetHandle(), handle, &part, &temp);
		}

		/** 角度、拡大率を指定して描画.*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, bool 反転フラグ = false) const
		{
			const int wbuf = int(part.w*拡大率);
			const int hbuf = int(part.h*拡大率);
			SDL_Rect temp = { (int)座標.x - wbuf / 2, (int)座標.y - hbuf / 2, wbuf, hbuf };
			SDL_Point point = { wbuf / 2, hbuf / 2 };
			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 角度 * 180 / PAI, &point, SDL_RendererFlip(反転フラグ));
		}

		/** 回転軸、角度、拡大率を指定して描画.*/
		bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率, double 角度, bool 反転フラグ = false) const
		{
			const int wbuf = int(part.w*拡大率);
			const int hbuf = int(part.h*拡大率);
			SDL_Rect temp = { (int)座標.x - wbuf / 2, (int)座標.y - hbuf / 2, wbuf, hbuf };
			SDL_Point point = { int(回転軸座標.x*拡大率), int(回転軸座標.y*拡大率) };
			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 角度 * 180 / PAI, &point, SDL_RendererFlip(反転フラグ));
		}

		/** 回転軸、角度、拡大率を縦横別に指定して描画.*/
		bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率X, double 拡大率Y, double 角度, bool 反転フラグ = false) const
		{
			const int wbuf = int(part.w*拡大率X);
			const int hbuf = int(part.h*拡大率Y);
			SDL_Rect temp = { (int)座標.x - wbuf / 2, (int)座標.y - hbuf / 2, wbuf, hbuf };
			SDL_Point point = { int(回転軸座標.x*拡大率X), int(回転軸座標.y*拡大率Y) };
			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 角度 * 180 / PAI, &point, SDL_RendererFlip(反転フラグ));
		}

		/** 四角形に変形描画[未実装].*/
		bool DrawModify(const Point &頂点A, const Point &頂点B, const Point &頂点C, const Point &頂点D) const
		{
			return false;
		}

		/** 一部を指定して描画.*/
		bool DrawPart(int 描画先X座標, int 描画先Y座標, int 描画元X原点, int 描画元Y原点, int 幅, int 高さ, bool 反転フラグ = false) const
		{
			SDL_Rect temp = { 描画先X座標, 描画先Y座標, 幅, 高さ };
			SDL_Rect part = { 描画元X原点 + this->part.x, 描画元Y原点 + this->part.y, 幅, 高さ };
			static SDL_Point point = { 0, 0 };
			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, &point, SDL_RendererFlip(反転フラグ));
		}

		/** スクリーンの一部をイメージに取り込む[未実装].*/
		/** 指定した座標を右上にして、スクリーンからImageと同じ大きさコピーする*/
		int LoadScreen(int X座標, int Y座標)
		{
			return false;
		}

		/** 幅を取得.*/
		int GetWidth() const
		{
			return part.w;
		}

		/** 高さを取得.*/
		int GetHeight() const
		{
			return part.h;
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