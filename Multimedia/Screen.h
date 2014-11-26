﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Multimedia/Renderer.h>
#include <Framework/Shape.h>

namespace SDX
{
	/** 現在の描画先を操作するクラス.*/
	/** \include ScreenSample.h*/
	class Screen
	{
	private:
		Screen(){};
		~Screen(){};
		Renderer *handle = nullptr;//!<
	public:
		/** シングルトンなインスタンスを取得.*/
		static Screen& Single()
		{
			static Screen single;
			return single;
		}

		/** スクリーンハンドルを取得.*/
		static SDL_Renderer* GetHandle()
		{
			return Single().handle->GetHandle();
		}

		/** Rendererを取得.*/
		static Renderer* GetRenderer()
		{
			return Single().handle;
		}

		/** Rendererを設定.*/
		static void SetRenderer(Renderer &描画先Renderer = Renderer::DefaultRenderer())
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

		/** 描画対象になっている画面の一部をBMP形式で保存[未実装].@todo*/ 
		static bool SaveBmp(const Rect &領域, const char *ファイル名)
		{
			//SDL_RenderReadPixelsで実装出来るはず
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