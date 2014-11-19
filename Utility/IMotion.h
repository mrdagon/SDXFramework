//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <SDXFramework.h>
#include <Framework/Model.h>
#include <utility/ISpeed.h>

namespace SDX
{
/**Modelの移動パターンのポリシー.*/
namespace MOTION
{
    /**Modelの移動方法.*/
    /**ジェネリックな設計なら継承不要.*/
    class IMotion
    {
    public:
        virtual void Update(IModel* 移動対象) = 0;
    };
}
}