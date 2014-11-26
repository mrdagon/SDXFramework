//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//音楽を再生する
#include <SDXFramework.h>

bool SampleMusic()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	Music music("music.mp3");

	music.Play();

	while (System::Update())
	{
		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}