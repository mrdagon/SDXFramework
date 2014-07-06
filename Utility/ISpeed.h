#pragma once//☀SDXFramework

namespace SDX
{
namespace Speed
{
/** 変化する数値を表す抽象クラス.*/
///    \include SpeedSample.h
class ISpeed
{
protected:
    double speed;
public:
    ISpeed(double 速度):
        speed(速度)
    {}
    virtual ~ISpeed(){};

    /** 現在の速度を取得.*/
    virtual double Get() const
    {
        return speed; 
    }

    /** 更新後、速度を取得.*/
    double Ease()
    {
        Update();
        return Get();
    }

    /** 速度を更新.*/
    virtual void Update() = 0;
};
}
}