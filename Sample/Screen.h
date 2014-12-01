//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
#include <SDXFramework.h>

bool SampleScreen()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	Image image("image.bmp");

	while (System::Update())
	{
		//輝度を変更して描画
		Screen::SetBright(Color::Red);
		image.Draw({ 0, 0 });
		Screen::SetBright(Color::Green);
		image.Draw({ 200, 0 });
		Screen::SetBright(Color::Blue);
		image.Draw({ 400, 0 });

		//半透明描画
		Screen::SetBright(Color::White);
		Screen::SetBlendMode(BlendMode::Alpha, 128);
		image.Draw({ 0, 200 });
		Screen::SetBlendMode(BlendMode::NoBlend, 0);

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}