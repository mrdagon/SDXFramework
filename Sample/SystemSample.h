//ライブラリの初期化等を行う
bool    SampleSystem()
{
    using    namespace    SDX;
    System::SetAlwaysRun(true);//ウィンドウが非アクティブでも処理を続行
    System::SetOutputLog(false);//動作ログを出力しない

    System::Initialise("sample",    600,    400);//ウィンドウタイトルを指定して、初期化する

    #ifdef    MAC_OSX
        Drawing::GetFont().Load("/System/Library/Fonts/AquaKana.ttc",    20    ,    1,    0);
    #endif
    
    while    (System::Update())//ウィンドウの更新や、入力の更新等を行う
    {
        if    (Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();//ライブラリの終了処理を行う
    return    true;
}