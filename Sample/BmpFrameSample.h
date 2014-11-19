//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//初期化を行い何かキーを押すと終了する
bool    SampleBmpFrame()
{
    using    namespace    SDX;
    System::Initialise("sample",    600,    400);

    //BmpFrame用の画像を読み込む
    ImagePack    frameImage("image.bmp",9,3,3);

    //BmpFrameを作成
    BmpFrame    bmpFrame;
    bmpFrame.Make(&frameImage);

    while    (System::Update())
    {
        bmpFrame.Draw({ 10, 10, 500, 300 });
        if    (Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();
    return    true;
}