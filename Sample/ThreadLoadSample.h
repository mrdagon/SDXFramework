//リソースを非同期で読み込む
bool SampleThreadLoad()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    ThreadLoad::SetIsUse(true);//非同期読み込み開始

    //200個同じ画像を非同期で読み込む
    Image loadTest[200];
    for (auto it : loadTest)
    {
        it.Load("image.bmp");
    }

    ThreadLoad::SetIsUse(false);//非同期読み込み終了

    while (System::Update())
    {
        //読み込み中のリソースの数を表示
        Drawing::String(10, 10, Color::White, { "読み込み中Image数", ThreadLoad::GetLoadingCount() });
        if (Input::key.Return.on) break;//Enterで終了    
    }

    System::End();
    return true;
}