#pragma once//?Unicode
#include <array>

namespace SDX
{
    /**�񋓌^�𒼐ړY���Ɏg����z��.*/
    template <class TData, class TType>
    class EnumArray
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