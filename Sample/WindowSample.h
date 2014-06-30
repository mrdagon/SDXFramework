//初期化を行い何かキーを押すと終了する
bool SampleWindow()
{
    using namespace SDX;

    System::Initialise("sampleWindow", 800, 450);

    while (System::Update())
    {
        Drawing::String({ 100, 100 }, Color::White, "Windowクラスのテスト");

        if (Input::key._1.on) Window::SetTitle("ウィンドウタイトルを変えたよ！");//ウィンドウタイトルを変更

        if (Input::key._2.on) Window::SetSizeChangeEnable(true);//ウィンドウの端を掴んで拡大・縮小可能に

        if (Input::key._3.on) Window::SetSize(300, 200);//ウィンドウの大きさを変更

        if (Input::key._4.on) Window::SetFullScreen(true);

        if (Input::key._5.on) Window::SetFullScreen(false);

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}