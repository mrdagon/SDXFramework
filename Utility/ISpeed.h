//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
/** 速度変化のポリシー.*/
namespace SPEED
{
/** 変化する数値を表す抽象クラス.*/
///    \include SpeedSample.h
class ISpeed
{
public:
    ISpeed(){};

    virtual ~ISpeed(){};

    /** 現在の速度を取得.*/
    virtual double Get() const = 0;

    /** 速度を更新.*/
    virtual double Update() = 0;
};
}
}