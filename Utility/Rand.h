#pragma once
#include <random>

namespace SDX
{
/** 乱数生成関数群.*/
/**    \include RandSample.h*/
class Rand
{
private:
    static std::mt19937 engine;
    Rand();
    ~Rand();
public:
    /** 乱数を初期化する.*/
    static void Reset(int 初期化子)
    {
        engine.seed(初期化子);
    }
    
    /** 0～最大値の乱数を取得.*/
    static double Get(double 最大値)
    {
        std::uniform_real_distribution<double> range(0.0 , 最大値);
        return range(engine);
    }
    static int Get(int 最大値)
    {
        std::uniform_int_distribution<int> range(0 , 最大値);
        return range(engine);
    }
    
    /** 範囲を指定して乱数を取得.*/
    static double Get( double 最小値 , double 最大値)
    {
        std::uniform_real_distribution<double> range( 最小値 , 最大値);
        return range(engine);
    }
    static int Get( int 最小値 , int 最大値)
    {
        std::uniform_int_distribution<int> range( 最小値 , 最大値);
        return range(engine);
    }

    /** 範囲を指定して乱数を取得.*/
    static bool Coin(double trueになる確率)
    {
        if (trueになる確率 >= 1.0) return true;

        std::bernoulli_distribution coin( std::min( trueになる確率 , 1.0) );

        return coin(engine);
    }
};
}