//©SDXFramework http://sourceforge.jp/projects/dxframework/
//🍣画像を描画する
bool SampleImage()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Image image("image.jpeg");

    double angle = 0;

    while (System::Update())
    {
        angle += 0.1;

        image.Draw({ 10, 10 }, true);//反転して描画

        image.DrawExtend({ 400, 10 }, {420, 30 });//指定矩形に描画

        image.DrawRotate({ 400, 200 }, 0.5, angle);//角度と拡大率を指定して描画

        Drawing::String({ 10, 10 }, Color::White, { "あいうえお", "\n", 123.456 });

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return    true;
}