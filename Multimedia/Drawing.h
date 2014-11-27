﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include<Multimedia/SDX.h>
#include<Multimedia/Color.h>
#include<Multimedia/Image.h>
#include<Multimedia/Font.h>
#include<Utility/VariadicStream.h>
#include<Framework/Shape.h>

namespace SDX
{
	/** リソースを読み込まずに描画を行う関数群.*/
	/** \include DrawingSample.h*/
	class Drawing
	{
	private:
		Drawing();
		~Drawing();

		/**透過状態を計算する.*/
		static void RGBACulculate(int 赤, int 緑, int 青)
		{
			SDL_SetRenderDrawBlendMode(Screen::GetHandle(), (SDL_BlendMode)Screen::activeRenderer->nowBlendMode);
			SDL_SetRenderDrawColor
				(
				Screen::GetHandle(),
				Screen::activeRenderer->rgba.GetRed() * 赤 / 255,
				Screen::activeRenderer->rgba.GetGreen() * 緑 / 255,
				Screen::activeRenderer->rgba.GetBlue() * 青 / 255,
				Screen::activeRenderer->blendParam
				);
		}
		/**円のデータを作成する.*/
		static Image& circleTexture(bool 塗りつぶしフラグ)
		{
			static Image circleA;
			static Image circleB;

			if (circleA.handle == nullptr)
			{
				Font font;
				font.Load(SystemFont::Gothic, 1000);

				SDL_Surface* surfaceA = TTF_RenderUTF8_Blended(font.GetHandle(), "●", { 255, 255, 255, 255 });
				circleA.handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), surfaceA);
				circleA.part.w = surfaceA->w;
				circleA.part.h = surfaceA->h;
				SDL_FreeSurface(surfaceA);

				SDL_Surface* surfaceB = TTF_RenderUTF8_Blended(font.GetHandle(), "○", { 255, 255, 255, 255 });
				circleB.handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), surfaceB);
				circleB.part.w = surfaceB->w;
				circleB.part.h = surfaceB->h;
				SDL_FreeSurface(surfaceB);

				font.Release();
			}

			if (塗りつぶしフラグ)
			{
				return circleA;
			}
			else
			{
				return circleB;
			}
		}

	public:

		/** デフォルトのフォントを取得する.*/
		static Font& GetFont()
		{
			static Font defaultFont;
			return defaultFont;
		}

		/** デフォルトのフォントを設定する.*/
		static void SetDefaultFont(const char* フォント名, int 大きさ)
		{
			GetFont().Load(フォント名, 大きさ);
		}

		/** 始点と終点を結ぶ直線を描画.*/
		/** @todo SDLは太さ指定不可*/
		static bool Line(const Point &始点, const Point &終点, Color 色, int 太さ)
		{
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			return !SDL_RenderDrawLine(Screen::GetHandle(), (int)始点.x, (int)始点.y, (int)終点.x, (int)終点.y);
		}

		/** 左上の座標と大きさを指定して矩形を描画.*/
		static bool Rect(const Rect &領域, Color 色, bool 塗りつぶしフラグ)
		{
			SDL_Rect buf = { (int)領域.GetLeft(), (int)領域.GetTop(), (int)領域.GetW(), (int)領域.GetH() };
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			if (塗りつぶしフラグ)
			{
				return !SDL_RenderFillRect(Screen::GetHandle(), &buf);
			}
			else{
				return !SDL_RenderDrawRect(Screen::GetHandle(), &buf);
			}
		}

		/** 中心と半径を指定して円を描画.*/
		/** @todo SDLは仮実装*/
		static void Circle(const Circle &円形, Color 色, bool 塗りつぶしフラグ)
		{
			SDL_SetRenderDrawColor(Screen::GetHandle(), 色.GetRed(), 色.GetGreen(), 色.GetBlue(), 0);
			circleTexture(塗りつぶしフラグ).DrawExtend({ 円形.x - 円形.radius, 円形.y - 円形.radius }, { 円形.x + 円形.radius, 円形.y + 円形.radius });
		}

		/** 中心と外接する四角形の大きさを指定して楕円を描画.*/
		/** @todo SDLは仮実装*/
		static void Oval(const Point &中心, int 幅, int 高さ, Color 色, bool 塗りつぶしフラグ)
		{
			SDL_SetRenderDrawColor(Screen::GetHandle(), 色.GetRed(), 色.GetGreen(), 色.GetBlue(), 0);
			circleTexture(塗りつぶしフラグ).DrawExtend({ 中心.x - 幅 / 2, 中心.y - 高さ / 2 }, { 中心.x + 幅 / 2, 中心.y + 高さ / 2 });
		}

		/** 頂点を３つ指定して三角形を描画.*/
		/** @todo SDLは塗りつぶし不可*/
		static void Triangle(const Point &頂点A, const Point &頂点B, const Point &頂点C, Color 色, bool 塗りつぶしフラグ = false)
		{
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			SDL_RenderDrawLine(Screen::GetHandle(), (int)頂点A.x, (int)頂点A.y, (int)頂点B.x, (int)頂点B.y);
			SDL_RenderDrawLine(Screen::GetHandle(), (int)頂点B.x, (int)頂点B.y, (int)頂点C.x, (int)頂点C.y);
			SDL_RenderDrawLine(Screen::GetHandle(), (int)頂点C.x, (int)頂点C.y, (int)頂点A.x, (int)頂点A.y);
		}

		/** 指定座標に点を描画.*/
		static void Pixel(const Point &座標, Color 色)
		{
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			SDL_RenderDrawPoint(Screen::GetHandle(), (int)座標.x, (int)座標.y);
		}

		/** 指定座標の色を取得 [未実装].@todo*/		
		static SDL_Color GetPixel(const Point &座標)
		{
			//SDL_RenderReadPixelsで実装可能
			return SDL_Color{ 0, 0, 0 };
		}

		/** 画像を一時的にメモリに読み込んで描画.*/
		/** この処理は重いので、通常はImageクラスを利用する*/
		static void ImageFile(const Point &座標, const char *ファイル名, bool 透過フラグ = true)
		{
			Image buf(ファイル名);
			buf.Draw(座標, false);
			buf.Release();
		}

		/** 文字を描画.*/
		/** フォントはデフォルトでゴシック体*/
		static void String(const Point &座標, Color 色, VariadicStream 描画する文字列)
		{
			GetFont().Draw(座標, 色, 描画する文字列);
		}
	};
}