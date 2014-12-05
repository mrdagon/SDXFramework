//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//画像をアニメーションさせる
bool SampleAnime()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	//画像を分割して読み込む
	Film filmA("image.bmp", 9, 3, 3, 5);
	Film filmB("image.bmp", 9, 3, 3, 5);

	//アニメーション
	Anime animeA(&filmA);
	Anime animeB(&filmB);

	//各コマの再生時間を設定する
	int frames[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	filmB.SetFrameTime(frames);

	while (System::Update())
	{
		animeA.Update();
		animeB.Update();

		animeA.GetFrame()->Draw({ 10, 10 });

		animeB.GetFrame()->Draw({ 100, 10 });

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}