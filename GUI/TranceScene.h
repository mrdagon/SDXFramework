//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <GUI/GUIData.h>

namespace SDX
{
	namespace TranceCode
	{
		/** GUIDataからSceneのコードを生成する.*/
		/** @todo とりあえず自分専用の試作*/
		/** \include TranceCode.h*/
		void GUItoScene(const char* クラス名 ,GUIData &GUIデータ )
		{
			std::string str = クラス名;
			str += "Scene.h";
			File file( str.c_str() , FileMode::Write);

			//utf-8bomを付ける
			char chr;
			file.Write( chr = (char)0xEF);
			file.Write( chr = (char)0xBB);
			file.Write( chr = (char)0xBF);

			file.AddLine("#pragma once");
			file.AddLine("#include <SDXFramework.h>");
			file.AddLine("");
			file.AddLine("namespace SDX_TD");
			file.AddLine("{");
			file.AddLine("	using namespace SDX;");
			file.AddLine("");
			file.AddLine({"	class " , クラス名 , "Scene : public IScene"});
			file.AddLine("	{");
			file.AddLine("	public:");
			GUIデータ.DefineCode(file);
			file.AddLine("");
			file.AddLine({"		", クラス名 , "Scene()" });
			file.AddLine("		{");
			file.AddLine("			LoadGUI();");
			file.AddLine("			Init();");
			file.AddLine("		}");
			file.AddLine("");
			file.AddLine("		//初期化");
			file.AddLine("		void Init() override");
			file.AddLine("		{");
			GUIデータ.InitCode(file);
			file.AddLine("		}");
			file.AddLine("");
			file.AddLine("		//終了時");
			file.AddLine("		void Final() override");
			file.AddLine("		{");
			GUIデータ.FinalCode(file);
			file.AddLine("		}");
			file.AddLine("");
			file.AddLine("		//更新");
			file.AddLine("		void Update() override");
			file.AddLine("		{");
			GUIデータ.DrawCode(file);
			file.AddLine("		}");
			file.AddLine("");
			file.AddLine("		//描画");
			file.AddLine("		void Draw() override");
			file.AddLine("		{");
			file.AddLine("			LoadGUI();");
			file.AddLine("");
			GUIデータ.DrawCode(file);
			file.AddLine("		}");

			//LoadGUI
			file.AddLine("		void LoadGUI() override");
			file.AddLine("		{");
			file.AddLine("			static bool isUpdate = true;");
			file.AddLine("");
			file.AddLine("#ifdef _DEBUG");
			file.AddLine("			if (Input::key.Return.on){ isUpdate = true; }");
			file.AddLine("#endif");
			file.AddLine("			if (!isUpdate) { return; }");
			file.AddLine("");
			file.AddLine({"			auto guiData = TranceCode::TMXtoGUI( \"",クラス名,".tmx\");" });
			file.AddLine("");
			GUIデータ.CopyCode(file);
			file.AddLine("");
			file.AddLine("		}");
			file.AddLine("	};");
			file.AddLine("}");

		}
	}

}