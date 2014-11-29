//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/IFont.h>
#include <Multimedia/SystemFont.h>
#include <Multimedia/Image.h>
#include <Framework/ImagePack.h>
#include <Multimedia/Window.h>

#include <map>
#include <iomanip>

namespace SDX
{
	/** 文字フォントを扱うクラス.*/
	/** 毎回レンダリングせず、ハッシュマップにImageを格納する*/
	/** 一度も表示していない文字が必要になった場合生成する*/
	/** \include FontSample.h*/
	class MixFont : public IFont
	{
	private:
		TTF_Font* handle = nullptr;//!<
		int size = 0;//!<
		int enterHeight = 0;//!<
		mutable std::map<int, Image*> hash;//!<

		static bool GetUTFSize(unsigned char 一文字目,int &文字長さ )
		{
			if (一文字目 < 0x20)
			{
				文字長さ = 1;
				return false;
			}

			if (一文字目 < 0x80){ 文字長さ = 1; }
			else if (一文字目 < 0xE0){ 文字長さ = 2; }
			else if (一文字目 < 0xF0){ 文字長さ = 3; }
			else { 文字長さ = 4; }
			return true;
		}

		/** UTFの文字列を一文字ずつ描画.*/
		void DrawUTFString(const Point &座標, const std::string &文字列 , const Color &描画色) const
		{
			Point 位置 = 座標;

			int charSize;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str() , charSize);
				str->SetColor(描画色);
				str->Draw(位置);
				位置.x += str->GetWidth();
			}
		}
		/** UTFの文字列を一文字ずつ拡大描画.*/
		void DrawUTFString(const Point &座標, double X拡大率, double Y拡大率, const std::string &文字列, const Color &描画色) const
		{
			Point 位置 = 座標;

			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);
				str->SetColor(描画色);
				str->DrawExtend(位置, { 位置.x + str->GetWidth()*X拡大率, 位置.y + str->GetWidth()*Y拡大率 });
				位置.x += str->GetWidth() * X拡大率;
			}
		}
		/** UTFの文字列を一文字ずつ回転拡大描画.*/
		void DrawRotateUTFString(const Point &座標, int X補正, int Y補正, double 拡大率, double 角度, const std::string &文字列, const Color &描画色) const
		{
			Point 位置 = 座標;

			int charSize = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);

				double x = 位置.x + std::cos(角度) * X補正 + std::cos(角度 + PAI / 2) * Y補正;
				double y = 位置.y + std::sin(角度) * X補正 + std::sin(角度 + PAI / 2) * Y補正;

				str->SetColor(描画色);
				str->DrawRotate({ x, y }, 拡大率, 角度);
				X補正 += int(str->GetWidth() * 拡大率);
			}
		}

		/** 文字イメージが生成されているか確認し、無ければ新規に生成する.*/
		Image* GetHash(const char* 文字 , int 文字長さ) const
		{
			if (handle == nullptr){ return nullptr; }

			int ID = 文字[0];
			if (文字長さ >= 2){ ID += 文字[1]*256; }
			if (文字長さ >= 3){ ID += 文字[2]*256*256; }
			if (文字長さ >= 4){ ID += 文字[3] * 256 * 256 * 256; }

			auto it = hash.find(ID);

			if (it == hash.end())
			{
				SDL_Surface* surface = TTF_RenderUTF8_Blended(handle, 文字, { 255, 255, 255 });
				SDL_Texture* moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), surface);
				Image* image = new Image(moji, surface->w, surface->h);
				hash[ID] = image;
				SDL_FreeSurface(surface);
				return image;
			}
			return it->second;
		}

		/** 指定した文字に対応する画像を設定.*/
		void SetHash(const char* 文字, int 文字長さ, Image *対応Image)
		{
			int ID = 文字[0];
			if (文字長さ >= 2){ ID += 文字[1] * 256; }
			if (文字長さ >= 3){ ID += 文字[2] * 256 * 256; }
			if (文字長さ >= 4){ ID += 文字[3] * 256 * 256 * 256; }

			hash[ID] = 対応Image;
		}

	public:

		MixFont() = default;

		MixFont(const char *フォント名, int 大きさ, int 改行高さ = 0)
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
					if (lead < 0x20){ continue; }
					else if (lead < 0x80){ charSize = 1; }
					else if (lead < 0xE0){ charSize = 2; }
					else if (lead < 0xF0){ charSize = 3; }
					else { charSize = 4; }

					幅 += GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize)->GetWidth();
				}

				最大幅 = std::max(幅, 最大幅);
			}
			return 最大幅;
		}

		/** 文字を描画.*/
		bool Draw(const Point &座標, Color 描画色, VariadicStream 描画する文字列) const override
		{
			if (handle == nullptr){ return false; }

			Point 位置 = 座標;

			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, it, 描画色);
				位置.y += this->enterHeight;
			}

			return true;
		}

		/** 文字を影付きで描画.*/
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
				DrawRotateUTFString(座標, X補正, Y補正, 拡大率, 角度, it, 描画色);
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
				DrawUTFString(位置, X拡大率, Y拡大率, it, 描画色);
				位置.y += this->enterHeight * Y拡大率;
			}

			return true;
		}

		/** 指定した文字に対応するImageをまとめて設定.*/
		void SetFont(const std::string &文字列, ImagePack &対応画像)
		{
			int charSize;
			int a = 0;
			for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }

				SetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(), charSize , 対応画像[a]);
			}
		}

		/** 指定した文字から連続してに対応するImageをまとめて設定.*/
		void SetFont(const std::string &文字列, ImagePack &対応画像 , int 登録数)
		{
			int charSize;
			int a = 0;
			auto it = 文字列.begin();
			if (!GetUTFSize(*it, charSize)){ return; }
			std::string str = 文字列.substr(0, charSize);
				
			for (int a = 0; a < 登録数;++a)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }
				SetHash(str.c_str(),charSize,対応画像[a]);
				if (str[charSize - 1] == 0xff)
				{
					str[charSize - 2]++;
					str[charSize - 1] = 0;
				}
				else
				{
					str[charSize - 1]++;
				}
			}
		}

		/** 指定した文字に対応するImageを設定.*/
		/** 文字列が2文字以上なら2文字目以降は無視*/
		void SetFont(const std::string &文字列, Image *対応画像)
		{
			int charSize;
			auto it = 文字列.begin();
			
			if (!GetUTFSize(*it, charSize)){ return; }
			SetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(), charSize, 対応画像);
		}
	};
}