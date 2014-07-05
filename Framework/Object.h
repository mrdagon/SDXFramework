#pragma once//☀SDXFramework
#include <SDXFrameWork.h>
#include <Framework/IObject.h>

namespace SDX
{

/** ModelにSTG用の機能を追加したクラス.*/
/**    \include */
template <class TShape = Point , class TSprite = SpImage>
class Object : public Model<TShape,TSprite> , public IObject
{
protected:
    int  timer = 0;//!< 発生してから経過したフレーム数
    bool isRemove = false;//!< 消滅フラグ
    bool isOutCheck = true;//!< 範囲外処理を行うかフラグ
    double  power;//!< 攻撃力
    int  attribute;//!< 攻撃属性
    int  lifeTime = -1;//!< 生存期間
    Belong belong;//!< 所属するレイヤー

    /** 消滅判定を行う.*/
    bool RemoveCheck(Rect* 存在可能な範囲) override
    {
        if(
            timer == this->lifeTime ||
            (isOutCheck && !shape.Hit( 存在可能な範囲 ) )
            )
        {
            this->isRemove = true;
        }

        if (isRemove) Remove();

        return this->isRemove;
    }

public:
    /** 説明.*/
    Object( const TShape &当たり判定 , const TSprite &描画方法 , double 攻撃力 = 0 , Belong 所属 = Belong::Etc):
        Model<>(当たり判定, 描画方法),
        power(攻撃力),
        belong(所属)
    {}

    virtual ~Object(){}

    /** 状態の更新.*/
    void Update() override
    {
        this->timer++;
        AnimeUpdate();
        this->Act();
    }

    /** 発生後経過時間を返す.*/
    int& GetTimer() override
    {
        return timer;
    }

    /** 消滅フラグの取得.*/
    bool& GetRemoveFlag() override
    {
        return isRemove;
    }

    /** 所属を取得.*/
    Belong& GetBelong() override
    {
        return belong;
    }
    
    /**Update時の追加処理.*/
    void Act() override{};

    /**消滅時の追加処理.*/
    void Remove() override{};

    /** ダメージを受けた時の処理.*/
    void React() override{};

    /**ダメージ処理.*/
    void Damaged(double ダメージ量 , IObject *衝突相手 ) override{};
};
}