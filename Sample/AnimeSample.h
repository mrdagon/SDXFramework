//画像をアニメーションさせる
bool    SampleAnime()
{
    using    namespace    SDX;
    System::Initialise("sample",    600,    400);

    //画像を分割して読み込む
    Anime    animeA    =    Anime("image.bmp",    9,    3,    3,    5);
    Anime    animeB    =    Anime("image.bmp",    9,    3,    3,    5    );

    //アニメーション
    Anime::Player    countA(&animeA);
    Anime::Player    countB(&animeB);

    //各コマの再生時間を設定する
    int    frames[9]    =    {    1,    2,    3,    4,    5,    6,    7,    8,    9    };
    animeB.SetFrameTime(    frames    );

    while (System::Update())
    {
        countA.Update();
        countB.Update();

        countA.GetFrame()->Draw({ 10, 10 });

        countB.GetFrame()->Draw({100, 10});

        if    (Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();
    return    true;
}