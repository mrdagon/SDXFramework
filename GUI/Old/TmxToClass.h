//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/TmxToGUI.h>

namespace SDX
{
		/**tmxファイルからGUIクラスのコードとGUI_Factory関数を生成する*/
		void TMXtoClass(const char* tmxFileName , const char* templateFileName)
		{
			File file(tmxFileName,FileMode::Read);
			File templateFile(templateFileName, FileMode::Read);
			std::vector<std::string> strS = file.GetLineS();
			std::vector<std::string> templateS = templateFile.GetLineS();
			
			std::string className = "";
			std::vector<std::string> propertyS;
			std::vector<std::string> factoryS;
			bool isProperty = false;
			bool isImage = false;
			int index = 0;

			for (auto &it : strS)
			{
				if ( it.find("<objectgroup") != std::string::npos )
				{
					isImage = false;
					isProperty = (strS[index + 1].find("<properties>") != std::string::npos);
					int a = it.find("name=") + 6;
					className = it.substr(a, it.find("\"", a) - a);
					propertyS.clear();
				}
				else if ( it.find("gid=") != std::string::npos)
				{
					//タイル用のレイヤー扱いにする
					isImage = true;
				}
				else if (it.find("<property") != std::string::npos && isProperty)
				{
					int a = it.find("name=") + 6;
					int b = it.find("value=") + 7;
					propertyS.push_back( it.substr(a, it.find("\"", a) - a) );
					propertyS.push_back( it.substr(b, it.find("\"", b) - b) );
				}
				else if (it.find("</properties>") != std::string::npos)
				{
					isProperty = false;
				}
				else if (it.find("</objectgroup>") != std::string::npos)
				{
					//コードを出力、プロパティ＆オブジェクト無しのパターンはコードを出力しない
					File classFile((className + ".h").c_str(),FileMode::Write);

					for (auto &it : templateS)
					{
						if (it.find("GUI_NAME") != std::string::npos)
						{
							std::string buf = it;
							int num = buf.find("GUI_NAME");
							buf.erase(num, 8);
							buf.insert(num, className);
							classFile.AddLine(buf);
						}
						else if (it.find("@メンバー宣言") != std::string::npos)
						{
							classFile.AddLine(it);
							if (isImage)
							{
								classFile.AddLine({ "\t\tint gID;" });
							}
							classFile.AddLine({ "\t\tRect rect;" });
							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								classFile.AddLine({ "\t\t", propertyS[a+1], " ", propertyS[a], ";" });
							}
						}
						else if(it.find("@コンストラクタ") != std::string::npos)
						{
							std::string str = "\t\t";
							str += className + "(const char* name,const Rect& rect";
							if (isImage)
							{
								str += ",int gID";
							}
							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								str += ",";
								if (propertyS[a + 1] == "std::string")
								{
									str += "const char* " + propertyS[a];
								}
								else
								{
									str += propertyS[a + 1] + " " + propertyS[a];							
								}
							}
							str += "):";

							classFile.AddLine(it);
							classFile.AddLine( str );
							classFile.AddLine({ "\t\t\tIGUI(name)," });
							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								classFile.AddLine({ "\t\t\t", propertyS[a], "(", propertyS[a], ")," });
							}
							if (isImage)
							{
								str += "\t\t\tgID(gID),";
							}
							classFile.AddLine({ "\t\t\trect(rect) " });
							classFile.AddLine({ "\t\t","{}" });
						}
						else if(it.find("@DefineCode") != std::string::npos)
						{
							std::string str = "\t\t\t";
							str += R"[]( 書込先.AddLine({ "\t\t\t)[]";
							str += className;
							str += R"[]( " , name , "={\"" , name ,"\",{", rect.GetX() ,",", rect.GetY() ,",", rect.GetW() ,",", rect.GetH() ,"}" )[]";
							if (isImage)
							{
								str += R"[]( ,",", gID )[]";
							}

							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								if (propertyS[a + 1].find("std::string") != std::string::npos)
								{
									//,",\"",変数名,"\"",
									str += R"[]( ,",\"", )[]";
									str += propertyS[a];
									str += R"[]( ,"\"" )[]";
								}
								else
								{
									//,",",変数名
									str += R"[]( ,",", )[]";
									str += propertyS[a];
								}
							}
							str += R"[]( ,"};"}); )[]";
							classFile.AddLine(str);
						}
						else
						{
							classFile.AddLine(it);
						}
					}

					std::string strr = "\t\t\tdata.dataS.push_back(std::make_shared<";
					strr += className + ">(name,rect";
					if (isImage){ strr += ",gid"; }

					for (unsigned int a = 0; a < propertyS.size(); a += 2)
					{
						if (propertyS[a + 1] == "std::string")
						{
							strr += ",properties[" + std::to_string(a/2) + "].c_str()";
						}
						else
						{
							strr += ",std::atoi(properties[" + std::to_string(a/2) + "].c_str())";	
						}
					}
					strr += "));";
					factoryS.push_back(className);
					factoryS.push_back(strr);

					propertyS.clear();
					classFile.Close();
				}
				++index;
			}

			File factoryFile("GUI_Factory.h", FileMode::Write);
			factoryFile.AddLine("#pragma once");
			factoryFile.AddLine("#include <GUI/GUIData.h>");
			factoryFile.AddLine("#include <vector>");
			factoryFile.AddLine("#include <string>");
			factoryFile.AddLine("");
			for (unsigned int a = 0; a < factoryS.size(); a += 2)
			{
				factoryFile.AddLine({ "#include \"", factoryS[a], ".h\"" });
			}
			factoryFile.AddLine("");
			factoryFile.AddLine("namespace SDX");
			factoryFile.AddLine("{");
			factoryFile.AddLine("\tvoid GUI_Factory(GUIData& data, std::string& layerName, const char* name, const char* type, int gid, Rect rect, double r, std::vector<std::string>& properties)");
			factoryFile.AddLine("\t{");
			for (unsigned int a = 0; a < factoryS.size(); a += 2)
			{
				if (a == 0)
				{
					factoryFile.AddLine({ "\t\tif(layerName == \"", factoryS[a], "\")" });
				}
				else
				{
					factoryFile.AddLine({ "\t\telse if(layerName == \"", factoryS[a], "\")" });
				}
				factoryFile.AddLine({ "\t\t{" });
				factoryFile.AddLine(factoryS[a+1]);
				factoryFile.AddLine({ "\t\t}" });
			}

			factoryFile.AddLine("\t}");
			factoryFile.AddLine("}");
		}

}