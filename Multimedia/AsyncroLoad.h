#pragma once//☀SDL
#include<Multimedia/Image.h>
#include<Multimedia/Sound.h>
#include<Multimedia/Movie.h>
#include<Multimedia/Font.h>

namespace SDX
{
/** リソースの非同期読み込み設定関数群.*/
///    \include AsyncroLoadSample.h
class AsyncroLoad
{
private:
    AsyncroLoad(void);
    ~AsyncroLoad(void);
public:
    /** Image,Sound等の非同期読み込み状態の設定.*/
    static bool SetIsUse(bool 非同期読み込みフラグ)
    {
        return false;
    }

    /** Image,Sound,Movie,Font等の読み込みが完了しているか取得.*/
    template<typename T>
    static bool CheckData(const T &リソース)
    {
        return false;
    }

    /** 非同期読み込み中のリソース数を取得.*/
    static int GetLoadingCount()
    {
        return false;
    }
};
}