#pragma once//☀DXLIB
#include <Multimedia/SDX.h>
#include <Multimedia/Window.h>
#include <Multimedia/Sound.h>

namespace SDX
{
/** BGM用音声を表すクラス.*/
/**	\include MusicSample.h*/
class Music
{
private:
	std::string fileName;
	int volume;

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
		volume = int(音量*255);
	}
		
	/** 音声ファイルを再生.*/
	/** Musicファイルは複数同時に再生する事は出来ない。\n
		現在再生中の音声は停止する。*/
	bool Play(PlayType 再生方法 = PlayType::Back)
	{
		const bool ok = !DxLib::PlayMusic(this->fileName.c_str(), (int)再生方法);
		DxLib::SetVolumeMusic( volume );
		return ok;
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
		return !DxLib::CheckMusic();
	}

	/** 再生中のMusicを停止.*/
	static bool Stop()
	{
		return !DxLib::StopMusic();
	}

    /** 再生中の音量を変更.*/
	/** いずれかのMusicが再生中なら音量を変更*/
	static void ChangeVolume(double 音量)
	{
	}

};
}