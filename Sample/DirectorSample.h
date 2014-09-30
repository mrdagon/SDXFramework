//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//🍣[サンプルコード作成中]
bool SampleDirector()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    while (System::Update())
    {
        if(Input::key.Return.on) break;//Enterで終了
    }

    System::End();
    return true;
}