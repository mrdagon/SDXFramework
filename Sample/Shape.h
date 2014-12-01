//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//図形の当たり判定をする
#include <SDXFramework.h>

bool SampleShape()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	//図形を宣言する
	Circle circle(10, 10, 100);
	Rect rect(60, 60, 100, 100);
	Line line(200, 100, PAI / 4, 300, 5);

	//共通のインターフェースを持っている
	IShape* shapes[3];
	shapes[0] = &circle;
	shapes[1] = &rect;
	shapes[2] = &line;

	while (System::Update())
	{
		circle.SetPos(Input::mouse.x, Input::mouse.y);
		//Lineは回転可能
		line.Rotate(0.01);

		//ダブルディスパッチによる当たり判定
		bool isHit[3];
		isHit[0] = circle.Hit(&rect) || circle.Hit(&line);
		isHit[1] = shapes[1]->Hit(shapes[0]) || shapes[1]->Hit(shapes[2]);
		isHit[2] = shapes[2]->Hit(shapes[0]) || shapes[2]->Hit(shapes[1]);

		for (int a = 0; a < 3; ++a)
		{
			if (isHit[a])
			{
				shapes[a]->Draw(Color::Red, 255);
			}
			else
			{
				shapes[a]->Draw(Color::White, 255);
			}
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}