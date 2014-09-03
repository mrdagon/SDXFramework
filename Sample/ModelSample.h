//©SDXFramework http://sourceforge.jp/projects/dxframework/
//🍣初期化を行い何かキーを押すと終了する
//\todo 未実装
bool SampleModel()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);
	/*
    Camera camera(300, 200, 1);
    camera.SetActive();

    Image image("image.bmp");

    Model model(new Point(300, 200), new SpImage(&image));
    Model model2(new Point(550, 350), new SpImage(&image));
    model2.SetIsCamera(false);

    while (System::Update())
    {
        model.Draw();
        model2.Draw();
        camera.Update();

        if (Input::pad.Down.hold  ) Camera::Now()->MoveForcus(0, 5);
        if (Input::pad.Up.hold    ) Camera::Now()->MoveForcus(0, -5);
        if (Input::pad.Right.hold ) Camera::Now()->MoveForcus(5, 0);
        if (Input::pad.Left.hold  ) Camera::Now()->MoveForcus(-5, 0);

        if (Input::key.Z.hold)      Camera::Now()->SetZoomForcus(2);
        if (Input::key.X.hold)      Camera::Now()->SetZoomForcus(0.5);
        if (Input::key.C.hold)      Camera::Now()->SetZoomForcus(1);

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
	*/
    return true;
}