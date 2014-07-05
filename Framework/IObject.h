#pragma once//☀SDXFramework

namespace SDX_STG
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

    /**Objectのインターフェース.*/
    class IObject
    {
    protected:
    /**消滅判定を行う.*/
        virtual bool RemoveCheck(Rect* 存在可能な範囲 ) = 0;
    public:
        /**毎フレームの更新処理.*/
        virtual void Update() = 0;

        /**経過フレームを取得.*/
        virtual int& GetTimer() = 0;

        /**死亡フラグの取得.*/
        virtual bool& GetRemoveFlag() = 0;

        /**所属レイヤーを取得.*/
        virtual Belong& GetBelong() = 0;

        /**Update時の追加処理.*/
        virtual void Act() = 0;

        /**消滅時の追加処理.*/
        virtual void Remove() = 0;

        /** ダメージを受けた時の処理.*/
        virtual void React() = 0;

        /**ダメージ処理.*/
        virtual void Damaged(double ダメージ量 , IObject *衝突相手 ) = 0;
    };

}