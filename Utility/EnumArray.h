//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <array>

namespace SDX
{
	/**列挙型を直接添字に使える配列.*/
	/** \include EnumArray.h */
	/**@todo エラー処理など未実装*/
	template <class TType, class TEnum>
	class EnumArray
	{
	private:
		std::array<TType, (int)TEnum::COUNT> Array;
	public:
		size_t size() const
		{
			return Array.size();
		}

		TType& operator[](const TEnum index)
		{
			return Array[(int)index];
		}

		const TType& operator[](const TEnum index) const
		{
			return Array[(int)index];
		}

		auto begin() ->decltype(Array.begin())
		{
			return Array.begin();
		}

		auto end() ->decltype(Array.end())
		{
			return Array.end();
		}

		auto begin() const ->decltype(Array.begin())
		{
			return Array.begin();
		}

		auto end() const ->decltype(Array.end())
		{
			return Array.end();
		}
	};
}