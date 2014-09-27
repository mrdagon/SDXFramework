//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
/** BGM用音声を表すクラス.*/
/**    \include MusicSample.h*/
class Music
{
    friend class System;
private:
    std::string fileName;
    int volume;
    Mix_Music* handle;
    static int nowVolume;
public:
    Music(){};
    ~Music(){};
    
    /** 音声ファイルを登録.*/
    Music(const char *ファイル名 , double 音量 = 1.0)
    {
        Music::Load( ファイル名 , 音量 );
    }
    
    /** 音声ファイルを登録.*/
    /** 音量は 0～1.0で指定、ファイルはメモリには読み込まない。*/
    void Load(const char *ファイル名 , double 音量 = 1.0)
    {
        this->fileName = ファイル名;

        handle = Mix_LoadMUS(ファイル名);                

        volume = int(音量*255);
    }
        
    /** 音声ファイルを再生.*/
    /** Musicファイルは複数同時に再生する事は出来ない。\n
        現在再生中の音声は停止する。*/
    bool Play(PlayType 再生方法 = PlayType::Loop)
    {
        switch (再生方法)
        {
        case PlayType::Back:
            Mix_PlayMusic(handle, 1);
            break;
        case PlayType::Loop:
            Mix_PlayMusic(handle, -1);
            break;
        }
        Mix_VolumeMusic(volume/2);
    nowVolume = volume / 2;

        return true;
    }

    /**0～1.0で音量を設定.*/
    void SetVolume(double 音量)
    {
        volume = int(音量*255);
    }

    /** 再生中か取得.*/
    /** いずれかのMusicが再生中ならtureを返す*/
    static bool Check()
    {
        return !Mix_PlayingMusic();
    }

    /** 再生中のMusicを停止.*/
    static bool Stop()
    {
        return !Mix_HaltMusic();
    }

    /** 再生中の音量を変更.*/
    /** いずれかのMusicが再生中なら音量を変更*/
    static void ChangeVolume(double 音量)
    {
        Mix_VolumeMusic(int(音量*255));
    }

};
}