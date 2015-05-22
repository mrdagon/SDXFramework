//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//時間を取得したり計測する
#include <SDXFramework.h>

bool SampleTime()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Time::ResetFPS();
	Time::ResetCount();

	int count = 0;

	Pool pool;

	std::vector<int> intS;
	std::vector<std::shared_ptr<int>> dataS;
	std::vector<int*> dataSS;
	//std::vector<SDX::SampleUnion> unionS;
	using UnionS = TempUnion <IUnion, Int, Double>;
	std::vector<UnionS> unionS;
	
	intS.reserve(1000000);
	unionS.reserve(1000000);
	dataS.reserve(1000000);
	dataSS.reserve(1000000);

	while (System::Update())
	{
		count++;
		Time::CheckFPS();//FramePerSecondを更新
		Drawing::String({ 10, 10 }, Color::White, { "FPS:", Time::GetFPS(), "\nNow:", Time::GetNowCount() });

		tm date;
		Time::GetDate(&date);
		Drawing::String({ 10, 100 }, Color::White, { date.tm_year + 1900, "年 ", date.tm_mon + 1, "月 ", date.tm_mday, "日" });

		Time::StartWatch();//処理時間の計測開始

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Circle({ 200, 100, 20 }, Color::White , 5);
		}

		Time::DrawWatch({ 10, 220 }, "○描画100回の処理時間:");

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Rect({ 210, 110, 40 ,40}, Color::White,true);
		}

		Time::DrawWatch({ 10, 240 }, "□描画100回の処理時間:");

		for (int a = 0; a < 100000; ++a)
		{
			int* b;
			b = new int(a);
			delete b;
		}

		Time::DrawWatch({ 10, 260 }, "new delete 十万回の処理時間:");

		char c[sizeof(int) *  100000];

		for (int a = 0; a < 1000000; ++a)
		{
			int* b;
			b = new(c+a/10*sizeof(int)) int(a);
			dataSS.push_back(b);
		}
		dataSS.clear();

		Time::DrawWatch({ 10, 280 }, "placement new 百万回の処理時間:");

		Time::StartWatch();
		for (int a = 0; a < 1000000; ++a)
		{
			dataS.emplace_back( pool.Get<int>(a) , [&pool](int* b) {pool.Destroy(b); });
		}

		//shared_ptr使わないなら自分でDestroyが必要
		dataS.clear();

		Time::DrawWatch({ 10, 300 }, "Pool 十万回の処理時間:");

		for (int a = 0; a < 100000; ++a)
		{
			intS.push_back(a);
			//intS.pop_back();
		}
		intS.clear();
		Time::DrawWatch({ 10, 320 }, "vector 100万回の処理時間:");


		for (int a = 0; a < 1000000; ++a)
		{
			unionS.push_back(Int());
			//unionS.pop_back();
		}
		unionS.clear();
		Time::DrawWatch({ 10, 340 }, "tempUnion 100万回の処理時間:");




		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}