//���\�[�X��񓯊��œǂݍ���
bool SampleAsyncroLoad()
{
    using namespace SDX;
    System::Initialise("sample", 600, 400);

    AsyncroLoad::SetIsUse(true);//�񓯊��ǂݍ��݊J�n

    //200�����摜��񓯊��œǂݍ���
    Image loadTest[200];
    for (auto it : loadTest)
    {
        it.Load("image.bmp");
    }

    AsyncroLoad::SetIsUse(false);//�񓯊��ǂݍ��ݏI��

    while (System::Update())
    {
        //�ǂݍ��ݒ��̃��\�[�X�̐���\��
        Drawing::String(10, 10, Color::White, "�ǂݍ��ݒ�Image��:%d", AsyncroLoad::GetLoadingCount());
        if (Input::key.Return.on) break;//Enter�ŏI��
    }

    System::End();
    return true;
}