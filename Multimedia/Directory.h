//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//Qiitaのこの記事を参考にしています[http://qiita.com/episteme/items/0e3c2ee8a8c03780f01e]
//Qiitaの利用規約9条2項、参照の事

#pragma once
#include <Multimedia/SDX.h>

#ifdef __WINDOWS__
#include <filesystem>
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

namespace SDX
{
	/** ディレクトリの作成、ディレクトリ内のファイルの列挙関数郡.*/
	/**@todo とりあえずWindow版のみ実装*/
	/** \include File.h*/
	class Directory
	{
	public:
		/**ディレクトリ内のファイル名/ディレクトリ名を取得する.*/
		static std::vector<std::string> GetFileName(const char* ディレクトリ名)
		{
			std::vector<std::string> nameS;

#ifdef __WINDOWS__
			namespace sys = std::tr2::sys;
			sys::path p(ディレクトリ名);
			
			//std::for_each(sys::directory_iterator(p),sys::directory_iterator(),
			std::for_each(sys::recursive_directory_iterator(p), sys::recursive_directory_iterator(),
				[&](const sys::path& p)
				{
				if (sys::is_regular_file(p))
				{ // ファイルなら...
					//VS2015はp.filename().string().c_str()にする
#ifdef VS_2015
					nameS.push_back(p.filename().string().c_str());
#else
					nameS.push_back(p.filename().c_str());
#endif
				}
				else if (sys::is_directory(p)) 
				{ // ディレクトリなら...
					nameS.push_back( p.string().c_str() );
				}
			});

#else
			DIR *dir = opendir(ディレクトリ名);
			struct dirent　 *dp;

			if( dir == nullptr ){return false;}

			for (dp = readdir(dir); dp != NULL; dp = readdir(dir))
			{
				nameS.push_back(dp->d_name);
			}
			closedir(dir);
#endif
			return nameS;
		}

		/**ディレクトリを作成する.*/
		static bool MakeDirectory(const char* ディレクトリ名)
		{
#ifdef __WINDOWS__
			return (_mkdir(ディレクトリ名) == 0);
#else
			return false;
#endif
		}
	};
}