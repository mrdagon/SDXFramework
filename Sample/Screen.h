//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
#include <SDXFramework.h>

bool SampleScreen()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);
	
	Image image("data/pipo-enemy035.png");

	Screen::SetBackColor(Color::White);

	while (System::Update())
	{
		//輝度を変更して描画
		Screen::SetBright(Color::Red);
		image.Draw({ 0, 0 });
		Screen::SetBright(Color::Green);
		image.Draw({ 100, 0 });
		Screen::SetBright(Color::Blue);
		image.Draw({ 200, 0 });

		//半透明描画
		Screen::SetDrawMode({ 255, 255, 255, 128 }, BlendMode::Alpha);
		image.Draw({ 300, 0 });
		Screen::SetDrawMode();//引数無しで解除

		//描画範囲制御
		Screen::SetClip({ 0, 100 , 60, 120 });
		image.Draw({ 0, 100 });
		Screen::SetClip();//引数無しで解除

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}