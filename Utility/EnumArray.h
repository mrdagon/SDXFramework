﻿#pragma once//©SDXFramework http://sourceforge.jp/projects/dxframework/
#include <array>

namespace SDX
{
    /**列挙型を直接添字に使える配列.*/
    /**エラー処理など未実装*/
    template <class TData, class TType>
    class EnumArray
    {
    private:
        std::array<TData, (int)TType::COUNT> Array;
    public:
        size_t size() const
        {
            return Array.size();
        }

        TData& operator[](const TType index)
        {
            return Array[(int)index];
        }

        const TData& operator[](const TType index) const
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