#pragma once//☀SDXFramework
namespace SDX
{
/** シーンのインターフェース.*/
/**    \include DirectorSample.h*/
class IScene
{
public:
    bool isEnd = false;

    virtual void Update() = 0;
    virtual void Draw() = 0;

    virtual void Init(){};
    virtual void Final(){};

    bool IsEnd()
    {
        return isEnd;
    }
};
}