//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	/**tmx読み込み用、タグ名の後には=も付ける.*/
	std::string GetTag(std::string &元の文字 , std::string タグ名)
	{
		if (元の文字.find(タグ名) == std::string::npos)
		{
			return "0";
		}

		int a = 元の文字.find(タグ名) + タグ名.size()+1;
		return 元の文字.substr( a , 元の文字.find("\"" , a) - a );
	}
}