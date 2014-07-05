#pragma once//☀SDXFramework
#include<Framework/IModel.h>
//#include<Framework/Sprite.h>
//#include<Framework/Shape.h>
#include<Framework/Camera.h>
#include<Framework/SpriteDerived.h>
#include<memory>

namespace SDX
{
/** ShapeとSpriteをまとめて、2Dモデルを表すクラス.*/
/** \include ModelSample.h*/
template <class TShape = Point , class TSprite = SpImage>
class Model : public IModel
{
private:
    double zoomX = 1;
    double zoomY = 1;
    double angle = 0;
    double shadowSize = 1;
    bool isCamera = true;
public:
    //TSprite sprite;
    //TShape  shape;    
    SpImage sprite;
    Point shape;

    Model( const TShape &位置と形 , const TSprite &描画ポリシー ):
        shape(位置と形),
        sprite(描画ポリシー)
    {}

    virtual ~Model()
    {}

    /** 更新処理を行う.*/
    void Update() override
    {}

    /** 影の大きさを設定.*/
    void SetShadowSize(double 影の表示倍率) override
    {
        shadowSize = 影の表示倍率;
    }

    /** 描画にカメラを使うか設定.*/
    void SetIsCamera(bool カメラ利用フラグ) override
    {
        isCamera = カメラ利用フラグ;
    }

    /** 描画する.*/
    void Draw() const override
    {
        if( !sprite.isVisible ) return;
        if( !sprite.isAllway && sprite.isActive ) return;

        if( sprite.GetColor() == Color::White )
        {
            sprite.Draw({ GetX(), GetY() }, isCamera && Camera::Now());
        }
        else
        {
            Screen::SetBright(sprite.GetColor());
            Screen::SetBlendMode( BlendMode::Alpha , sprite.GetColor().GetAlpha() );
            sprite.Draw({ GetX(), GetY() }, isCamera && Camera::Now());
            Screen::SetBlendMode(BlendMode::NoBlend, 0);
            Screen::SetBright(Color::White);
        }

        //当たり判定を表示するならコメントアウト解除
        //shape.get()->Draw(Color::Red,128,Camera::Now() );
    }

    /** 影を描画する.*/
    void DrawShadow( double X座標ずれ , double Y座標ずれ ) const override
    {
        if( shadowSize <= 0 ) return;

        X座標ずれ *= shadowSize;
        Y座標ずれ *= shadowSize;

        if( !sprite.isVisible ) return;
        if( !sprite.isAllway && sprite.isActive ) return;

        if( sprite.GetColor().GetAlpha() <= 255 )
        {
            double zoomX = sprite.zoomX;
            double zoomY = sprite.zoomY;
            //const_cast<double>(sprite.zoomX) *= shadowSize;
            //const_cast<double>(sprite.zoomY) *= shadowSize;
            sprite.Draw({ GetX() + X座標ずれ, GetY() + Y座標ずれ }, isCamera && Camera::Now());
            //const_cast<double>(sprite.zoomX) = zoomX;
            //const_cast<double>(sprite.zoomY) = zoomY;
        }

    }

    /** アニメーションを更新する.*/
    void AnimeUpdate() override
    {
        sprite.AnimeUpdate();
    }

    /** 相対座標で移動.*/
    void Move(double X移動量 , double Y移動量) override
    {
        shape.Move(X移動量, Y移動量);
    }

    /** 前方に移動.*/
    void MoveFront(double 距離) override
    {
        shape.MoveA(距離, GetAngle() );
    }

    /** 極座標で移動.*/
    void MovePolar(double 距離 , double 角度) override
    {
        shape.MoveA( 距離 , 角度);
    }

    /** 指定座標に移動.*/
    void SetPos(double X座標 , double Y座標) override
    {                
        shape.SetPos(X座標, Y座標);
    }

    /** 拡大率を設定する.*/
    void SetZoom(double 拡大率 ) override
    {
        MultiZoom(拡大率 / zoomX, 拡大率 / zoomY);
    }

    /** 縦横別で拡大率を設定する.*/
    void SetZoom(double X拡大率, double Y拡大率) override
    {
        MultiZoom(X拡大率 / zoomX, Y拡大率 / zoomY);
    }

    /** 拡大率を掛ける.*/
    void MultiZoom(double 倍率) override
    {
        MultiZoom(倍率,倍率);
    }

    /** 縦横別で拡大率を掛ける.*/
    void MultiZoom(double X倍率 , double Y倍率) override
    {
        shape.MultiZoom(X倍率 , Y倍率);
        sprite.MultiZoom(X倍率, Y倍率);

        zoomX *= X倍率;
        zoomY *= Y倍率;
    }

    /** 回転させる.*/
    void Rotate( double 回転角度 ) override
    {
        angle += 回転角度;
        shape.Rotate(回転角度);
        sprite.Rotate(回転角度);
    }

    /** 角度を取得する.*/
    double GetAngle() const override
    {
        return angle;
    }

    /** 角度を設定する.*/
    void SetAngle( double 角度 ) override
    {
        shape.SetAngle(角度);
        sprite.SetAngle(角度);
        angle = 角度;
    }

    /** 色をまとめて変更する、透明度も含む.*/
    void SetColor( Color 描画色) override
    {
        sprite.SetColor(描画色);
    }

    /** 横方向の拡大率を取得.*/
    double GetZoomX() const override
    {
        return zoomX;
    }

    /** 縦方向の拡大率を取得.*/
    double GetZoomY() const override
    {
        return zoomY;
    }

    /** X座標を取得.*/
    double GetX() const override
    {
        return shape.GetX();
    }

    /** Y座標を取得.*/
    double GetY() const override
    {
        return shape.GetY();
    }

    /** Modelとの衝突判定.*/
    bool Hit( IModel *判定を行うModel) override
    {
        return 判定を行うModel->Hit(&shape);
    }

    /** Shapeとの衝突判定.*/
    bool Hit( Shape *判定を行うShape) override
    {
        return shape.Hit(判定を行うShape);
    }

    /** 対象との角度を取得.*/
    double GetDirect(IModel* 比較対象) override
    {
        return atan2( 比較対象->GetY() - GetY(), 比較対象->GetX() - GetX());
    }
    double GetDirect(Shape* 比較対象) override
    {
        return atan2( 比較対象->GetY() - GetY(), 比較対象->GetX() - GetX());
    }

    /** 対象との相対座標を取得.*/
    double GetDistance(IModel* 比較対象) override
    {
        const double xd = this->GetX() - 比較対象->GetX();
        const double yd = this->GetY() - 比較対象->GetY();

        return sqrt( xd * xd + yd * yd );
    }
    double GetDistance(Shape* 比較対象) override
    {
        const double xd = this->GetX() - 比較対象->GetX();
        const double yd = this->GetY() - 比較対象->GetY();

        return sqrt( xd * xd + yd * yd );
    }


};
}