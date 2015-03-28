//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/GUIData.h>
#include <GUI/TmxToGUI.h>
#include <map>

namespace SDX
{
	struct ClassTemplate
	{
		std::string name;//class名
		bool isTile = false;
		std::vector<std::string> proNameS;//プロパティ名
		std::vector<std::string> proTypeS;//プロパティ型

		std::string drawCode;
		std::string updateCode;
		std::string initCode;
		std::string finalCode;
	};

	struct GUI_Scene
	{
		std::string name;//class名

		struct GUI
		{
			GUI(const std::string& name, const std::string& type, const Rect& rect , int gID):
				name(name),
				type(type),
				rect(rect),
				gID(gID),
				isTile(gID != 0)
			{}

			std::string name;//変数名
			std::string type;//型名
			Rect rect;//座標＆大きさ
			bool isTile;//gIDパラメータの有無
			int gID;
			std::vector<std::string> propertieS;
		};

		std::vector<GUI> guiS;
	};

	std::string GetTag(std::string &元の文字 , std::string タグ名)
	{
		if (元の文字.find(タグ名) == std::string::npos)
		{
			return "0";
		}

		int a = 元の文字.find(タグ名) + タグ名.size()+1;
		return 元の文字.substr( a , 元の文字.find("\"" , a) - a );
	}

	void MakeFactoryCode(std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS)
	{
		//Factoryの生成
		File file("GUI_Factory.h", FileMode::Write);

		file.AddLine("#pragma once");
		file.AddLine("#include <GUI/GUIData.h>");
		file.AddLine("#include <vector>");
		file.AddLine("#include <string>");
		for (auto &it : classNameS)
		{
			file.AddLine({ "#include \"", classS[it].name, ".h\"" });
		}
		file.AddLine("");
		file.AddLine("namespace SDX");
		file.AddLine("{");
		file.AddLine("\tvoid GUI_Factory(GUIData& data, std::string& type , int gid, Rect rect, double r, std::vector<std::string>& properties)");
		file.AddLine("\t{");
		int index = 0;
		for (auto &it : classNameS)
		{
			if (index == 0)
			{
				file.AddLine({ "\t\tif(type == \"", it, "\")" });
			}
			else
			{
				file.AddLine({ "\t\telse if(type == \"", it, "\")" });
			}
			file.AddLine("\t\t{");
			std::string str = "\t\t\tdata.dataS.push_back(std::make_shared<" + it + ">(rect";
			if (classS[it].isTile) { str += ",gid"; }
			int num = 0;
			for (auto & it : classS[it].proTypeS)
			{
				if (it == "std::string")
				{
					str += ",properties[" + std::to_string(num) + "].c_str()";
				}
				else if (it == "double")
				{
					str += ",std::atof(properties[" + std::to_string(num) + "].c_str())";
				}
				else
				{
					str += ",std::atoi(properties[" + std::to_string(num) + "].c_str())";
				}
				++num;
			}
			str += "));";
			file.AddLine(str);
			file.AddLine("\t\t}");
			++index;
		}

		file.AddLine("\t}");
		file.AddLine("}");
		file.Close();

	}

