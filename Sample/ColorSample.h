//色を指定して図形を描画する
bool    SampleColor()
{
    using    namespace    SDX;
    System::Initialise("sample",    600,    400);

    while    (System::Update())
    {
        //赤い線を描画、普通に指定する
        Drawing::Line(10,    10,    200,    10,    Color(255,0,0),    3);

        //緑の四角を描画、省略してみる
        Drawing::Rect(10,    100,    200,    200,    {    0,    255,    0    },    true);

        //青い●を描画、定数を使う
        Drawing::Circle(110,    300,    50,    Color::Blue,    true);

        if    (Input::key.Return.on)    break;//Enterで終了
    }
    System::End();
    return    true;
}