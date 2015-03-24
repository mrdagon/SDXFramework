//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
#include <SDXFramework.h>

bool TranceCode()
{
	using namespace SDX;

	//System::Initialise等は不要
	//デバッグビルド時はコード生成+CSV作成
	//CLIFormからGUIDataを取得
	//"MyForm.h"ならMyFormと入力
	TranceCode::CLItoScene("MyForm");

	return true;
}