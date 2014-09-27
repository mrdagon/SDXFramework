//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] GNU Affero General Public License, version 3
#pragma once
#include <Multimedia/Key.h>
#include <Multimedia/Window.h>

namespace SDX
{
class Gesture
{
friend class Input;
private:
    void Position(double X座標, double Y座標)
    {
        const double aspA = Window::Single().aspect;
        const double aspB = (double)Window::GetWidth() / Window::GetHeight();

        if (aspA == aspB)
        {
            xBuffer = int(X座標 * Window::GetWidth());
            yBuffer = int(Y座標 * Window::GetHeight());
        }
        else if (aspA > aspB){
            //横が余る
            double rate = aspA / aspB;
            double pos = (X座標 - (rate - 1) / rate / 2) * rate;
            xBuffer = int(pos * Window::GetWidth());
            yBuffer = int(Y座標 * Window::GetHeight());
        }
        else{
            //上が余る
            double rate = aspB / aspA;
            double pos = (Y座標 - (rate - 1) / rate / 2) * rate;
            xBuffer = int(X座標 * Window::GetWidth());
            yBuffer = int(pos * Window::GetHeight());
        }
    }

    bool press = false;
    double xBuffer;
    double yBuffer;
public:
    bool on = false;

    double rotate = 0;//回転ジェスチャー
    double pinche = 0;//ピンチ操作

    double x = 0;//ジェスチャー操作の中心点
    double y = 0;

    int fingerCount = 0;//ジェスチャーに使った指の本数

    void Update()
    {
        on = press;
        press = false;
    }

    void Reset()
    {    
        press = false;
        on = false;
        rotate = 0;
        pinche = 0;
        x = 0;
        y = 0;
        fingerCount = 0;
    }
};

class Touch
{
friend class Input;
private:
    bool press = false;
    double xBuffer;
    double yBuffer;

    void Position(double X座標 , double Y座標)
    {
        const double aspA = Window::Single().aspect;
        const double aspB = (double)Window::GetWidth() / Window::GetHeight();

        if (aspA == aspB)
        {
            xBuffer = int(X座標 * Window::GetWidth());
            yBuffer = int(Y座標 * Window::GetHeight());
        }else if (aspA > aspB){
            //横が余る
            double rate = aspA / aspB;
            double pos = (X座標 - (rate - 1) / rate / 2) * rate;
            xBuffer = int(pos * Window::GetWidth());
            yBuffer = int(Y座標 * Window::GetHeight());
        }else{
            //上が余る
            double rate = aspB / aspA;
            double pos = ( Y座標 - (rate - 1) / rate / 2) * rate;
            xBuffer = int(X座標 * Window::GetWidth());
            yBuffer = int(pos * Window::GetHeight());
        }
    }

public:
    double x = 0;
    double y = 0;

    double moveX = 0;
    double moveY = 0;

    bool on = false;
    bool off = false;
    bool hold = false;

    unsigned int  holdCount = 0;//押されている時間    

    /** 状態のリセット.*/
    void Reset()
    {
        x = 0;
        y = 0;

        moveX = 0;
        moveY = 0;

        on = false;
        off = false;
        hold = false;
        press = false;
    }

    /** 状態の更新.*/
    void Update()
    {
        on = (!hold && press);
        off = (hold && !press);
        hold = press;
        if (press)
        {
            ++holdCount;
        }else{
            holdCount = 0;
        }

        if ( !on )
        {
            moveX = xBuffer - x;
            moveY = yBuffer - y;
        }
        else
        {
            moveX = 0;
            moveY = 0;
        }

        x = xBuffer;
        y = yBuffer;
    }
};
}