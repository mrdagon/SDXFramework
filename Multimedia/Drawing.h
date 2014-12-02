//Copyright © 2014 SDXFramework
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
	/** \include Drawing.h*/
	class Drawing
	{
	private:
		//生成、削除、コピー等を禁止
		Drawing() = default;
		~Drawing() = default;
		void operator =(const Drawing& src){}
		Drawing(const Drawing& src){}

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
				Screen::activeRenderer->rgba.GetAlpha()
				);
		}
		/**円のデータを作成する.*/
		static Image& circleTexture( const Color &描画色 , int X座標 = 0, int Y座標 = 0, int 幅 = 0, int 高さ = 0 , int 太さ = 0)
		{
			static Image circleA;
			static Image circleB;
			static Renderer renderer;

			if (circleA.GetHandle() == nullptr)
			{
				renderer.Create(320, 320);
				renderer.SetBackColor(Color::Black);
				renderer.SetTransColor(Color::Black);
				renderer.Clear();

				Font font;
				font.Load(SystemFont::Gothic, 320);

				SDL_Surface* surface = TTF_RenderUTF8_Solid(font.GetHandle(), "●", { 255, 255, 255, 255 });
				circleA = Image(SDL_CreateTextureFromSurface(Screen::GetHandle(), surface), surface->w, surface->h);
				circleB = Image(SDL_CreateTextureFromSurface(renderer.GetHandle(), surface), surface->w, surface->h);
				SDL_FreeSurface(surface);

				font.Release();
			}

			if (太さ <= 0)
			{
				circleA.SetColor(描画色);
				return circleA;
			}
			else
			{
				太さ = std::max( 太さ * 640 / (幅 + 高さ) , 2);//最低2

				SDL_Rect rect = { 0, 0, 320, 320 };
				SDL_Rect in = { 太さ, 太さ, 320 - 太さ*2, 320 - 太さ*2 };

				if (Screen::activeRenderer->nowBlendMode == BlendMode::NoBlend)
				{
					//pngの透過部分があるのでNoBlendで描画はしない
					SDL_SetTextureBlendMode(circleB.GetHandle(), (SDL_BlendMode)BlendMode::Alpha);
					SDL_SetTextureAlphaMod(circleB.GetHandle(), 255);
				}
				else
				{
					SDL_SetTextureBlendMode(circleB.GetHandle(), (SDL_BlendMode)Screen::activeRenderer->nowBlendMode);
					SDL_SetTextureAlphaMod(circleB.GetHandle(), Screen::activeRenderer->rgba.GetAlpha());
				}

				int r = Screen::activeRenderer->rgba.GetRed() * 描画色.GetRed() / 255;
				int g = Screen::activeRenderer->rgba.GetGreen() * 描画色.GetGreen() / 255;
				int b = Screen::activeRenderer->rgba.GetBlue() * 描画色.GetBlue() / 255;
				int r2 = 0;

				//真っ白だと上手くいかないので補正
				if (r == 255 && g == 255 && b == 255)
				{
					r = 254;
					g = 254;
					b = 254;
				}

				if (r == 0 && g == 0 && b == 0)
				{			
					renderer.SetTransColor(Color::Red);
					renderer.SetBackColor(Color::Red);
					renderer.Clear();
					r2 = 255;
				}
				else
				{
					renderer.SetTransColor(Color::Black);
					renderer.SetBackColor(Color::Black);
					renderer.Clear();
				}

				//まず外側を描画				
				SDL_SetTextureColorMod(circleB.GetHandle(), r, g, b);		
				SDL_RenderCopy(renderer.GetHandle(), circleB.GetHandle(), &rect, &rect);
				//内側を黒で
				SDL_SetTextureColorMod(circleB.GetHandle(), r2, 0, 0);
				SDL_RenderCopy(renderer.GetHandle(), circleB.GetHandle(), &rect, &in);
				//色を戻す			
				renderer.DrawExtend({ 0, 0, 320, 320 }, {X座標,Y座標,幅,高さ});

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
		/**/
		/** @todo SDLは仮実装*/
		static void Circle(const Circle &円形, const Color& 色, int 太さ = 0)
		{
			if (太さ == 0)
			{
				circleTexture(色).DrawExtend({ 円形.x - 円形.radius, 円形.y - 円形.radius }, { 円形.x + 円形.radius, 円形.y + 円形.radius });
			} 
			else
			{
				circleTexture(色, int(円形.x - 円形.radius), int(円形.y - 円形.radius) ,int(円形.radius*2) , int(円形.radius*2) , 太さ);
			}
		}

		/** 中心と外接する四角形の大きさを指定して楕円を描画.*/
		/** @todo SDLは仮実装*/
		static void Oval(const Point &中心, int 幅, int 高さ, const Color& 色, int 太さ)
		{
			if (太さ == 0)
			{
				circleTexture(色).DrawExtend({ 中心.x - 幅 / 2, 中心.y - 高さ / 2 }, { 中心.x + 幅 / 2, 中心.y + 高さ / 2 });
			}
			else
			{
				circleTexture(色,int(中心.x - 幅 / 2), int(中心.y - 高さ / 2), int(中心.x + 幅 / 2), int(中心.y + 高さ / 2), 太さ);
			}
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