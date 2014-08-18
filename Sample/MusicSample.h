//🍣音楽を再生する
bool SampleMusic()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Music music("music.mp3");

    music.Play();

    while (System::Update())
    {
        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}