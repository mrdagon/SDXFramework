#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

using namespace SDX;

enum class ControlType
{
	Label,
	Picture,
	Button,
	Unknown
};

struct UIData
{
	Rect Size;
	ControlType Type;
	std::string Name;
	std::string Tag;
};

int main(int argc, char* argv[])
{
	using namespace SDX;;

	//自作ライブラリのクラス、一行ずつ文字列を読みこんで格納している
	File file("MyForm.h", FileMode::Read);
	std::vector<std::string> strS = file.GetLineS();

	std::vector<UIData> uiS;
	UIData client;

	int index = -1;
	int a, b, c;

	for (auto &it : strS)
	{

		if (it.find("private: System::Windows::Forms::") != std::string::npos)
		{
			uiS.push_back(UIData());
			if (it.find("Button") != std::string::npos) { uiS[uiS.size() - 1].Type = ControlType::Button; }
			else if (it.find("PictureBox") != std::string::npos) { uiS[uiS.size() - 1].Type = ControlType::Picture; }
			else if (it.find("Label") != std::string::npos) { uiS[uiS.size() - 1].Type = ControlType::Label; }
			else { uiS[uiS.size() - 1].Type = ControlType::Unknown; }
		}
		//->を検索文字に入れると誤爆しない
		else if (it.find("->Location") != std::string::npos)
		{
			++index;
			a = it.find_first_of("(");
			b = it.find_first_of(",");
			c = it.find_first_of(")");
			uiS[index].Size.x = std::atoi(it.substr(a + 1, b - a).c_str());
			uiS[index].Size.y = std::atoi(it.substr(b + 1, c - b).c_str());
		}
		else if (it.find("->Name") != std::string::npos)
		{
			a = it.find_first_of("\"");
			b = it.find_last_of("\"");
			uiS[index].Name = it.substr(a + 1, b - a - 1).c_str();
		}
		else if (it.find("->Size") != std::string::npos)
		{
			a = it.find_first_of("(");
			b = it.find_first_of(",");
			c = it.find_first_of(")");
			uiS[index].Size.widthRight = std::atoi(it.substr(a + 1, b - a).c_str());
			uiS[index].Size.heightDown = std::atoi(it.substr(b + 1, c - b).c_str());
		}
		else if (it.find("->ClientSize") != std::string::npos)
		{
			//フォーム全体の大きさ
			a = it.find_first_of("(");
			b = it.find_first_of(",");
			c = it.find_first_of(")");
			client.Size = { 0, 0, 0, 0 };
			client.Size.widthRight = std::atoi(it.substr(a + 1, b - a).c_str());
			client.Size.heightDown = std::atoi(it.substr(b + 1, c - b).c_str());
			break;//ここで終了
		}
		else if (it.find("->Tag") != std::string::npos)
		{
			a = it.find_first_of("\"");
			b = it.find_last_of("\"");
			uiS[index].Tag = it.substr(a + 1, b - a - 1).c_str();
		}
	}

	file.Close();
	//必要ならcsvにして出力とかする

	file.Open("UIData.csv", FileMode::Write);
	std::string data;

	for (auto && it : uiS)
	{
		data = it.Name + "," + it.Tag + "," + std::to_string((int)it.Type) + "," + std::to_string(it.Size.x) + "," + std::to_string(it.Size.y) + "," + std::to_string(it.Size.widthRight) + "," + std::to_string(it.Size.heightDown) + "\r\n";
		file.Write(data, false);
	}

	file.Close();
	//こんな感じでコードの雛形、あるいはコンパイル可能なコードを作成する
	file.Open("Sample.h", FileMode::Write);
	file.Write(data = "void Draw() override\r\n{\r\n", false);

	for (auto & it : uiS)
	{
		switch (it.Type)
		{
		case ControlType::Button:
			data = "DrawButton(" + it.Tag + "," + std::to_string(it.Size.x) + ");\r\n" /*以下パラメータ*/;
			break;
		case ControlType::Label:
			data = "DrawString(" + it.Tag + "," + std::to_string(it.Size.x) + ");\r\n" /*以下パラメータ*/;
			break;
		case ControlType::Picture:
			data = "DrawImage(" + it.Tag + "," + std::to_string(it.Size.x) + ");\r\n" /*以下パラメータ*/;
			break;
		default:
			break;
		}
		file.Write(data, false);
	}

	file.Write(data = "}", false);
	file.Close();

	return 0;
}