	void MakeClassCode(const char* templateClass,std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS )
	{
		//各クラスのコード
		File file(templateClass, FileMode::Read);
		auto strS = file.GetLineS();

		for (auto &itt : classNameS)
		{
			ClassTemplate& cls = classS[itt];
			File classFile((itt + ".h").c_str(), FileMode::Write);

			for (auto &it : strS)
			{
				if (it.find("GUI_NAME") != std::string::npos)
				{
					std::string buf = it;
					int num = buf.find("GUI_NAME");
					buf.erase(num, 8);
					buf.insert(num, cls.name );
					classFile.AddLine(buf);
				}
				else if (it.find("@メンバー宣言") != std::string::npos)
				{
					classFile.AddLine(it);
					if ( cls.isTile)
					{
						classFile.AddLine({ "\t\tint gID;" });
					}
					classFile.AddLine({ "\t\tRect rect;" });
					for (unsigned int a = 0; a < cls.proNameS.size();++a)
					{
						classFile.AddLine({ "\t\t", cls.proTypeS[a] , " ", cls.proNameS[a] , ";" });
					}
				}
				else if (it.find("@コンストラクタ") != std::string::npos)
				{
					std::string str = "\t\t";
					str += cls.name + "(const Rect& rect";
					if ( cls.isTile )
					{
						str += ",int gID";
					}
					for (unsigned int a = 0; a < cls.proNameS.size(); ++a)
					{
						str += ",";
						if (cls.proTypeS[a] == "std::string")
						{
							str += "const char* " + cls.proNameS[a];
						}
						else
						{
							str += cls.proTypeS[a] + " " + cls.proNameS[a];
						}
					}
					str += "):";

					classFile.AddLine(it);
					classFile.AddLine(str);
					for (unsigned int a = 0; a < cls.proNameS.size(); ++a)
					{
						classFile.AddLine({ "\t\t\t", cls.proNameS[a], "(", cls.proNameS[a], ")," });
					}
					if (cls.isTile)
					{
						str += "\t\t\tgID(gID),";
					}
					classFile.AddLine({ "\t\t\trect(rect) " });
					classFile.AddLine({ "\t\t", "{}" });
				}
				else if (it.find("@DefineCode") != std::string::npos)
				{

				}
				else
				{
					classFile.AddLine(it);
				}
			}
		}

	}

	void MakeSceneCode(const char* templateScene, std::vector<std::string> &classNameS, std::map<std::string, ClassTemplate> &classS, std::vector<GUI_Scene> &sceneS, const char* tmxFile)
	{
		File file(templateScene, FileMode::Read);
		auto strS = file.GetLineS();
		file.Close();
		bool isWrite;

		for (auto &scene : sceneS)
		{
			file.Open( (scene.name + ".h").c_str() , FileMode::Write );
			isWrite = true;

			for (auto &str : strS)
			{
				if (str.find("CLASSNAME") != std::string::npos)
				{
					int num = str.find("CLASSNAME");
					std::string buf = str;
					buf.erase(num, 9);
					buf.insert(num, scene.name);
					file.AddLine(buf);
				}
				else if (str.find("@Define") != std::string::npos)
				{
					isWrite = false;
					file.AddLine(str);
					
					for (auto &gui : scene.guiS)
					{

						std::string buf = "\t\t\t";
						buf += gui.type + " " + gui.name + " = { {";
						buf += std::to_string(int(gui.rect.x)) + ",";
						buf += std::to_string(int(gui.rect.y)) + ",";
						buf += std::to_string(int(gui.rect.GetW())) + ",";
						buf += std::to_string(int(gui.rect.GetH())) + "}";

						if (gui.isTile)
						{
							buf += ",";
							buf += gui.gID;
						}

						for (auto &pro : gui.propertieS)
						{
							buf += ",";
							buf += pro;
						}

						buf += "};";
	
						file.AddLine( buf);
					}
				}
				else if (str.find("@Init") != std::string::npos)
				{
					isWrite = false;
					file.AddLine(str);

					for (auto &gui : scene.guiS)
					{
						std::string buf = classS[gui.type].initCode;

						if (buf != "")
						{
							file.AddLine(buf);
						}
					}
				}
				else if (str.find("@Final") != std::string::npos)
				{
					isWrite = false;
					file.AddLine(str);

					for (auto &gui : scene.guiS)
					{
						std::string buf = classS[gui.type].finalCode;

						if (buf != "")
						{
							file.AddLine(buf);
						}
					}
				}
				else if (str.find("@Update") != std::string::npos)
				{
					isWrite = false;
					file.AddLine(str);

					for (auto &gui : scene.guiS)
					{
						std::string buf = classS[gui.type].updateCode;

						if (buf != "")
						{
							file.AddLine(buf);
						}
					}
				}
				else if (str.find("@Draw") != std::string::npos)
				{
					isWrite = false;

					file.AddLine(str);
					for (auto &gui : scene.guiS)
					{
						std::string buf = classS[gui.type].drawCode;

						if (buf != "")
						{
							file.AddLine(buf);
						}
					}
				}
				else if (str.find("@Load") != std::string::npos)
				{
					isWrite = false;
					file.AddLine(str);
					file.AddLine({ "\t\t\tGUIData guiData = TMXtoGUI(\"", tmxFile, "\", GUI_Factory);", });
					file.AddLine("");

					int index = 0;
					for (auto &gui : scene.guiS)
					{
						file.AddLine({ "\t\t\t", gui.name, " = *dynamic_cast<", gui.type , "*>(guiData.dataS[", index, "].get());" });
						++index;
					}
				}
				else if (str.find("@End") != std::string::npos)
				{
					isWrite = true;
					file.AddLine(str);
				}
				else if (isWrite)
				{
					file.AddLine(str);
				}
			}
			file.Close();
		}
	}

