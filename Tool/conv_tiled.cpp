#include <SDXFrameWork.h>
#include <Multimedia/SDXafx.h>

#include <Tiled/TmxToCode.h>

int main(int argc, char *argv[])
{
	//�ݒ��ǂݍ���
	SDX::File file("tiled/config_tiled.txt", SDX::FileMode::Read);
	auto strS = file.GetCsvToString2();
	file.Close();
	std::string tmxfile;
	std::string tClass;
	std::string tScene;
	std::string tEnum;
	std::string prefix;

	for (auto &str : strS)
	{
		if (str[0] == "tmxfile")
		{
			tmxfile = str[1];
		}
		else if (str[0] == "class")
		{
			tClass = "tiled/";
			tClass += str[1];
		}
		else if(str[0] == "scene")
		{
			tScene = "tiled/";
			tScene += str[1];
		}
		else if(str[0] == "enum")
		{
			tEnum = "tiled/";
			tEnum += str[1];
		}
		else if(str[0] == "prefix")
		{
			prefix = str[1];
		}
	}


	//1�ڂ͎��s�t�@�C���̃p�X�A�ȉ��h���b�v�����t�@�C��
	if ( argv[1] != nullptr)
	{
		//�t�@�C������ύX
		tmxfile = argv[1];
		file.Open("config_tiled.txt", SDX::FileMode::Write);
		file.AddLine({ "tmxfile," , tmxfile});
		file.AddLine({ "class,", tClass });
		file.AddLine({ "scene,", tScene });
		file.AddLine({ "enum,", tEnum });
		file.AddLine({ "prefix,", prefix });
		file.Close();
	}
	
	SDX::TMXtoCode(tmxfile.c_str(), tClass.c_str() , tScene.c_str() , tEnum.c_str() , prefix.c_str() );

	return 0;
}