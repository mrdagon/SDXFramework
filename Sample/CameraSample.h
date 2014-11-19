//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//初期化を行い何かキーを押すと終了する[未実装]
bool SampleCamera()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	System::End();
	return    true;
}