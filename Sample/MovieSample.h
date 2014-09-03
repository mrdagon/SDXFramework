//©SDXFramework http://sourceforge.jp/projects/dxframework/
//🍣動画の再生を行う[未実装]
bool SampleMovie()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    //動画をシングルスレッドで再生
    Movie movie("movie.mp4");
    movie.Play(1, true);

    //動画を非同期で再生
    MovieImage movieImage("movie.mp4");

    while (System::Update())
    {
        movieImage.Draw({ 10, 10 });

        if (Input::key.Z.on) movieImage.Play();
        if (Input::key.X.on) movieImage.Pause();

        if (Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}