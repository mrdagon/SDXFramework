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

		/** Rendererに円を描画、処理はかなり重い.*/
		static void MakeCircle(SDL_Renderer* renderer,int x1, int y1,int x2, int y2 , int alpha)
		{
			//実装参考[http://hp.vector.co.jp/authors/VA028002/sdl/]
			//パブリックドメインなのでわりとコピペしてます
			int r;
			int dx, dy;
			int xa, ya, xb, yb;
			int f;

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer,255,255,255,alpha);

			dx = x2 - x1 < 0 ? x1 - x2 : x2 - x1;
			dy = y2 - y1 < 0 ? y1 - y2 : y2 - y1;
			
			r = dx / 2;
			xa = r;
			ya = 0;
			f = 3 - 2 * r;
			x1 += dx / 2;
			y1 += dy / 2;
			x2 = x1 + dx % 2;
			y2 = y1 + dy % 2;
			while (xa >= ya){
				xb = (xa * dy) / dx;
				yb = (ya * dy) / dx;
				
				SDL_RenderDrawLine(renderer, xa + x2, -yb + y1,xa + x2, yb + y2); /*A*/
				SDL_RenderDrawLine(renderer, ya + x2, -xb + y1, ya + x2, xb + y2); /*B*/
				SDL_RenderDrawLine(renderer, -ya + x1, -xb + y1, -ya + x1, xb + y2); /*C*/
				SDL_RenderDrawLine(renderer, -xa + x1, -yb + y1, -xa + x1, yb + y2); /*D*/

				if (f >= 0){
					xa--;
					f -= 4 * xa;
				}
				ya++;
				f += 4 * ya + 2;
			}
		}
		
		/** 円.*/
		static Image& GetCircle(const Color &描画色, int X座標 = 0, int Y座標 = 0, int 幅 = 0, int 高さ = 0, int 太さ = 0)
		{
			static Image circleA;
			static Image circleB;
			static Image circleC;

			if (circleA.GetHandle() == nullptr)
			{
				circleA.Make(320, 320);
				circleB.Make(320, 320);
				circleC.Make(320, 320);

				SDL_SetRenderTarget(Screen::GetHandle(), circleA.GetHandle());
				MakeCircle(Screen::GetHandle(), 0, 0, 320, 320,255);
				SDL_SetRenderTarget(Screen::GetHandle(), circleC.GetHandle());
				Drawing::Rect({ 0, 0, 320, 320 }, Color::White, true);
				SDL_SetRenderTarget(Screen::GetHandle(), nullptr);
			}

			if (太さ <= 0)
			{
				circleA.SetColor(描画色);
				return circleA;
			}
			else
			{
				太さ = std::max(太さ * 640 / (幅 + 高さ), 2);//最低2

				SDL_SetRenderTarget(Screen::GetHandle(),circleB.GetHandle());
				circleA.SetColor(Color::White);
				circleA.Draw({ 0, 0 });
				circleA.SetColor(Color::Black);
				circleA.DrawExtend({ 太さ, 太さ },{ 320 - 太さ, 320 - 太さ });
				//白の場合乗算処理が不要
				if (描画色.GetRed() != 255 || 描画色.GetGreen() || 255 && 描画色.GetBlue() || 255)
				{
					SDL_SetRenderTarget(Screen::GetHandle(), circleC.GetHandle());
					circleA.SetColor(Color::Black);
					circleA.Draw({ 0, 0 });
					circleA.SetColor(Color::White);
					circleA.DrawExtend({ 太さ, 太さ }, { 320 - 太さ, 320 - 太さ });
				}
				SDL_SetRenderTarget(Screen::GetHandle(), nullptr);

				SDL_Rect rect2 = { X座標, Y座標, 幅, 高さ };
				if (描画色.GetRed() != 255 || 描画色.GetGreen() || 255 && 描画色.GetBlue() || 255)
				{
					SDL_SetTextureBlendMode(circleC.GetHandle(), (SDL_BlendMode)BlendMode::Mula);
					SDL_RenderCopy(Screen::GetHandle(), circleC.GetHandle(), nullptr, &rect2);
				}
				SDL_SetTextureBlendMode(circleB.GetHandle(), (SDL_BlendMode)BlendMode::Add);
				SDL_SetTextureAlphaMod(circleB.GetHandle(), 255 );
				SDL_SetTextureColorMod(circleB.GetHandle(), 描画色.GetRed(), 描画色.GetGreen(), 描画色.GetBlue());
				SDL_RenderCopy(Screen::GetHandle(), circleB.GetHandle(), nullptr, &rect2);		
				return circleB;
			}
		}

		/** 正三角形.*/
		static void GetTriangle(const Color &描画色, const Point &中心座標 = {0,0}, int 辺の長さ = 0, double 角度 = 0, int 太さ = 0)
		{
			static Image imageA;
			static Image imageB;
			static Image imageC;

			const int WSIZE = 173*2;
			const int HSIZE = 200*2;

			if (imageA.GetHandle() == nullptr)
			{
				imageA.Make(WSIZE, HSIZE);//高さ=√3の近似
				imageB.Make(WSIZE, HSIZE);
				imageC.Make(WSIZE, HSIZE);

				SDL_SetRenderTarget(Screen::GetHandle(), imageA.GetHandle());
				SDL_SetRenderDrawBlendMode(Screen::GetHandle(), SDL_BLENDMODE_NONE);
				SDL_SetRenderDrawColor(Screen::GetHandle(), 255, 255, 255, 255);
				for (int y = 0; y < HSIZE/2; ++y)
				{
					int x = WSIZE * y * 2 / HSIZE;
					SDL_RenderDrawLine(Screen::GetHandle(), 0, y, x, y); /*A*/
					SDL_RenderDrawLine(Screen::GetHandle(), 0, HSIZE-y-1, x, HSIZE-y-1); /*A*/
				}

				SDL_SetRenderTarget(Screen::GetHandle(), imageC.GetHandle());
				Drawing::Rect({ 0, 0, WSIZE, HSIZE }, Color::White, true);
				SDL_SetRenderTarget(Screen::GetHandle(), nullptr);
			}

			const double 拡大率 = double(辺の長さ) / HSIZE;
			const int width = int(WSIZE * 拡大率 / 2);
			const int height = int(HSIZE * 拡大率 / 2);
			SDL_Rect rect2 = { (int)中心座標.x - width, (int)中心座標.y - height, width * 2, height * 2 };
			SDL_Point center = { width * 2 / 3, height };

			if (太さ <= 0)
			{
				imageA.SetColor(描画色);
				imageA.RGBACulculate();
				SDL_RenderCopyEx(Screen::GetHandle(), imageA.GetHandle(), nullptr, &rect2, 角度 / DEG, &center, SDL_RendererFlip(false));
			}
			else
			{
				太さ = std::max(太さ * WSIZE* 2  / (辺の長さ), 2);//最低2

				SDL_SetRenderTarget(Screen::GetHandle(), imageB.GetHandle());
				imageA.SetColor(Color::White);
				imageA.Draw({ 0, 0 });
				imageA.SetColor(Color::Black);
				imageA.DrawExtend({ 太さ/2, 太さ }, { WSIZE - 太さ, HSIZE - 太さ });
				//白の場合乗算処理が不要
				if (描画色.GetRed() != 255 || 描画色.GetGreen() || 255 && 描画色.GetBlue() || 255)
				{
					SDL_SetRenderTarget(Screen::GetHandle(), imageC.GetHandle());
					imageA.SetColor(Color::Black);
					imageA.Draw({ 0, 0 });
					imageA.SetColor(Color::White);
					imageA.DrawExtend({ 太さ/2, 太さ }, { WSIZE - 太さ, HSIZE - 太さ });
				}
				SDL_SetRenderTarget(Screen::GetHandle(), nullptr);

				if (描画色.GetRed() != 255 || 描画色.GetGreen() || 255 && 描画色.GetBlue() || 255)
				{
					SDL_SetTextureBlendMode(imageC.GetHandle(), (SDL_BlendMode)BlendMode::Mula);
					SDL_RenderCopyEx(Screen::GetHandle(), imageC.GetHandle(), nullptr, &rect2, 角度/DEG, &center, SDL_RendererFlip(false));
				}
				SDL_SetTextureBlendMode(imageB.GetHandle(), (SDL_BlendMode)BlendMode::Add);
				SDL_SetTextureAlphaMod(imageB.GetHandle(), 255);
				SDL_SetTextureColorMod(imageB.GetHandle(), 描画色.GetRed(), 描画色.GetGreen(), 描画色.GetBlue());
				SDL_RenderCopyEx(Screen::GetHandle(), imageB.GetHandle(), nullptr, &rect2, 角度/DEG, &center, SDL_RendererFlip(false));
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
		static void SetDefaultFont(const char* フォント名, int 大きさ,int 行間 , FontRender 品質 = FontRender::Solid)
		{
			GetFont().Load(フォント名, 大きさ,行間,品質);
		}

		/** 始点と終点を結ぶ直線を描画.*/
		/** @todo 太さ指定不可*/
		static void Line(const Point &始点, const Point &終点, Color 色, int 太さ = 1)
		{
			if (太さ <= 1)
			{
				RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
				SDL_RenderDrawLine(Screen::GetHandle(), (int)始点.x, (int)始点.y, (int)終点.x, (int)終点.y);
			}
			else
			{

			}
		}

		/** 左上の座標と大きさを指定して矩形を描画.*/
		static void Rect(const Rect &領域, Color 色, bool 塗りつぶしフラグ)
		{
			SDL_Rect buf = { (int)領域.GetLeft(), (int)領域.GetTop(), (int)領域.GetW(), (int)領域.GetH() };
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			if (塗りつぶしフラグ)
			{
				SDL_RenderFillRect(Screen::GetHandle(), &buf);
			}
			else
			{
				SDL_RenderDrawRect(Screen::GetHandle(), &buf);
			}
		}

		/** 中心と半径を指定して円を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		static void Circle(const Circle &円形, const Color& 色, int 太さ = 0)
		{
			if (太さ <= 0)
			{
				GetCircle(色).DrawExtend({ 円形.x - 円形.radius, 円形.y - 円形.radius }, { 円形.x + 円形.radius, 円形.y + 円形.radius });
			} 
			else
			{
				GetCircle(色, int(円形.x-円形.radius),int(円形.y-円形.radius), int(円形.radius*2), int(円形.radius*2) , 太さ);
			}
		}

		/** 中心と外接する四角形の大きさを指定して楕円を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		static void Oval(const Point &中心, int 幅, int 高さ, const Color& 色, int 太さ = 0)
		{
			if (太さ <= 0)
			{
				GetCircle(色).DrawExtend({ 中心.x - 幅 / 2, 中心.y - 高さ / 2 }, { 中心.x + 幅 / 2, 中心.y + 高さ / 2 });
			}
			else
			{
				GetCircle(色, 幅 + 高さ, 太さ).DrawExtend({ 中心.x - 幅 / 2, 中心.y - 高さ / 2 }, { 中心.x + 幅 / 2, 中心.y + 高さ / 2 });
			}
		}

		/** 頂点を指定して多角形を描画.*/
		static void Polygon(std::vector<Point> 頂点, Color 色)
		{
			RGBACulculate(色.GetRed(), 色.GetGreen(), 色.GetBlue());
			
			for (unsigned int a = 0; a < 頂点.size() ; ++a)
			{
				if (a == 頂点.size() - 1)
				{
					SDL_RenderDrawLine(Screen::GetHandle(), (int)頂点[a].x, (int)頂点[a].y, (int)頂点[0].x, (int)頂点[0].y);
				}
				else
				{
					SDL_RenderDrawLine(Screen::GetHandle(), (int)頂点[a].x, (int)頂点[a].y, (int)頂点[a + 1].x, (int)頂点[a + 1].y);
				}

			}
		}

		/** 正三角形を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		static void Triangle(const Point &中心座標,int 辺の長さ , double 角度 , Color 描画色 , int 太さ = 0)
		{
			if (太さ <= 0)
			{
				GetTriangle(描画色, 中心座標, 辺の長さ, 角度);
			}
			else
			{
				GetTriangle(描画色, 中心座標, 辺の長さ, 角度, 太さ);
			}
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