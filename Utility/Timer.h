//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Color.h>
#include <chrono>

namespace SDX
{
/** 時間と日付を取得する関数群.*/
/** わりと標準ライブラリで良い感じはある.*/
/**    \include TimerSample.h*/
class Time
{
private:
    double fps;
    std::chrono::system_clock::time_point reset;
    std::chrono::system_clock::time_point fpsCounter;
    std::chrono::system_clock::time_point watch;

    Time(void)
    {
        this->ResetCount();
    }

    ~Time(void){};

    static Time singleton;
    
    static Time& Single()
    {
        return singleton;
    }

public:
    /** 時間の初期化.*/
    static void ResetCount()
    {
        Single().reset = std::chrono::system_clock::now();
    }
    
    /** リセット後の経過時間のミリ秒で取得(小数点以下).*/
    static double GetNowCount()
    {
        auto diff = std::chrono::system_clock::now() - Single().reset;        
        return (double)std::chrono::duration_cast<std::chrono::microseconds>(diff).count()/ 1000;
    }

    /** 日付を取得.*/
    static void GetDate(tm *現在時刻)
    {
        time_t timer;

        time( &timer);

        localtime_s( 現在時刻 , &timer);
    }
        
    /** FPSを取得.*/
    static double GetFPS()
    {
        return Single().fps;
    }
    
    /** FPSの計測開始.*/
    static void ResetFPS()
    {
        Single().fpsCounter = std::chrono::system_clock::now();
    }
    
    /** FPS計測を更新.*/
    static void CheckFPS()
    {
        auto diff = std::chrono::system_clock::now() - Single().fpsCounter;        
        Single().fps = 1000000.0 / (double)std::chrono::duration_cast<std::chrono::microseconds>(diff).count();
        Single().fpsCounter = std::chrono::system_clock::now();
    }
    
    /** 処理時間計測開始.*/
    static void StartWatch()
    {
        Single().watch = std::chrono::system_clock::now();
    }
    
    /** 処理時間計測終了.*/
    /**    StartWatchからの経過時間をミリ秒単位で描画\n
        続けてDrawWatchする事も可能*/
    static void DrawWatch(const Point &座標, const char* 描画文字列)
    {
        std::string buf = 描画文字列;
        buf += " = ";

        auto diff = std::chrono::system_clock::now() - Single().watch;
        Drawing::String(座標, Color(255, 255, 255), { buf , (double)std::chrono::duration_cast<std::chrono::microseconds>(diff).count() / 1000 });
        Single().watch = std::chrono::system_clock::now();
    }
};

}