#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

using namespace SDX;
int main(int argc, char* argv[])
{
	using namespace SDX;
	System::Initialise("BmpFontOutputer", 640, 480);

	//�ݒ�t�@�C���̓ǂݍ���
	File file("config.txt", FileMode::Read);
	auto strS = file.GetLineS();

	int size = strS.size();
	Screen::Clear();

	int y = 0;

	//�t�H���g�̏�����
	for (unsigned int a = 2; a < strS.size(); ++a)
	{
		Font fontA(strS[1].c_str(), std::atoi(strS[a].c_str()), 0, false);
		if (a == 2)
		{
			fontA.Draw({ 0, y }, Color::White, { "�t�H���g��:" , strS[1] , "\n�������X�g:", strS[0] });
			y += std::atoi(strS[a].c_str());
		}
		Screen::Flip();
		System::ProcessMessage();
		fontA.MakeBMPFont(strS[0]);
		y += std::atoi(strS[a].c_str());
		fontA.Draw({ 0, y }, Color::White, { "Size = ", std::atoi(strS[a].c_str()), "�쐬����" });

		Screen::Flip();
	}

	return 0;
}