//🍣初期化を行い何かキーを押すと終了する[未実装]
bool SampleCamera()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    System::End();
    return    true;
}