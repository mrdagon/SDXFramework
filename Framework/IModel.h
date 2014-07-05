#pragma once//☀SDXFramework
#include "Framework/Shape.h"
#include "Framework/Sprite.h"

namespace SDX
{
    class IModel
    {
    public:
    /** 更新処理を行う.*/
    virtual void Update() = 0;

    /** 影の大きさを設定.*/
    virtual void SetShadowSize(double 影の表示倍率) = 0;

    /** 描画にカメラを使うか設定.*/
    virtual void SetIsCamera(bool カメラ利用フラグ) = 0;

    /** 描画する.*/
    virtual void Draw() const = 0;

    /** 影を描画する.*/
    virtual void DrawShadow( double X座標ずれ , double Y座標ずれ ) const = 0;

    /** アニメーションを更新する.*/
    virtual void AnimeUpdate() = 0;

    /** 相対座標で移動.*/
    virtual void Move(double X移動量 , double Y移動量) = 0;

    /** 前方に移動.*/
    virtual void MoveFront(double 速度) = 0;

    /** 極座標で移動.*/
    virtual void MovePolar(double 距離 , double 角度) = 0;

    /** 指定座標に移動.*/
    virtual void SetPos(double X座標 , double Y座標) = 0;

    /** 拡大率を設定する.*/
    virtual void SetZoom(double 拡大率 ) = 0;

    /** 縦横別で拡大率を設定する.*/
    virtual void SetZoom(double X拡大率, double Y拡大率) = 0;

    /** 拡大率を掛ける.*/
    virtual void MultiZoom(double 倍率) = 0;

    /** 縦横別で拡大率を掛ける.*/
    virtual void MultiZoom(double X倍率 , double Y倍率) = 0;

    /** 回転させる.*/
    virtual void Rotate( double 回転角度 ) = 0;

    /** 角度を取得する.*/
    virtual double GetAngle() const = 0;

    /** 角度を設定する.*/
    virtual void SetAngle( double 角度 ) = 0;

    /** 色をまとめて変更する、透明度も含む.*/
    virtual void SetColor( Color 描画色) = 0;

    /** 横方向の拡大率を取得.*/
    virtual double GetZoomX() const = 0;

    /** 縦方向の拡大率を取得.*/
    virtual double GetZoomY() const  = 0;

    /** X座標を取得.*/
    virtual double GetX() const = 0;

    /** Y座標を取得.*/
    virtual double GetY() const = 0;

    /** Modelとの衝突判定.*/
    virtual bool Hit( IModel *判定を行うModel) = 0;
    virtual bool Hit( Shape *判定を行うShape) = 0;

    /** 対象との角度を取得.*/
    virtual double GetDirect(IModel* 比較対象) = 0;
    virtual  double GetDirect(Shape* 比較対象) = 0;

    /** 対象との相対座標を取得.*/
    virtual double GetDistance(IModel* 比較対象) = 0;
    virtual double GetDistance(Shape* 比較対象) = 0;
    
    };
}
