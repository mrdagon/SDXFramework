//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//時間を取得したり計測する
#include <SDXFramework.h>
#include <Sample/TimeTest.h>
#include <Utility/Any.h>

bool SampleTime()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Time::ResetFPS();
	Time::ResetCount();

	int count = 0;

	Pool pool;

	std::vector<int> intS;
	using UnionS = TempUnion<IUnion, Int, Double>;
	using AnionS = TempUnion<IUnion, Int, Double>;
	std::vector<UnionS> unionS;
	std::vector<AnionS> anionS;
	std::vector<Any<IUnion,20>> sAniS;

	std::vector<Double> sDoubleS;
	std::vector<Double*> pDoubleS;
	std::vector<std::shared_ptr<Double>> shDoubleS;

	sAniS.reserve(1000000);
	intS.reserve(1000000);
	unionS.reserve(1000000);

	while (System::Update())
	{
		if (Input::key.Return.on){ break;}//Enterで終了
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
			auto b = new Double();
			delete b;
		}

		Time::DrawWatch({ 10, 260 }, "new delete 十万回の処理時間:");

		char c[1000000];//大きすぎるとエラーになるので
		for (int a = 0; a < 1000000; ++a)
		{
			pDoubleS.push_back(new(c + a / 100 * sizeof(Double)) Double());
		}
		pDoubleS.clear();

		Time::DrawWatch({ 10, 280 }, "placement new 百万回の処理時間:");

		Time::StartWatch();
		//shared_ptr使うと遅いので自力でDestroy
		for (int a = 0; a < 1000000; ++a)
		{
			pDoubleS.push_back(pool.Get<Double>());
		}

		for (int a = 0; a < 1000000; ++a)
		{
			pool.Destroy( pDoubleS[a] );
		}

		pDoubleS.clear();

		Time::DrawWatch({ 10, 300 }, "Pool Double 100万回の処理時間:");
		
		for (int a = 0; a < 1000000; ++a)
		{
			intS.push_back(a);
		}
		intS.clear();

		Time::DrawWatch({ 10, 320 }, "vector<int> 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			unionS.push_back( Double());
		}
		unionS.clear();
		Time::DrawWatch({ 10, 340 }, "tempUnion 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			anionS.push_back( Double());
		}
		anionS.clear();
		Time::DrawWatch({ 10, 360 }, "AnyUnion 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			sAniS.push_back( Double() );
		}
		sAniS.clear();
		Time::DrawWatch({ 10, 380 }, "Any 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			sDoubleS.emplace_back();
		}
		sDoubleS.clear();
		Time::DrawWatch({ 10, 400 }, "vector<Double> 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			shDoubleS.push_back( std::make_shared<Double>() );
		}
		shDoubleS.clear();
		Time::DrawWatch({ 10, 420 }, "shared_ptr 100万回の処理時間:");
	}

	System::End();
	return true;
}