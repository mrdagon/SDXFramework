//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
	/*! 各ボタンとキーを表すクラス.*/
	/*!    \include InputSample.h*/
	class Key
	{
	public:
		bool on = false;//押した瞬間
		bool off = false;//離した瞬間
		bool hold = false;//押されている
		unsigned int  holdCount = 0;//押されている時間

		/*! キーのリセット.*/
		void Reset()
		{
			on = false;
			off = false;
			hold = false;
			holdCount = 0;
		}

		/*! 押下状態の更新.*/
		void Update(int 押下フラグ)
		{
			if (!hold && 押下フラグ)    on = true;
			else                        on = false;
			if (hold && !押下フラグ)    off = true;
			else                        off = false;

			if (押下フラグ){
				hold = true;
				holdCount++;
			}
			else{
				hold = false;
				holdCount = 0;
			}
		}
	};
}