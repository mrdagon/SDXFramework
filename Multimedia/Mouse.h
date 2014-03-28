#pragma once//☀SDL
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Framework/Shape.h>
#include <Multimedia/InputEnum.h>
#include <Multimedia/Window.h>

namespace SDX
{
/** マウスの状態を表すクラス.*/
/**    \include InputSample.h*/
class Mouse
{
    friend class Input;
private:
    Mouse(const Mouse &mouse){};
    Mouse operator =(const Mouse &mouse) = delete;
    int xBuffer;
    int yBuffer;
public:
    Mouse()
    {
        Reset();
    }

    int x;
    int y;

    int moveX;
    int moveY;

    int Whell;

    bool press[8];

    Key Left;
    Key Right;
    Key Middle;

    Key Button4;
    Key Button5;
    Key Button6;
    Key Button7;
    Key Button8;

    int maxButton;
    
    /** 状態のリセット.*/
    void Reset()
    {
        x = 0;
        y = 0;
        moveX = 0;
        moveY = 0;
        Left.Reset();
        Right.Reset();
        Middle.Reset();
        Button4.Reset();
        Button5.Reset();
        Button6.Reset();
        Button7.Reset();
        Button8.Reset();
        Whell = 0;
    }
        
    /** 状態の更新.*/
    void Update()
    {
        Left.Update( press[(int)MouseCode::Left] );
        Right.Update( press[(int)MouseCode::Right] );
        Middle.Update( press[(int)MouseCode::Middle] );

        Button4.Update( press[(int)MouseCode::_4] );
        Button5.Update( press[(int)MouseCode::_5] );
        Button6.Update( press[(int)MouseCode::_6] );
        Button7.Update( press[(int)MouseCode::_7] );
        Button8.Update( press[(int)MouseCode::_8] );

        moveX = xBuffer - x;
        moveY = yBuffer - y;

        x = xBuffer;
        y = yBuffer;
    }

    /** カーソルの表示設定[DXLIB].*/
    bool SetVisible(bool 表示フラグ)
    {
        return false;
    }
    
    /** カーソル位置を移動.*/
    bool SetPoint( int 移動先X , int 移動先Y )
    {
        SDL_WarpMouseInWindow(Window::Single().handle, x, y);
        return true;
    }
};
}