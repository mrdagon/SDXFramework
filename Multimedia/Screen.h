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
	/** アクティブなRendererを操作するクラス.*/
	/** ScreenにあってRendereに無い関数は[Screen専用]と表記.*/
	/** \include Screen.h*/
	class Screen
	{
	private:
		Screen() = default;
		~Screen() = default;
		void operator =(const Screen& src){}
		Screen(const Screen& src){}

	public:
		static Renderer *activeRenderer;//!<アクティブなRenderer

		/** スクリーンハンドルを取得.*/
		/** [Screen専用]*/
		static SDL_Renderer* GetHandle()
		{
			return activeRenderer->GetHandle();
		}

		/** アクティブなRendererを取得.*/
		/** [Screen専用]*/
		static Renderer* GetRenderer()
		{
			return activeRenderer;
		}

		/** アクティブなRendererを設定.*/
		/** [Screen専用]*/
		static void SetRenderer(Renderer &描画先Renderer = Renderer::mainRenderer)
		{
			activeRenderer = &描画先Renderer;
		}

		/** 描画内容を反映.*/
		/** [Screen専用]*/
		static bool Flip()
		{
			SDL_RenderPresent(GetHandle());
			return true;
		}

		/** 画面を消去する.*/
		static bool Clear()
		{
			return activeRenderer->Clear();
		}

		/** 描画領域を設定する、設定範囲外には描画されない.*/
		static bool SetArea(const Rect &描画領域)
		{
			return activeRenderer->SetArea(描画領域);
		}

		/**描画領域を解除する.*/
		static bool ResetArea()
		{
			return activeRenderer->ResetArea();
		}

		/** 非描画領域を設定する、設定範囲内には描画されない.*/
		static bool SetClip(const Rect &非描画領域)
		{
			return activeRenderer->SetClip(非描画領域);
		}

		/** 非描画領域を解除する.*/
		static bool ResetClip()
		{
			return activeRenderer->ResetClip();
		}

		/** Screen::Clear後の色を設定.*/
		static void SetBackColor(const Color &背景色)
		{
			activeRenderer->SetBackColor(背景色);
		}

		/** 描画輝度を設定.*/
		static void SetBright(const Color &輝度)
		{
			activeRenderer->SetBright(輝度);
		}

		/** ブレンド描画のモードを設定.*/
		static void SetBlendMode(BlendMode ブレンドモード, int 設定値)
		{
			activeRenderer->SetBlendMode(ブレンドモード,設定値);
		}

		/** 描画輝度と描画モードをまとめて設定*/
		static void SetDrawMode(const Color &輝度＋α値 = Color::White, BlendMode ブレンドモード = BlendMode::NoBlend)
		{
			activeRenderer->SetDrawMode(輝度＋α値,ブレンドモード);
		}

		/** 画面全体をBMP形式で保存.*/ 
		static bool SaveBmp(const char *ファイル名)
		{
			return activeRenderer->SaveBMP(ファイル名);
		}

	};
}