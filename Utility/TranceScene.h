//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/File.h>
#include <Utility/GUIData.h>
#include <vector>

namespace SDX
{
	namespace TranceCode
	{
		/** GUIDataからSceneのコードを生成する.*/
		/** @todo とりあえず自分専用の試作*/
		/** \include TranceCode.h*/
		void GUItoScene(const char* クラス名 ,const std::vector<GUIData> &GUIデータ )
		{
			std::string str = クラス名;
			str += "Scene.h";
			File file( str.c_str() , FileMode::Write);

			//生成するコード全体
			/*
			#pragma once
			#include "IScene.h"
			
			namespace SDX_TD
			{
				using namespace SDX;
			
				class クラス名 : public IScene
				{			
				public:
					//GUIを定義していく

					//初期化
					void Init() override
					{

					}
					//終了時
					void Final() override
					{

					}
					//更新
					void Update() override
					{
						//ボタン系のクラスはここに押下判定を入れる
					}
					//描画
					void Draw() override
					{
						//各種描画処理を行なう
					}

					//GUIデータの更新
					void LoadGUI()
					{
					static bool isUpdate = true;

						if(Input::key.Return.on){isUpdata = true;}
						if( !isUpdate ) { return; }
					}
				};
			}
			*/

			//ヘッダ部分
			/*
			#pragma once
			#include "IScene.h"

			namespace SDX_TD
			{
			using namespace SDX;

			class クラス名 : public IScene
			{
			public:
			*/
			file.AddLine("#pragma once");
			file.AddLine("#include <SDXFramework.h>");
			file.AddLine("");
			file.AddLine("namespace SDX_TD");
			file.AddLine("{");
			file.AddLine("using namespace SDX;");
			file.AddLine("");
			file.AddLine({"class " , クラス名 , "Scene : public IScene"});
			file.AddLine("{");
			file.AddLine("public:");

			//変数の宣言部
			for (auto & it : GUIデータ)
			{
				if (it.lineX > 1 || it.lineY > 1)
				{
					file.AddLine({ "GUIData ", it.name, "[", it.lineX * it.lineY, "];" });
				} 
				else
				{
					file.AddLine({ "GUIData ", it.name, ";" });
				}
			}

			//InitとFinal
			/*
			//コンストラクタ
			クラス名()
			{
				LoadGUI();
				Init();
			}

			//初期化
			void Init() override
			{}

			//終了時
			void Final() override
			{}
			*/
			file.AddLine({ クラス名 , "Scene()" });
			file.AddLine("{");
			file.AddLine("LoadGUI();");
			file.AddLine("Init();");
			file.AddLine("}");
			file.AddLine("");
			file.AddLine("//初期化");
			file.AddLine("void Init() override");
			file.AddLine("{}");
			file.AddLine("");
			file.AddLine("//終了時");
			file.AddLine("void Final() override");
			file.AddLine("{}");
			file.AddLine("");


			//Update
			/*
			//更新
			void Update() override
			{
				//ボタン系のクラスはここに押下判定を入れる
			}
			*/
			file.AddLine("//更新");
			file.AddLine("void Update() override");
			file.AddLine("{");
			for (auto & it : GUIデータ)
			{
				switch (it.type)
				{
				case GUIType::Button://枠のみ
					if (it.lineX > 1 || it.lineY > 1)
					{
						file.AddLine({ "for(int a=0;a < ", it.lineX * it.lineY, ";++a){" });
						file.AddLine({ "if( ", it.tag, ".size.Hit(&pt) )" });
						file.AddLine({ "{" });
						file.AddLine({ "}" });
						file.AddLine({ "}" });
					}
					else
					{
						file.AddLine({ "if( ", it.tag, ".size.Hit(&pt) )" });
						file.AddLine({ "{" });
						file.AddLine({ "}" });		
					}
					break;
				default:
					break;
				}


			}
			file.AddLine("}");
			file.AddLine("");


			//Draw
			/*
			//描画
			void Draw() override
			{
				LoadGUI();
				//各種描画処理を行なう
			}
			*/
			file.AddLine("//描画");
			file.AddLine("void Draw() override");
			file.AddLine("{");
			file.AddLine("LoadGUI();");
			file.AddLine("");
			for (auto & it : GUIデータ)
			{
				if (it.lineX > 1 || it.lineY > 1)
				{
					file.AddLine({ "for(int a=0;a < ", it.lineX * it.lineY, ";++a){" });
					switch (it.type)
					{
					case GUIType::Button://枠の描画
						file.AddLine({ it.tag, "[a].Draw(", it.name, ".size);" });
						break;
					case GUIType::Label://文字の描画
						file.AddLine({ it.tag, "[a].Draw(", it.name, ".GetPoint(),Color::White,{\"", it.text, "\"});" });
						break;
					case GUIType::Picture://画像の描画
						file.AddLine({ it.tag, "[a].DrawRotate(", it.name, ".GetCenter() , 1 , 0 );" });
						break;
					default:
						break;
					}
					file.AddLine("}");
				}
				else
				{
					switch (it.type)
					{
					case GUIType::Button://枠の描画
						file.AddLine({ it.tag, ".Draw(", it.name, ".size);" });
						break;
					case GUIType::Label://文字の描画
						file.AddLine({ it.tag, ".Draw(", it.name, ".GetPoint(),Color::White,{\"", it.text, "\"});" });
						break;
					case GUIType::Picture://画像の描画
						file.AddLine({ it.tag, ".DrawRotate(", it.name, ".GetCenter() , 1 , 0 );" });
						break;
					default:
						break;
					}
				}
			}
			file.AddLine("}");

			//LoadGUI
			/*
			//GUIデータの更新
			void LoadGUI() override
			{
				static bool isUpdate = true;

				#ifdef _DEBUG
				if (Input::key.Return.on){ isUpdata = true; }
				#endif
				if (!isUpdate) { return; }

				#ifdef _DEBUG
				auto uiS = TranceCode::CLIForm("クラス名" + ".h");	
				#else
				auto uiS = TranceCode::CSVtoGUI("クラス名" + ".csv");	
				#endif
				
				nameA = uiS[0];
				nameB = uiS[1];
				nameC = uiS[2];
				...
				
				}
			}
			};
			}
			*/

			file.AddLine("void LoadGUI() override");
			file.AddLine("{");
			file.AddLine("static bool isUpdate = true;");
			file.AddLine("");
			file.AddLine("#ifdef _DEBUG");
			file.AddLine("if (Input::key.Return.on){ isUpdate = true; }");
			file.AddLine("#endif");
			file.AddLine("if (!isUpdate) { return; }");
			file.AddLine("");
			file.AddLine("#ifdef _DEBUG");
			file.AddLine("auto uiS = TranceCode::CLIForm( \"クラス名.h\");");
			file.AddLine("#else");
			file.AddLine("auto uiS = TranceCode::CSVtoGUI( \"クラス名.csv\");");
			file.AddLine("#endif");
			file.AddLine("");
			int index = 0;
			for (auto & it : GUIデータ)
			{
				if (it.lineX > 1 || it.lineY > 1)
				{
					file.AddLine({ "for(int a=0;a < ", it.lineX * it.lineY, ";++a){" });
					file.AddLine({ it.name, "[a] = uiS[", index, "];" });
					file.AddLine({ it.name, "[a].size.x += uiS[",index,"].size.widthRight * (a%" , it.lineX , ");" });
					file.AddLine({ it.name, "[a].size.y += uiS[",index,"].size.heightDown * (a/" , it.lineX , ");" });
					file.AddLine("}");
				}
				else
				{
					file.AddLine({ it.name, " = uiS[", index, "];" });
				}
				++index;
			}
			file.AddLine("");
			file.AddLine("}");
			file.AddLine("};");
			file.AddLine("}");

		}
	}

}