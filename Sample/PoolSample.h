//[未実装]
bool    SamplePool()
{
    using    namespace    SDX;
    System::Initialise("sample",    600,    400);

    while    (System::Update())
    {
        if    (Input::key.Return.on)    break;//Enterで終了    
    }

    System::End();
    return    true;
}