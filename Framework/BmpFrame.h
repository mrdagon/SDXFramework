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
    virtual void Draw(const Rect &領域) const = 0;
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
    void Draw(const Rect &領域) const
    {
        const int fWidth = frame->GetWidth();
        const int fHeight = frame->GetHeight();

        const double X座標 = 領域.GetLeft();
        const double Y座標 = 領域.GetTop();
        const double xA = X座標 + fWidth;
        const double xB = X座標 - fWidth + 領域.GetW();
        const double yA = Y座標 + fHeight;
        const double yB = Y座標 - fHeight + 領域.GetH();

        //内部スキンを描画
        frame[0][4]->DrawExtend({ fWidth +X座標, fHeight + Y座標}, { 領域.GetW() - fWidth + X座標, 領域.GetH() - fHeight + Y座標});

        //まず外枠を描画    
        frame[0][3]->DrawExtend({ X座標, yA }, { xA, yB });
        frame[0][5]->DrawExtend({ xB, yA }, { xB + fWidth, yB });

        frame[0][1]->DrawExtend({ xA, Y座標 }, { xB, yA });
        frame[0][7]->DrawExtend({ xA, yB }, { xB, yB + fHeight });

        //四隅を描画
        frame[0][0]->Draw({ X座標, Y座標 });
        frame[0][2]->Draw({ X座標 + 領域.GetW() - fWidth, Y座標 });
        frame[0][6]->Draw({ X座標, Y座標 + 領域.GetH() - fHeight });
        frame[0][8]->Draw({ X座標 + 領域.GetW() - fWidth, Y座標 + 領域.GetH() - fHeight });
    }
};
}