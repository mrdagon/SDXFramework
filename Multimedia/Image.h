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
		SrcR,//!<
		SrcG,//!<

		SrcB,//!<
		SrcA,//!<
		BlendR,//!<
		BlendG,//!<
		BlendB,//!<
		BlendA,//!<
	};

	/** 説明.*/
	enum class ClipType
	{
		Less,//!<
		Greater,//!<
	};

	/** 画像データを表すクラス.*/
	/** デストラクタでリソース解放周りは調整中*/
	/** \include ImageSample.h*/
	class Image
	{
		friend class Anime;
		friend class Renderer;
		friend class ImagePack;
		friend class Drawing;
	private:
		SDL_Rect part;
		SDL_Texture* handle = nullptr;

		/**透過状態を計算する.*/
		void RGBACulculate() const
		{
			if (Screen::activeRenderer->nowBlendMode == BlendMode::NoBlend)
			{
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)BlendMode::Alpha);
				SDL_SetTextureAlphaMod(handle, 255);
			}
			else{
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)Screen::activeRenderer->nowBlendMode);
				SDL_SetTextureAlphaMod(handle, Screen::activeRenderer->blendParam);
			}

			SDL_SetTextureColorMod
				(
				handle,
				Screen::activeRenderer->rgba.GetRed(),
				Screen::activeRenderer->rgba.GetGreen(),
				Screen::activeRenderer->rgba.GetBlue()
				);
		}

	public:
		Image() = default;
		~Image() = default;

		Image(const char *ファイル名)
		{
			Load(ファイル名);
		}

		Image(Image& コピー元, int X頂点, int Y頂点, int 幅, int 高さ)
		{
			Copy(コピー元, X頂点, Y頂点, 幅, 高さ);
		}

		Image(SDL_Texture* 画像ハンドル,int 幅,int 高さ):
			handle(画像ハンドル),
			part({0,0,幅,高さ})
		{}

		/** 空のイメージを作成.*/
		Image(int 幅, int 高さ)
		{
			Make(幅, 高さ);
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
		SDL_Texture* Make(int 幅, int 高さ)
		{
			Release();

			handle = SDL_CreateTexture(Screen::GetHandle(), 0, 0, 幅, 高さ);
			part.x = 0;
			part.y = 0;
			part.w = 幅;
			part.h = 高さ;

			return handle;
		}

		/** 別のImageの一部をコピーして、Imageを初期化.*/
		/** handleは同一*/
		SDL_Texture* Copy(const Image& 元イメージ, int X原点, int Y原点, int 幅, int 高さ)
		{
			this->handle = 元イメージ.handle;
			part.x = X原点;
			part.y = Y原点;
			part.w = 幅;
			part.h = 高さ;

			return handle;
		}

		/** 同じImageを作成[未実装].*/
		/** handleは別*/
		/** @todo 実装中*/
		Image Clone() const
		{
			Image image(part.w, part.h);

			return image;
		}

		/** Imageの一部から別Imageを作成[未実装].*/
		/** handleは別*/
		/** @todo 実装中*/
		Image Clone(int X原点, int Y原点, int 幅, int 高さ) const
		{
			Image image(幅, 高さ);

			return image;
		}

		/** ハンドルを取得.*/
		SDL_Texture* GetHandle() const
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
		/** @todo 実装予定無し*/
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
	};
}