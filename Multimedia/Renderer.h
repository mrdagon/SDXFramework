//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Multimedia/Renderer.h>
#include <Framework/Shape.h>

namespace SDX
{
	/** ブレンドモード.*/
	enum class BlendMode
	{
		NoBlend = SDL_BLENDMODE_NONE,//!<
		Alpha = SDL_BLENDMODE_BLEND,//!<
		Add = SDL_BLENDMODE_ADD,//!<
		Mula = SDL_BLENDMODE_MOD,//!<
	};

	/** 描画先を表すクラス.*/
	/** Screenに無くてRendereにある関数は[Renderer専用]と表記.*/
	/** \include ScreenSample.*/
	class Renderer
	{
		friend class SubWindow;
	private:
		SDL_Renderer* handle = nullptr;//!<
		SDL_Surface* surface = nullptr;//!<
		bool isWindow;//!< ウィンドウに対応しているかどうか

		/*Windowに対応した、Rendererを生成.*/
		bool Create(SDL_Window* 元Window)
		{
			if (handle != nullptr) return false;

			isWindow = true;
			handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC);
			surface = SDL_GetWindowSurface(元Window);
			return true;
		}

	public:
		static Renderer &mainRenderer;

		BlendMode nowBlendMode = BlendMode::NoBlend;//!<
		int blendParam = 0;//!<αブレンドの比率 0～255
		Color clearColor = Color(0, 0, 0);//!<消去時の色
		Color rgba = Color(255, 255, 255, 0);//!<描画輝度と透明度

		/*描画ハンドルを取得*/
		SDL_Renderer* GetHandle()
		{
			return handle;
		}

		Renderer() = default;

		~Renderer()
		{
			Destroy();
		}

		Renderer(int 幅, int 高さ)
		{
			Create(幅,高さ);
		}

		/** Windowと独立した、Rendererを生成.*/
		/** [Renderer専用]*/
		bool Create(int 幅, int 高さ)
		{
			if (handle != nullptr) return false;

			isWindow = false;
			surface = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
			handle = SDL_CreateSoftwareRenderer(surface);

			return true;
		}

		/** Rendererを削除.*/
		/** Windowに対応して生成したRendererは削除不可.*/
		/** [Renderer専用]*/
		bool Destroy()
		{
			if ( isWindow){ return false; }
			if (handle == 0){ return false; }
			if (surface != nullptr)
			{
				SDL_FreeSurface(surface);
			}

			SDL_DestroyRenderer(handle);

			surface = nullptr;
			handle = nullptr;

			return true;
		}

		/** 透過色を設定.*/
		/** [Renderer専用]*/
		bool SetTransColor(Color 透過色)
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 透過色.GetRed(), 透過色.GetBlue(), 透過色.GetGreen()));
		}

		/** 透過色を解除.*/
		/** [Renderer専用]*/
		bool ResetTransColor()
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, false, 0);
		}

		/**対象RenderHandleにコピー.*/
		/** [Renderer専用]*/
		bool Draw(const Rect& 領域, Renderer& コピー先 = Renderer::mainRenderer)
		{
			if (!surface){ return false; }

			SDL_Texture* image;
			image = SDL_CreateTextureFromSurface(コピー先.GetHandle(), surface);

			SDL_Rect srcrect = { 0, 0, (int)領域.GetW(), (int)領域.GetH() };
			SDL_Rect dsrect = { (int)領域.GetX(), (int)領域.GetY(), (int)領域.GetW(), (int)領域.GetH() };
			SDL_RenderCopy(コピー先.GetHandle(), image, &srcrect, &dsrect);
			SDL_DestroyTexture(image);

			return true;
		}

		/** 画面を消去する.*/
		bool Clear()
		{
			if (handle == nullptr){ return false; }

			SDL_SetRenderDrawColor
				(
				handle,
				clearColor.GetRed(),
				clearColor.GetGreen(),
				clearColor.GetBlue(),
				0
				);
			SDL_RenderClear(handle);
			return true;
		}

		/** 描画領域を設定する、設定範囲外には描画されない.*/
		bool SetArea(const Rect &描画領域)
		{
			if (handle == nullptr){ return false; }
			SDL_Rect rect = { (int)描画領域.GetX(), (int)描画領域.GetY(), (int)描画領域.GetW(), (int)描画領域.GetH() };

			return !SDL_RenderSetViewport(handle, &rect);
		}

		/**描画領域を解除する.*/
		bool ResetArea()
		{
			if (handle == nullptr){ return false; }
			return !SDL_RenderSetViewport(handle, 0);
		}

		/** 非描画領域を設定する、設定範囲内には描画されない.*/
		bool SetClip(const Rect &非描画領域)
		{
			if (handle == nullptr){ return false; }
			SDL_Rect rect = { (int)非描画領域.GetX(), (int)非描画領域.GetY(), (int)非描画領域.GetW(), (int)非描画領域.GetH() };

			return !SDL_RenderSetViewport(handle, &rect);
		}

		/** 非描画領域を解除する.*/
		bool ResetClip()
		{
			if (handle == nullptr){ return false; }
			return !SDL_RenderSetViewport(handle, 0);
		}

		/** Screen::Clear後の色を設定.*/
		void SetBackColor(const Color &背景色)
		{
			clearColor.SetColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue() );
		}

		/** 描画輝度を設定.*/
		void SetBright(const Color &輝度)
		{
			rgba.SetColor(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
		}

		/** ブレンド描画のモードを設定.*/
		void SetBlendMode(BlendMode ブレンドモード, int 設定値)
		{
			nowBlendMode = ブレンドモード;
			if (設定値 > 255){ blendParam = 255; }
			else if (設定値 < 0){ blendParam = 0; }
			else { blendParam = 設定値; }
		}

		/** BMP形式で保存.*/
		bool SaveBMP(const char* ファイル名)
		{
			if ( handle == nullptr ){ return false; }
			return !SDL_SaveBMP(surface, ファイル名);
		}
	};
}