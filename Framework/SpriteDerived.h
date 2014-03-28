#pragma once//☀SDXFramework
#include <Framework/Sprite.h>

namespace SDX
{
/** Imageスプライト.*/
/**    \include ModelSample.h*/
class SpImage : public Sprite
{
private:
    const Image *image;

public:
    SpImage(const Image *描画Image ):
        image(描画Image)
    {}

    void Draw(double X座標, double Y座標, bool Cameraフラグ) override
    {
        if ( Cameraフラグ )
        {
            image->DrawRotateAxis(        (int)Camera::Now()->TransX(X座標 + gapX) ,
                                        (int)Camera::Now()->TransY(Y座標 + gapY) ,
                                        (int)(axisX + image->GetWidth() / 2), 
                                        (int)(axisY + image->GetHeight() / 2), 
                                        zoomX * Camera::Now()->GetZoom() ,
                                        zoomY * Camera::Now()->GetZoom() ,
                                        angle , isTurn);
        }else{
            image->DrawRotateAxis(        (int)(X座標 + gapX) ,
                                        (int)(Y座標 + gapY),
                                        (int)(axisX + image->GetHeight() / 2), 
                                        (int)(axisY + image->GetHeight() / 2), 
                                        zoomX ,
                                        zoomY ,
                                        angle , isTurn);
        }
    }
};

/** ImagePackスプライト.*/
/**    \include ModelSample.h*/
class SpImageS : public Sprite
{
private:
    const ImagePack *imageS;
    int index = 0;
public:
    SpImageS(const ImagePack *描画ImagePack ):
        imageS(描画ImagePack)
    {}

    void SetIndex(int コマ番号)
    {
        index = コマ番号;
    }

    int GetIndex()
    {
        return index;
    }

    void Draw(double X座標, double Y座標, bool Cameraフラグ) override
    {
        const auto image = imageS->operator[](index);

        if ( Cameraフラグ )
        {
            image->DrawRotateAxis((int)Camera::Now()->TransX(X座標 + gapX) ,
                                        (int)Camera::Now()->TransY(Y座標 + gapY) ,
                                        (int)(axisX + image->GetWidth() / 2), 
                                        (int)(axisY + image->GetHeight() / 2), 
                                        zoomX * Camera::Now()->GetZoom() ,
                                        zoomY * Camera::Now()->GetZoom() ,
                                        angle , isTurn);
        }else{
            image->DrawRotateAxis(        (int)(X座標 + gapX) ,
                                        (int)(Y座標 + gapY),
                                        (int)(axisX + image->GetHeight() / 2), 
                                        (int)(axisY + image->GetHeight() / 2), 
                                        zoomX ,
                                        zoomY ,
                                        angle , isTurn);
        }
    }        
};


/** Animeスプライト.*/
/**    \include */
class SpAnime : public Sprite
{
private:
    const Anime *anime;
    Anime::Player counter;
    double aniSpeed;

public:

    SpAnime(const Anime *描画Anime , double 再生速度 = 1) :
            anime( 描画Anime ),
            counter( 描画Anime ),
            aniSpeed( 再生速度 )
    {}

    void AnimeUpdate() override
    {
        counter.Update( aniSpeed );
    }

    void Draw(double X座標, double Y座標, bool Cameraフラグ) override
    {
        if( Cameraフラグ )
        {
            counter.GetFrame()->DrawRotateAxis( 
                                        (int)Camera::Now()->TransX(X座標 + gapX) , 
                                        (int)Camera::Now()->TransY(Y座標 + gapY) ,
                                        (int)(axisX + anime->GetWidth() / 2 ), 
                                        (int)(axisY + anime->GetHeight() / 2 ),
                                        zoomX * Camera::Now()->GetZoom() ,
                                        zoomY * Camera::Now()->GetZoom(),
                                        angle ,
                                        isTurn);
        }
        else
        {
            counter.GetFrame()->DrawRotateAxis(
                                        (int)(X座標 +gapX),
                                        (int)(Y座標 +gapY),
                                        (int)axisX + anime->GetWidth() / 2,
                                        (int)axisY + anime->GetHeight() / 2,
                                        zoomX ,
                                        zoomY ,
                                        angle , isTurn);
        }
    }
};

/** Fontスプライト.*/
/**    \include */
class SpFont : public Sprite
{
private:
    const IFont *font;
    std::string& refStr;
    std::string  str;
    bool isReference;
    Color rgb;

public:
    SpFont(const IFont *フォント ,  Color 描画色 , double 縦倍率 , double 横倍率,const char* 描画する文字列 ):
        font(フォント),
        rgb(描画色),
        str( 描画する文字列 ),
        refStr( str ),
        isReference(false)
    {
        this->SetZoom(縦倍率,横倍率);
    }

