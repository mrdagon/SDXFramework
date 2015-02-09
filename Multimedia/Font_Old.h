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

namespace SDX
{

/** 旧フォントクラス.*/
/** 毎回レンダリングするので遅い*/
/** \include Font.h*/
class FontOld : public IFont
{
private:
	TTF_Font* handle = nullptr;//!<
	int size = 0;
	int thick = 0;
	int enterHeight = 0;
public:
	FontOld(){}
	
	/** デフォルトコンストラクタ.*/
	FontOld(const char *フォント名, int 大きさ, int 太さ = 1, int 改行高さ = 0)
	{
		Load( フォント名 , 大きさ , 太さ , 改行高さ);
	}

	/** メモリ上にフォントを作成する.*/
	/** 太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n*/
	/**	改行高さは0の場合、改行後の文字が上下くっつく。*/
	/**	@todo 太さが無効*/
	bool Load(const char *フォント名,int 大きさ ,int 太さ = 1 , int 改行高さ = 0)
	{
		Release();
		this->size = 大きさ;
		this->enterHeight = 改行高さ + 大きさ;
		this->thick = 太さ;

		handle = TTF_OpenFont(フォント名,大きさ);
		return (handle != nullptr);
	}
			
	/** フォントをメモリから開放する.*/
	bool Release() const
	{
		if(handle != nullptr) return false;

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
		int 幅   = GetDrawStringWidth(描画する文字列);
		int 高さ = ((int)描画する文字列.StringS.size()-1) * enterHeight + size;
		int Y座標 = 0;

		std::vector<SDL_Surface*> surfaces;
		
		for (auto it : 描画する文字列.StringS)
		{
			SDL_Surface* surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
			幅 = std::max(幅, surface->w);
			surfaces.push_back( surface );
		}
		
		SDL_Surface* toRend = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
		SDL_Renderer* render = SDL_CreateSoftwareRenderer( toRend );
		
		for (auto it : surfaces)
		{
			SDL_Texture* texture = SDL_CreateTextureFromSurface( render , it);

			SDL_Rect temp = { 0, Y座標, it->w, it->h };
			SDL_RenderCopy( render , texture , 0, &temp);

			Y座標 += this->enterHeight;

			SDL_FreeSurface(it);
			SDL_DestroyTexture( texture );
		}
		//描画先を戻す
		Image image(SDL_CreateTextureFromSurface(Screen::GetHandle(), toRend),幅,高さ);

		SDL_FreeSurface(toRend);
		SDL_DestroyRenderer(render);

		return image;
	}

	/** 大きさを取得.*/
	int GetSize() const
	{
		return this->size;
	}
			
	/** 太さを取得.*/
	int Getthick() const
	{
		return this->thick;
	}
			
	/** 文字を描画.*/
	bool Draw(const Point &座標, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const override
	{        
		if( !handle ) return false;
		
		SDL_Surface* image;
		SDL_Texture* moji;
		SDL_Rect temp;

		int y = (int)座標.y;

		for( auto it : 描画する文字列.StringS)
		{
			if(it.size() > 0)
			{
				image = TTF_RenderUTF8_Blended(handle, it.c_str() , 描画色);
			
				moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
				temp = { (int)座標.x, y, image->w, image->h };
				SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);

				SDL_FreeSurface(image);
				SDL_DestroyTexture(moji);
			}
			y += this->enterHeight;
		}

		return true;
	}

	/** 文字を回転して描画.*/
	/** 呼び出す度に画像イメージを作成するので処理は重い*/
	bool DrawRotate(const Point &座標, double 拡大率, double 角度, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const override
	{
		Image 文字イメージ = MakeImage(描画色, 反転フラグ, 描画する文字列);
		文字イメージ.DrawRotate(座標,拡大率,角度,反転フラグ);
		文字イメージ.Release();
		return true;
	}

	/** 拡大率を指定して文字を描画.*/
	bool DrawExtend(const Point &座標, double X軸拡大率, double Y軸拡大率, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const override
	{
		if( !handle ) return false;
		
		SDL_Surface* image;
		SDL_Texture* moji;
		SDL_Rect temp;

		int y = (int)座標.y;

		for (auto it:描画する文字列.StringS)
		{
			if(it.size() > 0 )
			{
				image = TTF_RenderUTF8_Blended(handle, it.c_str() , 描画色);
			
				moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
				temp = { (int)座標.x, y, int(image->w * X軸拡大率), int(image->h * Y軸拡大率) };

				SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);
				SDL_FreeSurface(image);
				SDL_DestroyTexture(moji);
			}

			y += int(this->enterHeight * Y軸拡大率);
		}

		return true;
	}        

};
}