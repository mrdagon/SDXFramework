#pragma once//?Unicode
#include <array>

namespace SDX
{
    /**—ñ‹“Œ^‚ğ’¼Ú“Yš‚Ég‚¦‚é”z—ñ.*/
    template <class TData, class TType>
    class DataPack
    {
    private:
        std::array<TData, (int)TType::MAX> Array;
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

#ifdef __WINDOWS__
        std::_Array_iterator<TData, (int)TType::MAX> begin()
        {
            return Array.begin();
        }

        std::_Array_iterator<TData, (int)TType::MAX> end()
        {
            return Array.end();
        }

        std::_Array_const_iterator<TData, (int)TType::MAX> begin() const
        {
            return Array.begin();
        }

        std::_Array_const_iterator<TData, (int)TType::MAX> end() const
        {
            return Array.end();
        }
#else
        auto begin()
        {
            return Array.begin();
        }

        auto end()
        {
            return Array.end();
        }

        auto begin() const
        {
            return Array.begin();
        }

        auto end() const
        {
            return Array.end();
        }
#endif

    };
}