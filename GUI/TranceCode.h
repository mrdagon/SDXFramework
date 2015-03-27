//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include "TranceTMX.h"

namespace SDX
{
	namespace TranceCode
	{
		/**tmxファイルとテンプレートからコードを生成する*/
		void TMXtoCode( const char* className ,const char* tmxFile, const char* templateFile )
		{
			GUIData guiS = TMXtoGUI(tmxFile , GUI_Factory );//tmxファイルを変換するあれこれ

			std::string outputFile = className;
			outputFile += ".h";

			File file(templateFile, FileMode::Read);
			std::vector<std::string> strS = file.GetLineS();
			file.Close();

			File file2(outputFile.c_str(), FileMode::Write);

			bool isWrite = true;

			for (auto &it : strS)
			{
				if (it.find("CLASSNAME") != std::string::npos)
				{
					int num = it.find("CLASSNAME");
					it.erase(num, 9);
					it.insert(num, className);
					file2.AddLine(it);
				}
				else if (it.find("@Define") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					for (auto &it : guiS.dataS){ it->DefineCode(file2); }
				}
				else if (it.find("@Init") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					for (auto &it : guiS.dataS){ it->InitCode(file2); }
				}
				else if (it.find("@Final") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					for (auto &it : guiS.dataS){ it->FinalCode(file2); }
				}
				else if (it.find("@Update") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					for (auto &it : guiS.dataS){ it->UpdateCode(file2); }
				}
				else if (it.find("@Draw") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					for (auto &it : guiS.dataS){ it->DrawCode(file2); }
				}
				else if (it.find("@Load") != std::string::npos)
				{
					isWrite = false;
					file2.AddLine(it);
					int index = 0;
					file2.AddLine({ "\t\t\tGUIData guiData = TranceCode::TMXtoGUI(\"" ,tmxFile ,"\", TranceCode::GUI_Factory);", });
					file2.AddLine("");
					for (auto &it : guiS.dataS)
					{
						file2.AddLine({ "\t\t\t", it->name, " = *dynamic_cast<", typeid(*it).name(), "*>(guiData.dataS[", index, "].get());" });
						++index;
					}
				}
				else if (it.find("@End") != std::string::npos)
				{
					isWrite = true;
					file2.AddLine(it);
				}
				else if (isWrite)
				{
					file2.AddLine(it);
				}

				//これに囲まれた区間は無視する
				
			}
		}

		/**tmxファイルからGUIクラスのコードを生成する*/
		void TMXtoGUIClass(const char* tmxFileName , const char* templateFileName)
		{
			File file(tmxFileName,FileMode::Read);
			File templateFile(templateFileName, FileMode::Read);
			std::vector<std::string> strS = file.GetLineS();
			std::vector<std::string> templateS = templateFile.GetLineS();
			
			std::string className = "";
			std::vector<std::string> propertyS;
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
							classFile.AddLine({ "\t\tRect rect;" });
							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								classFile.AddLine({ "\t\t", propertyS[a+1], " ", propertyS[a], ";" });
							}

						}
						else if(it.find("@コンストラクタ") != std::string::npos)
						{
							std::string str = "\t\t";
							str += className + "(const char* name,Rect& rect";
							for (unsigned int a = 0; a < propertyS.size(); a += 2)
							{
								str += ",";
								if (propertyS[a + 1] == "std::string")
								{
									str += "const char* " + propertyS[a];
								}
								else
								{
									str += propertyS[a + 1] + "& " + propertyS[a];							
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
							classFile.AddLine({ "\t\t\t", "rect(rect) " });
							classFile.AddLine({ "\t\t","{}" });
						}
						else if(it.find("@DefineCode") != std::string::npos)
						{
							std::string str = "\t\t\t";
							str += R"[]( 書込先.AddLine({ "\t\t\t)[]";
							//書込先.AddLine({"\"", name, "\",","{"
							str += className;
							str += R"[]( " , name , "={\"" , name ,"\",{", rect.GetX() ,",", rect.GetY() ,",", rect.GetW() ,",", rect.GetH() ,"}" )[]";

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
					propertyS.clear();
					classFile.Close();
				}


				++index;
			}


		}
	}

}