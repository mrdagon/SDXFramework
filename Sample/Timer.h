//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//時間を取得したり計測する
#include <SDXFramework.h>

bool SampleTimer()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	Time::ResetFPS();
	Time::ResetCount();

	int count = 0;


	while (System::Update())
	{
		count++;
		Time::CheckFPS();//FramePerSecondを更新
		Drawing::String({ 10, 10 }, Color::White, { "FPS:", Time::GetFPS(), "\nNow:", Time::GetNowCount() });

		tm date;
		Time::GetDate(&date);

		//Drawing::String({ 10, 100 }, Color::White, { date.tm_year + 1900, "年    ", date.tm_mon + 1, "月    ", date.tm_mday, "日" });

		Time::StartWatch();//処理時間の計測開始

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Circle({ 100, 100, 20 }, Color::White);
		}

		Time::DrawWatch({ 10, 220 }, "処理時間:");//StartWatchかDrawWatchを呼んでからかかった時間をミリ秒で表示

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Circle({ 110, 110, 20 }, Color::White,5);
		}

		Time::DrawWatch({ 10, 240 }, "処理時間:");//StartWatchかDrawWatchを呼んでからかかった時間をミリ秒で表示


		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}