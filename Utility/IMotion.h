#pragma once//☀SDXFramework
#include <SDXFrameWork.h>
#include <Framework/Model.h>
#include <utility/ISpeed.h>

namespace SDX
{
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