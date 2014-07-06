#pragma once//☀SDXFramework
#include <Utility/ISpeed.h>

namespace SDX
{
/** ISpeedを継承したクラスが属する.*/
namespace Speed
{
/** 常に同じ速度.*/
///    \include SpeedSample.h
class Liner : public ISpeed
{
public:
    Liner(double 速度) :
        ISpeed(速度)
    {}

    void Update() override
    {}
};

/** 加速する.*/
///    \include SpeedSample.h
class Accel : public ISpeed
{
private:
    double accel;//加速度
public:
    Accel( double 初速 , double 加速度):
        ISpeed(初速),
        accel(加速度)
    {}

    void Update() override
    {
        speed += accel;
    }
};

/** 0～速度で周期的に変化.*/
///    \include SpeedSample.h
class Wave : public ISpeed
{
private:
    double 角度;
    double 角速度;
public:
    Wave( double 速度 , double 角速度 , double 初角 = 0):
        ISpeed(速度),
        角速度(角速度),
        角度(初角)
    {}

    double Get() const override
    {
        return std::abs(std::sin( 角度 ) * speed);
    }

    void Update() override
    {
        角度 += 角速度;
    }
};

/** 一定速度まで加速.*/
class AccelLimit : public ISpeed
{
private:
    double 加速度;
    double 限界速度;
public:
    AccelLimit(double 初速, double 加速度,double 限界速度) :
        ISpeed(初速),
        加速度(加速度),
        限界速度(限界速度)
    {}

    void Update() override
    {
        speed += 加速度;
        if (speed > 限界速度 && 加速度 > 0) speed = 限界速度;
        if (speed < 限界速度 && 加速度 < 0) speed = 限界速度;
    }
};

}
}