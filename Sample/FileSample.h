//ファイルに書き込みと読み込みを行う
bool SampleFile()
{
    using namespace SDX;

    File fileA("test.txt", FileMode::Write, true );
    int a = 100;
    char c = 123;
    std::string    str = "こんにちは";
    fileA.Write(a);
    fileA.Write(c);
    fileA.Write(str);
    fileA.Close();

    File fileB("test.txt", FileMode::Read, true );
    int b;
    std::string str2;
    fileB.Read(b);
    fileB.Read(c);
    fileB.Read(str2);
    fileA.Close();

    System::Initialise("sample", 600, 400);

    while (System::Update())
    {
        Drawing::String(10, 10, Color::White, { "書き込んだ数字は:", b, "\n書き込んだ文字は:", str2 });

        if (Input::key.Return.on) break;//Enterで終了    
    }

    System::End();
    return    true;
}