//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once
#include<Framework/Sprite.h>
#include<Framework/Shape.h>
#include<Framework/Camera.h>
#include<memory>

namespace SDX
{

/** ShapeとSpriteをまとめて、2Dモデルを表すクラス.*/
/** \include ModelSample.h*/
class IModel
{
private:
    double zoomX = 1;
    double zoomY = 1;
    double angle = 0;
    double shadowSize = 1;
    bool isCamera = true;
protected:
    bool isRemove = false;
public:
    IShape &iShape;
    ISprite &iSprite;

    IModel(IShape &図形,ISprite &描画方法):
        iShape(図形),
        iSprite(描画方法)
    {};
    virtual ~IModel(){};
    

    /** 消滅フラグの取得.*/
    bool GetRemoveFlag()
    {
        return isRemove;
    }

    /** 更新処理を行う.*/
    virtual void Update(){}

    /** 影の大きさを設定.*/
    void SetShadowSize(double 影の表示倍率)
    {
        shadowSize = 影の表示倍率;
    }

    /** 描画にカメラを使うか設定.*/
    void SetIsCamera(bool カメラ利用フラグ)
    {
        isCamera = カメラ利用フラグ;
    }

    /** 描画する.*/
    virtual void Draw()
    {
        if( iSprite.GetColor() == Color::White )
        {
            iSprite.Draw({ GetX(), GetY()}, isCamera && Camera::Now());
        }
        else
        {
            Screen::SetBright(iSprite.GetColor());
            Screen::SetBlendMode( BlendMode::Alpha , iSprite.GetColor().GetAlpha() );
            iSprite.Draw({ GetX(), GetY() }, isCamera && Camera::Now());
            Screen::SetBlendMode(BlendMode::NoBlend, 0);
            Screen::SetBright(Color::White);
        }

        //当たり判定を表示するならコメントアウト解除
        //shape.get()->Draw(Color::Red,128,Camera::Now() );
    }

    /** 影を描画する.*/
    void DrawShadow( double X座標ずれ , double Y座標ずれ )
    {
        if( shadowSize <= 0 ) return;

        X座標ずれ *= shadowSize;
        Y座標ずれ *= shadowSize;

        double zoomX = iSprite.zoomX;
        double zoomY = iSprite.zoomY;
        iSprite.zoomX *= shadowSize;
        iSprite.zoomY *= shadowSize;
        iSprite.Draw({ GetX() + X座標ずれ, GetY() + Y座標ずれ }, isCamera && Camera::Now());
        iSprite.zoomX = zoomX;
        iSprite.zoomY = zoomY;
    }

    /** アニメーションを更新する.*/
    void AnimeUpdate()
    {
        iSprite.AnimeUpdate();
    }

    /** 相対座標で移動.*/
    void Move(double X移動量 , double Y移動量)
    {
        iShape.Move(X移動量, Y移動量);
    }

    /** 極座標で移動.*/
    void MovePolar(double 距離 , double 角度)
    {
        iShape.Move(距離 * cos(角度), 距離 * sin(角度));
    }

    /** 指定座標に移動.*/
    void SetPos(double X座標 , double Y座標)
    {                
        iShape.SetPos(X座標, Y座標);
    }

    /** 拡大率を設定する.*/
    void SetZoom(double 拡大率 )
    {
        MultiZoom(拡大率 / zoomX, 拡大率 / zoomY);
    }

    /** 縦横別で拡大率を設定する.*/
    void SetZoom(double X拡大率, double Y拡大率)
    {
        MultiZoom(X拡大率 / zoomX, Y拡大率 / zoomY);
    }

    /** 拡大率を掛ける.*/
    void MultiZoom(double 倍率)
    {
        MultiZoom(倍率,倍率);
    }

    /** 縦横別で拡大率を掛ける.*/
    void MultiZoom(double X倍率 , double Y倍率)
    {
        iShape.MultiZoom(X倍率 , Y倍率);
        zoomX *= X倍率;
        zoomY *= Y倍率;
        
        iSprite.MultiZoom(X倍率, Y倍率);
    }

    /** 回転させる.*/
    void Rotate( double 回転角度 )
    {
        this->angle += 回転角度;
        iSprite.Rotate(回転角度);
    }

    /** 角度を取得する.*/
    double GetAngle()
    {
        return angle;
    }

    /** 角度を設定する.*/
    void SetAngle( double 角度 )
    {
        iSprite.Rotate( 角度 - this->angle);
        this->angle = 角度;
    }

    /** 色をまとめて変更する、透明度も含む.*/
    void SetColor( Color 描画色)
    {
        iSprite.SetColor(描画色);
    }

    /** 横方向の拡大率を取得.*/
    double GetZoomX()
    {
        return zoomX;
    }

    /** 縦方向の拡大率を取得.*/
    double GetZoomY()
    {
        return zoomY;
    }

    /** X座標を取得.*/
    double GetX() const
    {
        return iShape.GetX();
    }

    /** Y座標を取得.*/
    double GetY() const
    {
        return iShape.GetY();
    }

    /** Modelとの衝突判定.*/
    bool Hit( IModel *判定を行うModel)
    {
        return iShape.Hit( &判定を行うModel->iShape);
    }

    /** Shapeとの衝突判定.*/
    bool Hit( IShape *判定を行うShape)
    {
        return iShape.Hit(判定を行うShape);
    }

    /** マウスカーソルとの衝突判定.*/
    bool Hit( Camera *座標変換に使うCamera = nullptr)
    {
        Point pt;

        if (座標変換に使うCamera)
        {
            pt.x = 座標変換に使うCamera->TransX(Input::mouse.x + 座標変換に使うCamera->GetCenterX());
            pt.y = 座標変換に使うCamera->TransY(Input::mouse.y + 座標変換に使うCamera->GetCenterY());
        }else{
            pt.x = Input::mouse.x;
            pt.y = Input::mouse.y;
        }

        return iShape.Hit(&pt);
    }

    /** 対象との角度を取得.*/
    template <class T>
    double GetDirect(T* 比較対象)
    {
        return atan2( 比較対象->GetY() - GetY(), 比較対象->GetX() - GetX());
    }

    /** 対象との相対座標を取得.*/
    template <class T>
    double GetDistance(T* 比較対象)
    {
        const double xd = this->GetX() - 比較対象->GetX();
        const double yd = this->GetY() - 比較対象->GetY();

        return sqrt( xd * xd + yd * yd );
    }
    
};

/**Modelの基本クラス.*/
template <class TShape,class TSprite>
class Model : public IModel
{
    public:
        TShape shape;
        TSprite sprite;

        Model(TShape &&図形と位置,TSprite &&描画方法):
            IModel(shape,sprite),
            shape(図形と位置),
            sprite(描画方法)
        {}
};

}