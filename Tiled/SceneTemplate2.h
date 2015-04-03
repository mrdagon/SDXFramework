//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace SDX
{
	class CLASSNAME : public IScene
	{
	public:
		GUIData guiS;

		CLASSNAME()
		{
			guiS = TMXtoGUI("template.tmx", "CLASSNAME", GUI_Factory);
			Init();
		}

		//初期化
		void Init() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Init();
			}
		}

		//終了時
		void Final() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Final();
			}
		}

		//更新
		void Update() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Update();
			}
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			for (auto &it : guiS.dataS)
			{
				it->Draw();
			}
		}

		void LoadGUI() override
		{
#ifndef _DEBUG			
			return;
#endif
			guiS = TMXtoGUI("template.tmx", "CLASSNAME", GUI_Factory);
		}
	};
}