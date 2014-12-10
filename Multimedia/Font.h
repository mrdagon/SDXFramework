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
	/** TrueTypeFontとBMPFontをまとめて扱うクラス.*/
	/** 毎回レンダリングせず、ハッシュマップにImageを格納する*/
	/** 一度も表示していない文字が必要になった場合生成し以後使いまわす*/
	/** @todo 高さが違う文字が混ざった場合の仕様が未定、現状上揃え*/
	/** \include Font.h*/
	class Font : public IFont
	{
	private:
		TTF_Font* handle = nullptr;//!<
		bool isBlendRender;
		int size = 0;//!<
		int enterHeight = 0;//!<
		mutable std::map<int, Image*> hash;//!<

		int style = TTF_STYLE_NORMAL;//!<

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
				if (handle == nullptr && *it == ' ')
				{
					位置.x += size;
					continue;
				}

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str() , charSize);
				if (str == nullptr){ continue; }

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
				if (handle == nullptr && *it == ' ')
				{
					位置.x += size * X拡大率;
					continue;
				}

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);
				if (str == nullptr){ continue; }

				str->SetColor(描画色);
				str->DrawExtend({ 位置.x , 位置. y ,  str->GetWidth()*X拡大率, str->GetHeight()*Y拡大率 });
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
				if (handle == nullptr && *it == ' ')
				{
					位置.x += size * 拡大率;
					continue;
				}

				Image* str = GetHash(文字列.substr(std::distance(文字列.begin(), it), charSize).c_str(),charSize);
				if (str == nullptr){ continue; }

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
			int ID = 文字[0];
			if (文字長さ >= 2){ ID += 文字[1]*256; }
			if (文字長さ >= 3){ ID += 文字[2]*256*256; }
			if (文字長さ >= 4){ ID += 文字[3] * 256 * 256 * 256; }

			auto it = hash.find(ID);

			if (it == hash.end())
			{
				if (handle == nullptr){ return nullptr; }

				SDL_Surface* surface;

				if (isBlendRender)
				{
					surface = TTF_RenderUTF8_Blended(handle, 文字, { 255, 255, 255 });
				}
				else
				{
					surface = TTF_RenderUTF8_Solid(handle, 文字, { 255, 255, 255 });
				}

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

		Font() = default;

		/** コンストラクタ*/
		Font(const char *フォント名, int 大きさ, int 行間 = 0 , bool 高品質レンダリングフラグ = true )
		{
			Load(フォント名, 大きさ, 行間, 高品質レンダリングフラグ);
		}

		/** フォントを作成する.*/
		/**	行間は0の場合、改行後の文字が上下くっつく。\n*/
		/** BMPフォント専用にしたい場合、フォント名は無効な物を入れる*/
		bool Load(const char *フォント名, int 大きさ, int 行間 = 0, bool 高品質レンダリングフラグ = true )
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(フォント名, 大きさ, 行間, 高品質レンダリングフラグ); });
				return true;
			}

			if (handle != nullptr){ return false; }

			this->size = 大きさ;
			this->enterHeight = 行間 + 大きさ;
			isBlendRender = 高品質レンダリングフラグ;
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
		Image MakeImage(Color 文字色, bool 反転フラグ, const VariadicStream &描画する文字列) const
		{
			if (handle == nullptr){ return Image(); }

			int 幅 = GetDrawStringWidth(描画する文字列);
			int 高さ = ((int)描画する文字列.StringS.size() - 1) * enterHeight + size;
			int Y座標 = 0;

			std::vector<SDL_Surface*> surfaces;
			SDL_Surface* surface;

			for (auto it : 描画する文字列.StringS)
			{
				if (isBlendRender)
				{
					surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
				}
				else
				{
					surface = TTF_RenderUTF8_Solid(handle, it.c_str(), 文字色);
				}

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
		int GetDrawStringWidth(const VariadicStream &幅を計算する文字列) const
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
		bool Draw(const Point &座標, const Color &描画色, const VariadicStream &描画する文字列) const override
		{
			Point 位置 = 座標;

			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, it, 描画色);
				位置.y += this->enterHeight;
			}

			return true;
		}

		/** 文字を影付きで描画.*/
		bool DrawShadow(const Point &座標, Color 表色, Color 影色, const VariadicStream &描画する文字列) const
		{
			Draw({ 座標.x + 1, 座標.y + 1 }, 影色, 描画する文字列);
			return Draw(座標, 表色, 描画する文字列);
		}

		/** 文字を回転して描画.*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, const Color &描画色, bool 反転フラグ, const VariadicStream &描画する文字列) const override
		{
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
		bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, const Color &描画色, const VariadicStream &描画する文字列) const override
		{
			Point 位置 = 座標;

			for (auto it : 描画する文字列.StringS)
			{
				DrawUTFString(位置, X拡大率, Y拡大率, it, 描画色);
				位置.y += this->enterHeight * Y拡大率;
			}

			return true;
		}

		/** 指定した文字に対応するImageを設定.*/
		/** 文字列が2文字以上なら2文字目以降は無視*/
		void SetImage(const std::string &文字, Image *対応画像)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ SetImage(文字,対応画像); });
				return;
			}

			int charSize;
			auto it = 文字.begin();

			if (!GetUTFSize(*it, charSize)){ return; }
			SetHash(文字.substr(std::distance(文字.begin(), it), charSize).c_str(), charSize, 対応画像);
		}

		/** 指定した文字から連続してに対応するImageをまとめて設定.*/
		/** 例えば文字列="0"で登録数=10なら0～9までを登録*/
		/** アルファベットや数字用*/
		void SetImageS(const std::string &文字列, ImagePack *対応画像, int 登録数)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ SetImageS(文字列, 対応画像,登録数); });
				return;
			}

			int charSize;
			int a = 0;
			auto it = 文字列.begin();
			if (!GetUTFSize(*it, charSize)){ return; }
			std::string str = 文字列.substr(0, charSize);
				
			for (int a = 0; a < 登録数;++a)
			{
				if (!GetUTFSize(*it, charSize)){ continue; }
				SetHash(str.c_str(),charSize,対応画像[0][a]);
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
	};
}