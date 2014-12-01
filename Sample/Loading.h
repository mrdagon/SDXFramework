//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//リソースを非同期で読み込む
bool SampleLoading()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	Loading::Start();//非同期読み込み開始

	Image loadTest[200];
	for (int a = 0; a < 200;++a)
	{
		//200個の画像を読み込み
		loadTest[a].Load("image.bmp");
	}

	Loading::End();//非同期読み込み終了

	while (System::Update())
	{
		//読み込み中のリソースの数を表示
		Drawing::String({ 10, 10 }, Color::White, { "読み込み中Image数", Loading::GetSuccesCount() ,"/",Loading::GetLoadingCount()});
		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}