//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
bool SampleModel()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);
	
	Image image("image.bmp");

	Image ねずみ("data/pipo-enemy034.png");
	Image ひよこ("data/pipo-enemy035.png");

	Model<Point, SpImage> model(Point( 300, 200 ), SpImage(&image));
	Model<Point, SpImage> model2(Point(550, 350), SpImage(&image));

	while (System::Update())
	{
		model.Draw();
		model2.Draw();

		model.Hit(&model2);


		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	
	return true;
}