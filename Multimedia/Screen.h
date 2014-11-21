//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
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
		RendererHandle handle = nullptr;
		SurfaceHandle surface = nullptr;
	public:
		static Renderer defaultRenderer;

		BlendMode nowBlendMode = BlendMode::NoBlend;
		int blendParam = 0;//!<αブレンドの比率 0～255
		Color clearColor = Color(0, 0, 0);//!<消去時の色
		Color rgba = Color(255, 255, 255, 0);//!<描画輝度と透明度

		/*描画ハンドルを取得*/
		RendererHandle GetHandle()
		{
			return handle;
		}

		~Renderer()
		{
			Destroy();
		}

		/*Surfaceに対応した、Rendererを生成.*/
		bool Create(int 幅,int 高さ)
		{
			if (handle != nullptr) return false;
			surface = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
			handle = SDL_CreateSoftwareRenderer(surface);

			return true;
		}

		/*Windowに対応した、Rendererを生成.*/
		bool Create(WindowHandle 元Window)
		{
			if (handle != nullptr) return false;

			handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC);

			return true;
		}

		/**対象RenderHandleにコピー.*/
		bool Draw( const Rect& 領域 , Renderer& コピー先 = Renderer::defaultRenderer)
		{
			if (surface == nullptr) return false;

			ImageHandle image;
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
			if (handle == 0) return false;
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
			return !SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 透過色.GetRed(), 透過色.GetBlue(), 透過色.GetGreen()));
		}

		/** 透過色を解除.*/
		bool ResetTransColor()
		{
			return !SDL_SetColorKey(surface, false , 0);
		}

		/** BMP形式で保存.*/
		bool SaveBMP(const char* ファイル名)
		{
			return !SDL_SaveBMP(surface, ファイル名);
		}
	};

	/** 現在の描画先を操作するクラス.*/
	/** \include ScreenSample.h*/
	class Screen
	{
	private:
		Screen(){};
		~Screen(){};
		Renderer *handle = nullptr;
	public:
		/** シングルトンなインスタンスを取得.*/
		static Screen& Single()
		{
			static Screen single;
			return single;
		}

		/** スクリーンハンドルを取得.*/
		static RendererHandle GetHandle()
		{
			return Single().handle->GetHandle();
		}

		/** Rendererを取得.*/
		static Renderer* GetRenderer()
		{
			return Single().handle;
		}

		/** Rendererを設定.*/
		static void SetRenderer(Renderer &描画先Renderer = Renderer::defaultRenderer)
		{
			Single().handle = &描画先Renderer;
		}

		/** 描画領域を設定する、設定範囲外には描画されない.*/
		static bool SetArea(const Rect &描画領域)
		{
			SDL_Rect rect = { (int)描画領域.GetX(), (int)描画領域.GetY(), (int)描画領域.GetW(), (int)描画領域.GetH() };

			return !SDL_RenderSetViewport(Single().GetHandle(),&rect);
		}

		/** 非描画領域を設定する、設定範囲内には描画されない.*/
		static bool SetClip(const Rect &非描画領域)
		{
			SDL_Rect rect = { (int)非描画領域.GetX(), (int)非描画領域.GetY(), (int)非描画領域.GetW(), (int)非描画領域.GetH() };

			return !SDL_RenderSetViewport(Single().GetHandle(), &rect);
		}

		/**描画領域を解除する.*/
		static void ResetArea()
		{
			SDL_RenderSetViewport(Single().GetHandle(), 0);
		}

		/**非描画領域を解除する.*/
		static void ResetClip()
		{
			SDL_RenderSetViewport(Single().GetHandle(), 0);
		}

		/** Screen::Clear後の色を設定.*/
		static bool SetBackColor(Color 背景色)
		{
			Single().GetRenderer()->clearColor.SetColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue());

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
				GetHandle(),
				Single().GetRenderer()->clearColor.GetRed(),
				Single().GetRenderer()->clearColor.GetGreen(),
				Single().GetRenderer()->clearColor.GetBlue(),
				0
				);
			SDL_RenderClear(GetRenderer()->GetHandle());
			return true;
		}

		/** ブレンド描画のモードを設定.*/
		static bool SetBlendMode(BlendMode ブレンドモード, int 設定値)
		{
			Single().GetRenderer()->nowBlendMode = ブレンドモード;
			if (設定値 > 255)      Single().GetRenderer()->blendParam = 255;
			else if (設定値 < 0)      Single().GetRenderer()->blendParam = 0;
			else                   Single().GetRenderer()->blendParam = 設定値;

			return true;
		}

		/** 描画対象になっている画面の一部をBMP形式で保存[未実装].*/
		static bool SaveBmp(const Rect &領域, const char *ファイル名)
		{
			return false;
		}

		/** 描画輝度を設定.*/
		static bool SetBright(Color 輝度)
		{
			Single().GetRenderer()->rgba.SetColor(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
			return true;
		}
	};
}