//🍣入力を取得する
bool SampleInput()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    std::string message = "";

    while (System::Update())
    {
        if (Input::mouse.Left.on)  message = "クリックした";
        if (Input::mouse.Left.off) message = "離した";

        if (Input::key.Z.hold           ) message = "Zを押している";
        if (Input::key.Z.holdCount > 60 ) message = "Zを長押し";

        //マウスの位置に文字を描画
        Drawing::String({ Input::mouse.x, Input::mouse.y }, Color::White, message.c_str());

        if (Input::key.Return.on) break;//Enterで終了    
    }

    System::End();
    return true;
}