//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] GNU Affero General Public License, version 3
#pragma once
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
    virtual void Event(){};

    bool IsEnd()
    {
        return isEnd;
    }
};
}