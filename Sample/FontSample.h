﻿//フォントを使って文字列を描画する
bool SampleFont()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    //SDLとDXLIBでフォント指定方法が違うので注意が必要
    Font fontA( SystemFont::Gothic , 20 , 1 , 10 );
    Font fontB( SystemFont::Mincho , 20 , 1 , 10 );

    double angle = 0;

    while(System::Update())
    {
        angle += 0.02;

        fontA.Draw( int(10*angle) ,  10 , Color::White , "Hello!\nこんにちは\n今日は" );
        fontB.Draw( int(10*angle) , 200 , Color::Blue  , "Hello!\nこんにちは\n今日は" );

        fontA.DrawRotate( 300 , 200 , 1 , angle   , Color::White , false , "文字の回転\nてすとしますよ~~~" );
        fontB.DrawRotate( 300 , 200 , 1 , angle/2 , Color::White , false , "文字の回転\nてすとしますよ~~~" );

        if(Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();
    return true;
}