#pragma once//☀SDXFramework
#include <SDXFrameWork.h>
#include <Framework/ModelMove.h>
#include <Utility/Module.h>

namespace SDX
{
/** 所属するレイヤーの識別子.*/
enum class Belong
{
    Ally,//!< 味方
    EnemyF,//!< 空中の敵
    EnemyG,//!< 地上の敵
    Item,//!< アイテム
    Block,//!< 障害物
    Etc,//!< その他
};

/** ModelにSTG用の機能を追加したクラス.*/
/**    \include */
class IObject : public IModel
{
friend class Layer;

protected:
    int  timer = 0;//!< 発生してから経過したフレーム数
    bool isRemove = false;//!< 消滅フラグ
    bool isOutCheck = true;//!< 範囲外処理を行うかフラグ
    double  power;//!< 攻撃力
    int  attribute;//!< 攻撃属性
    int  lifeTime = -1;//!< 生存期間
    Belong belong;//!< 所属するレイヤー

    /** 消滅判定を行う.*/
    virtual bool RemoveCheck(Rect* 存在可能範囲)
    {
        if(
            timer == this->lifeTime ||
            (isOutCheck && !shape->Hit( 存在可能範囲 ) )
            )
        {
            this->isRemove = true;
        }

        if (isRemove) Remove();

        return this->isRemove;
    }

    /** 衝突した相手に攻撃する.*/
    virtual void Attack(Object *攻撃対象 )
    {
        攻撃対象->Damaged( power );
    }

    void SetTimer(int フレーム数)
    {
        timer = フレーム数;
    }

public:
    /** 説明.*/
    IObject( IShape &図形 , ISprite &描画方法 , double 攻撃力 = 0 , Belong 所属 = Belong::Etc):
        IModel(図形, 描画方法),
        ModelMove(this),
        power(攻撃力),
        belong(所属)
    {}

    /** 発生後経過時間を返す.*/
    int GetTimer()
    {
        return timer;
    }

    virtual ~Object(){}

    /** 状態の更新.*/
    virtual void Update()
    {
        this->timer++;
        AnimeUpdate();
        this->Act();
    }

    /** 消滅フラグの取得.*/
    bool GetRemoveFlag()
    {
        return isRemove;
    }

    void SetRemoveFlag(bool 消滅フラグ)
    {
        isRemove = 消滅フラグ;
    }

    /** 所属を取得.*/
    Belong GetBelong()
    {
        return belong;
    }

    /** Update時の行動処理.*/
    virtual void Act(){}

    /** 消滅時の処理.*/
    virtual void Remove(){}

    /** ダメージを受けた時の処理.*/
    virtual void React(){}

    /** 攻撃された時の処理.*/
    virtual void Damaged(double 被ダメージ){}

};

template <class TShape,class TSprite>
class Object : public IObject
{
    public:
        TShape shape;
        TSprite sprite;

        Object(const TShape &図形と位置, const TSprite &描画方法):
            shape(図形と位置),
            sprite(描画方法)
        {}

};

}