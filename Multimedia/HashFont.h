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

#include <iomanip>

namespace SDX
{
/** フォントデータを表すクラス[未実装].*/
/** 毎回レンダリングせず、ハッシュマップにデータを格納する*/
/**    \include FontSample.h*/
class HashFont : public IFont
{
private:
    FontHandle handle = NULL_HANDLE;
    int size = 0;
    int thick = 0;
    int enterHeight = 0;
    mutable std::map<std::string, Image*> hash;

public:

    HashFont(){}
    
    HashFont(const char *フォント名, int 大きさ, int 太さ = 1, int 改行高さ = 0, FontType フォントタイプ = FontType::Normal)
    {
        Load( フォント名 , 大きさ , 太さ , 改行高さ , フォントタイプ);
    }

    /** メモリ上にフォントを作成する.*/
    /**    太さは0～9で指定、大きさと太さは-1にするとデフォルトになる\n
        改行高さは0の場合、改行後の文字が上下くっつく。
        SDLとDXLIBではフォント名の指定方法が違うので注意。
        SDLでは太さとフォントタイプが無効*/
    bool Load(const char *フォント名,int 大きさ ,int 太さ = 1 , int 改行高さ = 0, FontType フォントタイプ = FontType::Normal)
    {
        Release();
        this->size = 大きさ;
        this->enterHeight = 改行高さ + 大きさ;
        this->thick = 太さ;
        handle = TTF_OpenFont(フォント名,大きさ);
        return true;
    }
            
    /** フォントをメモリから開放する.*/
    bool Release() const
    {
        if(handle != NULL_HANDLE) return false;
        TTF_CloseFont(handle);
        for(auto && it: hash)
        {
            it.second->Release();
        }
        return true;
    }

    /** フォントのハンドルを取得.*/
    FontHandle GetHandle() const
    {
        return handle;
    }
    
    Image MakeImage(Color 文字色, bool 反転フラグ, VariadicStream 描画する文字列) const
    {
        std::vector<SDL_Surface*> surfaces;
        SDL_Surface* surface;

        for (auto it : 描画する文字列.StringS)
        {
            surface = TTF_RenderUTF8_Blended(handle, it.c_str(), 文字色);
            幅 = std::max(幅, surface->w);
            surfaces.push_back( surface );
        }

        SDL_Surface* toRend = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0, 0, 0, 0);
        SDL_Renderer* render = SDL_CreateSoftwareRenderer( toRend );
        
        for (auto it : surfaces)
        {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(render, it);

            SDL_Rect temp = { 0, Y座標, it->w, it->h };
            SDL_RenderCopy( render , texture , 0, &temp);

            Y座標 += this->enterHeight;

            SDL_FreeSurface(it);
            SDL_DestroyTexture( texture );
        }
        //描画先を戻す
        image.handle = SDL_CreateTextureFromSurface( Screen::GetHandle() , toRend);
        image.part.w = 幅;
        image.part.h = 高さ;

        SDL_FreeSurface(toRend);
        SDL_DestroyRenderer(render);

        return image;
    }

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
            
    /** 太さを取得.*/
    int Getthick() const
    {
        return this->thick;
    }
            
    /** 描画時の幅を取得.*/
    int GetDrawStringWidth( VariadicStream 幅を計算する文字列 ) const
    {
        for (auto it : 幅を計算する文字列.StringS)
        {
            幅 = std::max( 幅 , DxLib::GetDrawStringWidthToHandle(it.c_str(), strlen(it.c_str()), this->handle) );
        }
        return 幅;
    }

    void DrawUTFString(const Point &座標 , const std::string &文字列) const
    {
        unsigned char lead;
        int charSize = 0;
        for (auto it = 文字列.begin(); it != 文字列.end(); it += charSize)
        {
            lead = *it;
            if(lead < 0x80)         charSize = 1;
            else if (lead < 0xE0)   charSize = 2;
            else if (lead < 0xF0)   charSize = 3;
            else                    charSize = 4;

            Image* str = GetHash( 文字列.substr(std::distance(文字列.begin() , it) , charSize).c_str() );
            str->Draw(X座標, Y座標);
            X座標 += str->GetWidth();
        }
    }

    /** 文字を描画.*/
    bool Draw(const Point &座標, Color 色, VariadicStream 描画する文字列) const override
    {
        if( !handle ) return false;
        for (auto it : 描画する文字列.StringS)
        {
            DrawUTFString(X座標, Y座標, it);
            Y座標 += this->enterHeight;
        }

        return true;
    }
    
    /** 文字を回転して描画.*/
    /** 呼び出す度に画像イメージを作成するので処理は重い*/
    bool DrawRotate(const Point &座標, double 拡大率, double 角度, Color 描画色 , bool 反転フラグ, VariadicStream 描画する文字列) const override
    {
        return false;
    }

    /** 拡大率を指定して文字を描画.*/
    bool DrawExtend(const Point &座標, double X拡大率, double Y拡大率, Color 描画色, VariadicStream 描画する文字列) const override
    {
        SDL_Surface* image;
        SDL_Texture* moji;
        SDL_Rect temp;
        for (auto it:描画する文字列.StringS)
        {
            image = TTF_RenderUTF8_Blended(handle, it.c_str() , 描画色);
            
            moji = SDL_CreateTextureFromSurface(Screen::GetHandle(), image);
            temp = { X座標, Y座標, int(image->w * X拡大率), int(image->h * Y拡大率) };

            SDL_RenderCopy(Screen::GetHandle(), moji, 0, &temp);

            Y座標 += int(this->enterHeight * Y拡大率);
            SDL_FreeSurface(image);
            SDL_DestroyTexture(moji);
        }
    }        
};
}