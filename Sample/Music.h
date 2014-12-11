//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//音楽を再生する
#include <SDXFramework.h>

bool SampleMusic()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Music musicA("data/bgm_maoudamashii_piano14.ogg");//このmp3再生出来ない?
	Music musicB("data/bgm_maoudamashii_piano14.ogg");

	musicB.SetFadeInTime(1000);
	musicB.SetFadeOutTime(1000);

	while (System::Update())
	{
		Drawing::String({10,10},Color::White,"AとBでBGMを再生または再開、Sで停止");

		if (Input::key.A.on)
		{
			musicA.Restart();
		}
		if (Input::key.B.on)
		{
			musicB.Restart();
		}
		if (Input::key.S.on)
		{
			Music::Stop();
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}