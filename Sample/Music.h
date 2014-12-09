//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//音楽を再生する
#include <SDXFramework.h>

bool SampleMusic()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Music musicA("bgm_maoudamashii_healing01.mp3");
	Music musicB("bgm_maoudamashii_piano14.ogg");

	musicB.SetFadeinTime(1000);

	while (System::Update())
	{
		if (Input::key.A.on)
		{
			musicA.Restart();
		}
		if (Input::key.B.on)
		{
			musicB.Restart();
		}

		//音量変更

		//停止-フェードアウト付き

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}