    SpFont(const IFont *フォント ,  Color 描画色 , double 縦倍率 , double 横倍率, std::string& 参照する文字列 ):
        font(フォント),
        rgb(描画色),
        refStr( 参照する文字列 ),
        isReference(true)
    {
        this->SetZoom(縦倍率,横倍率);
    }

    void Draw(double X座標, double Y座標, bool Cameraフラグ) override
    {
        if( Cameraフラグ )
        {
            font->DrawExtend
                (
                    (int)Camera::Now()->TransX(X座標 + gapX) ,
                    (int)Camera::Now()->TransY(Y座標 + gapY) ,
                    zoomX * Camera::Now()->GetZoom() ,
                    zoomY * Camera::Now()->GetZoom() ,
                    rgb ,
                    refStr.c_str() 
                );
        }
        else
        {
            font->DrawExtend
                (
                    (int)(X座標+gapX),
                    (int)(Y座標+gapY),
                    zoomX,
                    zoomY,
                    rgb,
                    refStr.c_str()
                );
        }
    }

    void SetText( const char* 表示する文字 )
    {
        refStr = 表示する文字;
    }
};

/** IFrameスプライト.*/
/**    \include */
class SpFrame : public Sprite
{
private:
    const IFrame *bmpFrame;
    double width;
    double height;

public:
    SpFrame(const IFrame *描画する枠 , double 幅 , double 高さ ):
        bmpFrame( 描画する枠),
        width( 幅 ),
        height( 高さ )
    {}

    void Draw(double X座標, double Y座標, bool Cameraフラグ) override
    {
        if( Cameraフラグ )
        {
            bmpFrame->Draw(    (int)Camera::Now()->TransX(X座標 + gapX) ,
                            (int)Camera::Now()->TransY(Y座標 + gapY) ,
                            (int)(width * zoomX * Camera::Now()->GetZoom()) ,
                            (int)(height * zoomY * Camera::Now()->GetZoom()));
        }
        else
        {
            bmpFrame->Draw(    (int)(X座標 + gapX),
                            (int)(Y座標 + gapY),
                            (int)(width * zoomX) ,
                            (int)(height * zoomY) );
        }
    }
};

/** マップチップスプライト.*/
/**    \include */
class SpMap : public Sprite
{
private:
    ImagePack &chip;
    int width;
    int height;
    int rotate;
    std::vector< std::vector<int> > data;
public:

    SpMap( ImagePack& マップチップ , const char* ファイル名 , int 幅 , int 高さ , int 角度):
        width(幅),
        height(高さ),
        rotate(角度),
        chip(マップチップ)
    {
        File csvFile( ファイル名 , FileMode::Read );

        data.resize( 幅 );

        for(int i=0 ; i<幅 ;++i)
        {
            data[i].resize( 高さ );
        }

        auto lineS = csvFile.GetCsvS();

        for(int i = 0 ; i < 高さ ; ++i )
        {
            for( int j = 0 ; j < 幅 ; j++)
            {
                data[j][i] = atoi( lineS[i][j].c_str() );
            }
        }
    }

    void Draw(double X座標, double Y座標, bool カメラ有りフラグ) override
    {
        const int chipW = chip.GetWidth();
        const int chipH = chip.GetHeight();

        if( カメラ有りフラグ )
        {
            const int baseY = int(Camera::Now()->TransY( Y座標 ));
            const int baseX = int(Camera::Now()->TransX( X座標 ));
            
            int posXA;
            int posYA;
            int posXB;
            int posYB;

            for(int i=0 ; i<width ; ++i )
            {
                posXA = int( baseX + chipW * i * Camera::Now()->GetZoom() );
                posXB = int( baseX + chipW * (i+1) * Camera::Now()->GetZoom() );

                for(int j=0 ; j<height ; ++j )
                {
                    posYA = int( baseY + chipH * j * Camera::Now()->GetZoom() );
                    posYB = int( baseY + chipH * (j+1) * Camera::Now()->GetZoom() );
                    const int no = data[i][j];
                    if( no == 0 ) continue;
                    chip[no]->DrawExtend( posXA , posYA , posXB , posYB );
                }
            }
        }else{
            for(int i=0 ; i<width ; ++i )
            {
                for(int j=0 ; j<height ; ++j )
                {
                    const int no = data[i][j];
                    if( no == 0 ) continue;
                    chip[no]->Draw( int(X座標 + i*chipW) , int(Y座標 + j*chipH) );
                }
            }
        }
    }

};

}