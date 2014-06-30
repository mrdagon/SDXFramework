﻿//画像に処理を施して加工する[サンプル作成中]
bool SampleFilter()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Image image("image.bmp");

    Filter::Hsb(&image, 60, 0, -0.5);

    while (System::Update())
    {
        image.Draw({ 10, 10 });
        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}