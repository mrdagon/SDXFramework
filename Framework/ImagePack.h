#pragma once//☀SDXFramework
#include<Multimedia/SDX.h>
#include<Multimedia/Image.h>

namespace SDX
{
/** 複数のImageをまとめるクラス.*/
/**    \include ImageSample.h*/
class ImagePack
{
protected:
    std::vector<Image*> images;
    int widthMax;
    int heightMax;
public:
    ImagePack():
        widthMax( 0 ),
        heightMax( 0 )
    {}

    /** １つの画像を分割して読み込む.*/
    ImagePack( const char *ファイル名 , int 総コマ数 , int コマ割り横,int コマ割り縦)
    {
        ImagePack::Load(ファイル名,総コマ数 , コマ割り横, コマ割り縦 );
    }

    /** １つの画像を分割して読み込む.*/
    /** 総コマ数=14,コマ割り横=4,コマ割り縦=4の場合\n
        [ 0][ 1][ 2][ 3]\n
        [ 4][ 5][ 6][ 7]\n
        [ 8][ 9][10][11]\n
        [12][13][  ][  ]\n
        のように分割して、ImagePackのサイズは14になる */
    bool Load(const char *ファイル名 , int 総コマ数,int コマ割り横, int コマ割り縦 )
    {
        int x = 0, y = 0, count = 0;
        Image image(ファイル名);

        const int width = image.GetWidth() / コマ割り横;
        const int height = image.GetHeight() / コマ割り縦;

        for (int i = 0; i < コマ割り縦; ++i)
        {
            x = 0;
            for (int j = 0; j < コマ割り横; j++)
            {
                if (count >= 総コマ数) break;
                this->Add(new Image(image, x, y, width, height));
                x += width;
                count++;
            }
            y += height;
        }

        return true;
    }

    /** 連番ファイルを一括して読み込む.*/
    /**    ファイル名の後に三桁の連番が付いたファイルを連続して読み込む\n
        例:「ファイル名***.拡張子」*/
    bool Load(const char *ファイル名 , const char *拡張子 , int 総コマ数 , const char* 書式 = "%03d.")
    {
        for(int i=0 ; i<総コマ数 ; ++i)
        { 
            char fileBuf[8];
            sprintf_s( fileBuf , 8 , 書式 , i );

            std::string fileName = ファイル名;
            fileName += fileBuf;
            fileName += 拡張子;

            this->Add( new Image( fileName.c_str() ) );
        }
        return true;
    }
            
    /** Imageを末尾に追加.*/
    void Add(Image *追加イメージ)
    {
        images.push_back( 追加イメージ );
        this->widthMax  = std::max( this->widthMax  , 追加イメージ->GetWidth() );
        this->heightMax = std::max( this->heightMax, 追加イメージ->GetHeight());
    }
    void Add(const char *ファイル名)
    {
        Add( new Image( ファイル名 ) );
    }
            
    /** Imageをメモリから開放.*/
    virtual void Release()
    {
        for( auto it : images)
        {
            it->Release();
        }

        images.clear();
    }
            
    /** 要素数を取得.*/
    int GetSize() const
    {
        return (int)images.size();
    }
                
    /** 最大幅を取得.*/
    int GetWidth() const
    {
        return this->widthMax;
    }
            
    /** 最大高さを取得.*/
    int GetHeight() const
    {
        return this->heightMax;
    }
    
    Image* operator[](int index)
    {
        return images[index];
    }
    
    Image* operator[](int index) const
    {
        return images[index];
    }

};
}