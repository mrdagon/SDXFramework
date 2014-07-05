//初期化を行い何かキーを押すと終了する
bool SampleCamera()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Camera camera(300,200,1);
    camera.SetActive();

    Image image("image.bmp");

    Model<> model({300,200},{&image} );
    Model<> model2({550, 350},{&image});
    model2.SetIsCamera(false);
    
    while(System::Update())
    {
        model.Draw();
        model2.Draw();
        camera.Update();

        if(Input::pad.Down.hold )   Camera::Now()->MoveForcus( 0, 5);
        if(Input::pad.Up.hold   )   Camera::Now()->MoveForcus( 0,-5);
        if(Input::pad.Right.hold)   Camera::Now()->MoveForcus( 5, 0);
        if(Input::pad.Left.hold )   Camera::Now()->MoveForcus(-5, 0);

        if(Input::key.Z.hold)       Camera::Now()->SetZoomForcus(2);
        if(Input::key.X.hold)       Camera::Now()->SetZoomForcus(0.5);
        if(Input::key.C.hold)       Camera::Now()->SetZoomForcus(1);

        if(Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();
    return    true;
}