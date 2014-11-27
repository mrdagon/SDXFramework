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
	/** 文字フォントを扱うクラス.*/
	/** 毎回レンダリングせず、ハッシュマップにデータを格納する*/
	/** \include FontSample.h*/
	class Font : public IFont
	{
	private:
		TTF_Font* handle = nullptr;//!<
		int size = 0;//!<
		int enterHeight = 0;//!<
		mutable std::map<std::string, Image*> hash;//!<

		/** UTFの文字列を一文字ずつ描画.*/
		void DrawUTFString(const Point &座標, const std::string &文字列) const
		{
			Point 位置 = 座標;

			unsigned char lead;
			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				lead = *it;
				if (lead < 0x80){ charSize = 1; }
				else if (lead < 0xE0){ charSize = 2; }
				else if (lead < 0xF0){ charSize = 3; }
				else { charSize = 4; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str());
				str->Draw(位置);
				位置.x += str->GetWidth();
			}
		}
		/** UTFの文字列を一文字ずつ拡大描画.*/
		void DrawUTFString(const Point &座標, double X拡大率, double Y拡大率, const std::string &文字列) const
		{
			Point 位置 = 座標;

			unsigned char lead;
			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				lead = *it;
				if (lead < 0x80){ charSize = 1; }
				else if (lead < 0xE0){ charSize = 2; }
				else if (lead < 0xF0){ charSize = 3; }
				else { charSize = 4; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str());
				str->DrawExtend(位置, { 位置.x + str->GetWidth()*X拡大率, 位置.y + str->GetWidth()*Y拡大率 });
				位置.x += str->GetWidth();
			}
		}
		/** UTFの文字列を一文字ずつ回転拡大描画.*/
		void DrawRotateUTFString(const Point &座標, int X補正, int Y補正, double 拡大率, double 角度, const std::string &文字列) const
		{
			Point 位置 = 座標;

			unsigned char lead;
			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				lead = *it;
				if (lead < 0x80){ charSize = 1; }
				else if (lead < 0xE0){ charSize = 2; }
				else if (lead < 0xF0){ charSize = 3; }
				else { charSize = 4; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str());

				double x = 位置.x + std::cos(角度) * X補正 + std::cos(角度 + PAI / 2) * Y補正;
				double y = 位置.y + std::sin(角度) * X補正 + std::sin(角度 + PAI / 2) * Y補正;

				str->DrawRotate({ x, y }, 拡大率, 角度);
				X補正 += int(str->GetWidth() * 拡大率);
			}
		}

		/** 文字イメージが生成されているか確認し、無ければ新規に生成する.*/
		Image* GetHash(const char* 文字) const
		{
			if (handle == nullptr){ return nullptr; }

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

	public:

		Font() = default;

		Font(const char *フォント名, int 大きさ, int 改行高さ = 0)
		{
			Load(フォント名, 大きさ, 改行高さ);
		}

		/** メモリ上にフォントを作成する.*/
		/** 太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n*/
		/**	改行高さは0の場合、改行後の文字が上下くっつく。*/
		bool Load(const char *フォント名, int 大きさ, int 改行高さ = 0)
		{
			if (handle != nullptr){ return false; }

			Release();
			this->size = 大きさ;
			this->enterHeight = 改行高さ + 大きさ;
			handle = TTF_OpenFont(フォント名, 大きさ);
			return true;
		}

		/** フォントハンドルをメモリから開放する.*/
		bool Release() const
		{
			if (handle != nullptr){ return false; }
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

		/** FontからImageを生成.*/
		Image MakeImage(Color 文字色, bool 反転フラグ, VariadicStream 描画する文字列) const
		{
			if (handle == nullptr){ return Image(); }

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

		/** 大きさを取得.*/
		int GetSize() const
		{
			return this->size;
		}

		/** 描画時の幅を取得.*/
		int GetDrawStringWidth(VariadicStream 幅を計算する文字列) const
		{
			if (handle == nullptr){ return 0; }

			int 最大幅 = 0;

			for (auto 文字列 : 幅を計算する文字列.StringS)
			{
				unsigned char lead;
				int charSize = 0;
				int 幅 = 0;

				for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
				{
					lead = *it;
					if (lead < 0x80){ charSize = 1; }
					else if (lead < 0xE0){ charSize = 2; }
					else if (lead < 0xF0){ charSize = 3; }
					else { charSize = 4; }

					幅 += GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str())->GetWidth();
				}

				最大幅 = std::max(幅, 最大幅);
			}
			return 最大幅;
		}

		/** 文字を描画.*/
		bool Draw(const Point &座標, Color 色, VariadicStream 描画する文字列) const override
		{
			if (handle == nullptr){ return false; }

			Point 位置 = 座標;

			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, it);
				位置.y += this->enterHeight;
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
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色, bool 反転フラグ, VariadicStream 描画する文字列) const override
		{
			if (handle == nullptr){ return false; }

			int 行数 = 描画する文字列.StringS.size();

			int X補正 = int(-GetDrawStringWidth(描画する文字列) * 拡大率 * 0.5);
			int Y補正 = int(-enterHeight * 拡大率 * 0.5*行数);

			for (auto it : 描画する文字列.StringS)
			{
				DrawRotateUTFString(座標, X補正, Y補正, 拡大率, 角度, it);
				Y補正 += int(enterHeight * 拡大率);
			}

			return true;
		}

		/** 拡大率を指定して文字を描画.*/
		bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
		{
			if (handle == nullptr){ return false; }

			Point 位置 = 座標;

			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, X拡大率, Y拡大率, it);
				位置.y += this->enterHeight * Y拡大率;
			}

			return true;
		}
	};
}