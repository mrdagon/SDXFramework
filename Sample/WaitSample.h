﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//処理停止関数を試す
bool SampleWait()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    Drawing::String({ 10, 10 }, Color::White, "5秒待ちます・・・");
    System::Update();

    Wait::Timer(5000);//5000ミリ秒停止

    Drawing::String({ 10, 10 }, Color::White, "何かキーを押すと終了します");
    System::Update();

    Wait::PushKey();//何かキーを押すまで停止

    System::End();
    return true;
}