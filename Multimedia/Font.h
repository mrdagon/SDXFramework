//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/IFont.h>
#include <Multimedia/SystemFont.h>
#include <Multimedia/Image.h>
#include <Multimedia/Window.h>
#include <Framework/Shape.h>

namespace SDX
{
	/** フォントデータを表すクラス.*/
	/** 描画の度にImageを生成する旧実装、MixFontの使用を推奨.*/
	/** \include Font.h*/
	class Font : public IFont
	{
	private:
		TTF_Font* handle = nullptr;//!<
		int size = 0;//!<
		int enterHeight = 0;//!<
	public:
		Font(){}

		Font(const char *フォント名, int 大きさ, int 行間 = 0)
		{
			Font::Load(フォント名, 大きさ, 行間);
		}

		/** メモリ上にフォントを作成する.*/
		/** 太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n*/
		/**	行間は0の場合、改行後の文字が上下くっつく。*/
		bool Load(const char *フォント名, int 大きさ, int 行間 = 0)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(フォント名,大きさ,行間); });
				return true;
			}

			if (handle != nullptr){ return false; }

			this->size = 大きさ;
			this->enterHeight = 行間 + 大きさ;

			handle = TTF_OpenFont(フォント名, 大きさ);
			return (handle != nullptr);
		}

		/** フォントをメモリから開放する.*/
		bool Release() const
		{
			if (handle != nullptr) return false;

			TTF_CloseFont(handle);
			return true;
		}

		/** フォントのハンドルを取得.*/
		TTF_Font* GetHandle() const
		{
			return handle;
		}

		/** フォントから画像を生成*/
		Image MakeImage(Color 文字色, bool 反転フラグ, VariadicStream 描画する文字列) const
		{
			int 幅 = GetDrawStringWidth(描画する文字列);
			int 高さ = ((int)描画する文字列.StringS.size() - 1) * enterHeight + size;
			int Y座標 = 0;

			std::vector<SDL_Surface*> surfaces;

			for (auto it : 描画する文字列.StringS)
			{
				SDL_Surface* surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
				幅 = std::max(幅, surface->w);
				surfaces.push_back(surface);
			}

			SDL_Surface* toRend = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
			SDL_Renderer* render = SDL_CreateSoftwareRenderer(toRend);

			for (auto it : surfaces)
			{
				SDL_Texture* texture = SDL_CreateTextureFromSurface(render, it);

				SDL_Rect temp = { 0, Y座標, it->w, it->h };
				SDL_RenderCopy(render, texture, 0, &temp);

				Y座標 += this->enterHeight;

				SDL_FreeSurface(it);
				SDL_DestroyTexture(texture);
			}

			Image image = Image(SDL_CreateTextureFromSurface(Screen::GetHandle(), toRend), 幅, 高さ);
			SDL_FreeSurface(toRend);
			SDL_DestroyRenderer(render);

			return image;
		}

		/** 大きさを取得.*/
		int GetSize() const
		{
			return this->size;
		}

		/** 描画時の幅を取得[未実装].*/ 
		int GetDrawStringWidth(VariadicStream 幅を計算する文字列) const
		{
			int 幅 = 0;

			return 幅;
		}

		/** 文字を描画.*/
		bool Draw(const Point &座標, Color 色, VariadicStream 描画する文字列) const override
		{
			if (!handle) return false;

			SDL_Surface* image;
			SDL_Texture* moji;
			SDL_Rect temp;
			int Y座標 = (int)座標.y;

			for (auto it : 描画する文字列.StringS)
			{
				if (it.size() > 0)
				{
					image = TTF_RenderUTF8_Blended(handle, it.c_str(), 色);

					moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
					temp = { (int)座標.x, Y座標, image->w, image->h };
					SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);

					SDL_FreeSurface(image);
					SDL_DestroyTexture(moji);
				}
				Y座標 += this->enterHeight;
			}

			return true;
		}

		/** 文字を回転して描画.*/
		bool DrawShadow(const Point &座標, Color 表色, Color 影色, VariadicStream 描画する文字列) const
		{
			Draw({ 座標.x + 1, 座標.y + 1 }, 影色, 描画する文字列);
			return Draw(座標, 表色, 描画する文字列);
		}

		/** 文字を回転して描画.*/
		/** 呼び出す度に画像イメージを作成するので処理は重い*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const override
		{
			Image 文字イメージ = MakeImage(描画色, 反転フラグ, 描画する文字列);
			文字イメージ.DrawRotate(座標, 拡大率, 角度, 反転フラグ);
			文字イメージ.Release();
			return true;
		}

		/** 拡大率を指定して文字を描画.*/
		bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
		{
			if (!handle) return false;

			SDL_Surface* image;
			SDL_Texture* moji;
			SDL_Rect temp;
			int Y座標 = (int)座標.y;

			for (auto it : 描画する文字列.StringS)
			{
				if (it.size() > 0)
				{
					image = TTF_RenderUTF8_Blended(handle, it.c_str(), 描画色);

					moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
					temp = { (int)座標.x, Y座標, int(image->w * X拡大率), int(image->h * Y拡大率) };

					SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);
					SDL_FreeSurface(image);
					SDL_DestroyTexture(moji);
				}

				Y座標 += int(this->enterHeight * Y拡大率);
			}

			return true;
		}
	};
}