﻿//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <SDXFrameWork.h>

namespace SDX
{
	class CLASSNAME : public IScene
	{
	public:
		//@Define
		//@End

		CLASSNAME()
		{
			LoadGUI();
			Init();
		}

		//初期化
		void Init() override
		{
			//@Init
			//@End
		}

		//終了時
		void Final() override
		{
			//@Final
			//@End
		}

		//更新
		void Update() override
		{
			//@Update
			//@End
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (!Input::key.Return.on){ LoadGUI(); }
#endif
			//@Draw
			//@End
		}

		void LoadGUI() override
		{
#ifndef _DEBUG			
			return;
#endif
			//@Load
			//@End
		}
	};
}