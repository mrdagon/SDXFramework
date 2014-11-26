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
	/** ScreenにSetして使う.*/
	/** \include ScreenSample.*/
	class Renderer
	{
	private:
		SDL_Renderer* handle = nullptr;//!<
		SDL_Surface* surface = nullptr;//!<
	public:
		static Renderer DefaultRenderer()
		{
			static Renderer defaultRenderer;
			return defaultRenderer;
		}

		BlendMode nowBlendMode = BlendMode::NoBlend;//!<
		int blendParam = 0;//!<αブレンドの比率 0～255
		Color clearColor = Color(0, 0, 0);//!<消去時の色
		Color rgba = Color(255, 255, 255, 0);//!<描画輝度と透明度

		/*描画ハンドルを取得*/
		SDL_Renderer* GetHandle()
		{
			return handle;
		}

		~Renderer()
		{
			Destroy();
		}

		/*Surfaceに対応した、Rendererを生成.*/
		bool Create(int 幅, int 高さ)
		{
			if (handle != nullptr) return false;
			surface = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
			handle = SDL_CreateSoftwareRenderer(surface);

			return true;
		}

		/*Windowに対応した、Rendererを生成.*/
		bool Create(SDL_Window* 元Window)
		{
			if (handle != nullptr) return false;

			handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC);

			return true;
		}

		/**対象RenderHandleにコピー.*/
		bool Draw(const Rect& 領域, Renderer& コピー先 = Renderer::DefaultRenderer())
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

		/*Rendererを削除.*/
		bool Destroy()
		{
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
		bool SetTransColor(Color 透過色)
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 透過色.GetRed(), 透過色.GetBlue(), 透過色.GetGreen()));
		}

		/** 透過色を解除.*/
		bool ResetTransColor()
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, false, 0);
		}

		/** BMP形式で保存.*/
		bool SaveBMP(const char* ファイル名)
		{
			if (!surface){ return false; }
			return !SDL_SaveBMP(surface, ファイル名);
		}
	};
}