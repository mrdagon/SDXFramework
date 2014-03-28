#pragma once

namespace SDX
{
/** 変化する数値を表す抽象クラス.*/
/**    \include SpeedSample.h */
class ISpeed
{
protected:
    double speed;//基本速度
public:
    ISpeed(double 速度):
            speed(速度)
    {}

    /** 現在の速度を取得.*/
    virtual double Get() const
    {
        return speed; 
    };

    /** 更新後、速度を取得.*/
    double Ease()
    {
        Update();
        return Get();
    }

    /** 速度を更新.*/
    virtual void Update() = 0;

    /** 速度を掛ける.*/
    virtual void Multi(double 倍率)
    {
        speed *= 倍率;
    }

    /** 速度を加算する.*/
    virtual void Add(double 加算値)
    {
        speed += 加算値;
    }
};
}