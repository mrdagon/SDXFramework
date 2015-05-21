//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

namespace SDX
{
/**汎用メモリプール(非推奨).*/
/**プログラムの勉強に書いた適当なコード*/
class Pool
{
	//メモリプール
	static const int BS = 65536;//バッファサイズ//2のn乗にする
	int index[7] = { BS,BS,BS,BS,BS,BS,BS };
	std::vector<std::array<int, BS>> poolS[7];

	//空き状況
	std::vector<int> emptyS[7];
public:
	Pool()
	{
	}

	template< class T>
	T* Get(const T data)
	{
		int size = 0;
		int buff = 1;

		if (sizeof(T) <= 4) { size = 0; buff = 1; }
		else if (sizeof(T) <= 8) { size = 1;; buff = 2; }
		else if (sizeof(T) <= 16) { size = 2; buff = 4; }
		else if (sizeof(T) <= 32) { size = 3; buff = 8; }
		else if (sizeof(T) <= 64) { size = 4; buff = 16; }
		else if (sizeof(T) <= 128) { size = 5; buff = 32; }
		else if (sizeof(T) <= 256) { size = 6; buff = 64; }
		else
		{
			//普通にnewする
		}

		//大きさ+1して最後尾を返す
		if (emptyS[size].size() == 0)
		{
			index[size] += buff;
			if (index[size] >= BS)
			{
				poolS[size].push_back({});
				index[size] = 0;
			}

			return new(&poolS[size][poolS[size].size() - 1][index[size]]) T(data);
		}
		else
		{
			//空きがある場合
			int n = emptyS[size].back();
			emptyS[size].pop_back();
			return new(&poolS[size][n / BS][n % BS]) T(data);
		}
	}

	template< class T>
	void Destroy(T* pt)
	{
		int size = 0;
		int buff = 1;

		if (sizeof(T) <= 4) { size = 0; buff = 1; }
		else if (sizeof(T) <= 8) { size = 1;; buff = 2; }
		else if (sizeof(T) <= 16) { size = 2; buff = 4; }
		else if (sizeof(T) <= 32) { size = 3; buff = 8; }
		else if (sizeof(T) <= 64) { size = 4; buff = 16; }
		else if (sizeof(T) <= 128) { size = 5; buff = 32; }
		else if (sizeof(T) <= 256) { size = 6; buff = 64; }
		else
		{
			//普通にnewする
		}

		int n = -1;
		int a = 0;

		while( (unsigned int)a < poolS[size].size())
		{
			n = ((int*)pt - &poolS[size][a][0]);//0なら先頭要素削除
			if ( n >= 0 && n < BS)
			{
				n += a * BS;
				emptyS[size].push_back(n);
				return;
			}
			++a;
		}
	}

};

}