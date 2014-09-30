//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
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