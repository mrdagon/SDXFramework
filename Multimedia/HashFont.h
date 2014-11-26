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

#include <map>
#include <iomanip>

namespace SDX
{
	/** フォントデータを表すクラス[未実装].@todo*/ 
	/** 毎回レンダリングせず、ハッシュマップにデータを格納する*/
	/** \include FontSample.h*/
	class HashFont : public IFont
	{
	private:
		TTF_Font* handle = nullptr;//!<
		int size = 0;//!<
		int enterHeight = 0;//!<
		mutable std::map<std::string, Image*> hash;//!<

	public:

		HashFont(){}

		HashFont(const char *フォント名, int 大きさ, int 改行高さ = 0)
		{
			Load(フォント名, 大きさ, 改行高さ);
		}

		/** メモリ上にフォントを作成する.*/
		/** 太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n*/
		/**	改行高さは0の場合、改行後の文字が上下くっつく。*/
		bool Load(const char *フォント名, int 大きさ, int 改行高さ = 0)
		{
			Release();
			this->size = 大きさ;
			this->enterHeight = 改行高さ + 大きさ;
			handle = TTF_OpenFont(フォント名, 大きさ);
			return true;
		}

		/** フォントをメモリから開放する.*/
		bool Release() const
		{
			if (handle != nullptr) return false;
			TTF_CloseFont(handle);
			for (auto && it : hash)
			{
				it.second->Release();
			}
			return true;
		}

		/** フォントのハンドルを取得.*/
		TTF_Font* GetHandle() const
		{
			return handle;
		}

		/**.*/
		Image MakeImage(Color 文字色, bool 反転フラグ, VariadicStream 描画する文字列) const
		{
			int 幅 = GetDrawStringWidth(描画する文字列);
			int 高さ = ((int)描画する文字列.StringS.size() - 1) * enterHeight + size;
			int Y座標 = 0;

			std::vector<SDL_Surface*> surfaces;
			SDL_Surface* surface;

			for (auto it : 描画する文字列.StringS)
			{
				surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
				幅 = std::max(幅, surface->w);
				surfaces.push_back(surface);
			}

			SDL_Surface* toRend = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
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
			//描画先を戻す
			Image image(SDL_CreateTextureFromSurface(Screen::GetHandle(), toRend), 幅, 高さ);

			SDL_FreeSurface(toRend);
			SDL_DestroyRenderer(render);

			return image;
		}

		/**.*/
		Image* GetHash(const char* 文字) const
		{
			auto it = hash.find(文字);

			if (it == hash.end())
			{
				SDL_Surface* surface = TTF_RenderUTF8_Blended(handle, 文字, { 255, 255, 255 });
				SDL_Texture* moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), surface);
				Image* image = new Image(moji, surface->w, surface->h);
				std::map<std::string, Image*> *map = &hash;
				map->operator[](文字) = image;
				SDL_FreeSurface(surface);
				return image;
			}
			return it->second;
		}

		/** 大きさを取得.*/
		int GetSize() const
		{
			return this->size;
		}

		/** 描画時の幅を取得.*/
		int GetDrawStringWidth(VariadicStream 幅を計算する文字列) const
		{
			int 幅 = 0;
			std::string 文字列 = 幅を計算する文字列.StringS[0];

			unsigned char lead;
			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				lead = *it;
				if (lead < 0x80)         charSize = 1;
				else if (lead < 0xE0)   charSize = 2;
				else if (lead < 0xF0)   charSize = 3;
				else                    charSize = 4;

				幅 += GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str())->GetWidth();
			}

			return 幅;
		}
		
		/**.*/
		void DrawUTFString(const Point &座標, const std::string &文字列) const
		{
			Point 位置 = 座標;

			unsigned char lead;
			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				lead = *it;
				if (lead < 0x80)         charSize = 1;
				else if (lead < 0xE0)   charSize = 2;
				else if (lead < 0xF0)   charSize = 3;
				else                    charSize = 4;

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str());
				str->Draw(位置);
				位置.x += str->GetWidth();
			}
		}

		/** 文字を描画.*/
		bool Draw(const Point &座標, Color 色, VariadicStream 描画する文字列) const override
		{
			Point 位置 = 座標;

			if (!handle) return false;
			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, it);
				位置.y += this->enterHeight;
			}

			return true;
		}

		/** 文字を回転して描画.*/
		/** 呼び出す度に画像イメージを作成するので処理は重い*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const override
		{
			return false;
		}

		/** 拡大率を指定して文字を描画.*/
		bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
		{
			Point 位置 = 座標;

			SDL_Surface* image;
			SDL_Texture* moji;
			SDL_Rect temp;
			for (auto it : 描画する文字列.StringS)
			{
				image = TTF_RenderUTF8_Blended(handle, it.c_str(), 描画色);

				moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
				temp = { (int)位置.x, (int)位置.y, int(image->w * X拡大率), int(image->h * Y拡大率) };

				SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);

				位置.y += int(this->enterHeight * Y拡大率);
				SDL_FreeSurface(image);
				SDL_DestroyTexture(moji);
			}
		}
	};
}