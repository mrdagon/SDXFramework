//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Rect.h>

namespace SDX
{
    /** GUIオブジェクトのテンプレート.*/
    class IGUI
    {
    public:
        IGUI(int id, const Rect& rect , double angle):
            id(id),
            rect(rect),
            angle(angle)
        {}

        virtual ~IGUI()
        {}

        int id;
        Rect rect;
        double angle;

        virtual void Init(){};
        virtual void Final(){};
        virtual void Draw(){};
        virtual void Update(){};

        /** マウスオーバー判定 */
        bool isMouse()
        {
            return rect.Hit( &Input::mouse.GetPoint() );
        }

        /** クリックorタッチ判定 */
        bool isClick()
        {
            return Input::mouse.Left.on && rect.Hit(&Input::mouse.GetPoint());
        }
    };
}