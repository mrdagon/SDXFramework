#pragma once//☀SDXFramework
#include <Multimedia/Image.h>
#include <Multimedia/Font.h>
#include <Framework/BmpFont.h>
#include <Framework/Anime.h>

namespace SDX
{

/** 描画用枠のインターフェース.*/
/**    \include BmpFrameSample.h*/
class IFrame
{
public:
    virtual void Draw(int X座標, int Y座標, int 幅, int 高さ) const = 0;
};

/** 描画用枠を表すクラス.*/
/**    \include BmpFrameSample.h*/
class BmpFrame : public IFrame
{
private:
    bool isMake;
    ImagePack *frame;
public:
    /** フレームを作成する.*/
    /** ３×３分割したImagePackを元にフレームを作成*/
    bool Make( ImagePack *フレーム画像 )
    {
        if( フレーム画像->GetSize() != 9  ) return false;

        this->frame = フレーム画像;
        this->isMake = true;

        return true;
    }
    
    /** 矩形のフレームを描画.*/
    /** 右上座標を指定してフレームを描画する*/
    void Draw( int X座標, int Y座標, int 幅, int 高さ) const
    {
        const int fWidth = frame->GetWidth();
        const int fHeight = frame->GetHeight();

        const int xA = X座標 + fWidth;
        const int xB = X座標 - fWidth + 幅;
        const int yA = Y座標 + fHeight;
        const int yB = Y座標 - fHeight + 高さ;

        //内部スキンを描画
        frame[0][4]->DrawExtend(X座標 + fWidth, Y座標 + fHeight, X座標 + 幅 - fWidth, Y座標 + 高さ - fHeight);
        
        //まず外枠を描画    
        frame[0][3]->DrawExtend(X座標, yA, xA, yB);
        frame[0][5]->DrawExtend(xB, yA, xB + fWidth, yB);

        frame[0][1]->DrawExtend(xA, Y座標, xB, yA);
        frame[0][7]->DrawExtend(xA, yB, xB, yB + fHeight);
        
        //四隅を描画
        frame[0][0]->Draw(X座標, Y座標);
        frame[0][2]->Draw(X座標 + 幅 - fWidth, Y座標);
        frame[0][6]->Draw(X座標, Y座標 + 高さ - fHeight);
        frame[0][8]->Draw(X座標 + 幅 - fWidth, Y座標 + 高さ - fHeight);
    }
};
}