	/**tmxファイルとテンプレートからコードを生成する*/
	void TMXtoCode(const char* tmxFile, const char* templateClass , const char* templateScene , const std::string& クラス名プリフィックス = "GUI_")
	{
		//まず内部データに変更
		//その後、クラス情報を取得、その後各クラスのコード、GUI_Factoryのコード、
		File file(tmxFile, FileMode::Read);
		std::vector<std::string> strS = file.GetLineS();
		file.Close();

		std::map<std::string, ClassTemplate> classS;
		std::vector<std::string> classNameS;
		std::vector<GUI_Scene> sceneS;

		std::string nowClass;

		//0何もしない、1コードテンプレート追加、2クラステンプレート追加、3オブジェクト追加
		int mode = 0;

		for (auto &it : strS)
		{
			if (it.find("\"TemplateCode\">") != std::string::npos)
			{
				mode = 1;
			}
			else if (it.find("\"TemplateClass\">") != std::string::npos)
			{
				mode = 2;
			}
			else if (it.find("<objectgroup") != std::string::npos)
			{
				mode = 3;
				nowClass = GetTag(it,"name=");
				sceneS.push_back(GUI_Scene());
				sceneS.back().name = nowClass;
			}
			else if (it.find("<object id=") != std::string::npos)
			{
				if (mode <= 2)
				{
					nowClass = クラス名プリフィックス + GetTag(it, "name=");
					classS[nowClass].name = nowClass;
					if (mode == 1)
					{
						classNameS.push_back(nowClass);
					}
				}
				else
				{		
					std::string name = GetTag(it,"name=");
					std::string type = クラス名プリフィックス + GetTag(it, "type=");
					Rect rect;
					int gid;
					rect.x = std::atoi(GetTag(it, "x=").c_str());
					rect.y = std::atoi(GetTag(it, "y=").c_str());					
					rect.widthRight = std::atoi(GetTag(it, "width=").c_str());
					rect.heightDown = std::atoi(GetTag(it, "height=").c_str());
					gid = std::atoi(GetTag(it, "gid=").c_str());

					sceneS.back().guiS.push_back(GUI_Scene::GUI(name, type, rect, gid));
				}

			}
			else if (it.find("<property name") != std::string::npos)
			{
				if (mode == 1)//Code
				{
					std::string proName = GetTag(it,"name=");
					std::string code = GetTag(it, "value=");

					if (proName == "Draw"){ classS[nowClass].drawCode = code; }
					if (proName == "Final"){ classS[nowClass].finalCode = code; }
					if (proName == "Init"){ classS[nowClass].initCode = code; }
					if (proName == "Update"){ classS[nowClass].updateCode = code; }
				}
				else if (mode == 2)//Class
				{
					//gid
					std::string name = GetTag(it, "name=");
					std::string type = GetTag(it, "value=");

					if (name == "gID")
					{
						classS[nowClass].isTile = true;						
					}
					else
					{
						classS[nowClass].proNameS.push_back(GetTag(it, "name="));
						classS[nowClass].proTypeS.push_back(GetTag(it, "value="));
					}
				}
				else if( mode == 3)//Data
				{
					sceneS.back().guiS.back().propertieS.push_back(GetTag(it, "value="));
				}
			}
		}

		MakeFactoryCode(classNameS, classS);
		MakeClassCode(templateClass, classNameS, classS);
		MakeSceneCode(templateScene, classNameS, classS, sceneS , tmxFile);

		//シーンのコード

		/*
		
		*/
	}
}