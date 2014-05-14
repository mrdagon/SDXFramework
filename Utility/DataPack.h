#pragma once//?Unicode

namespace SDX
{
    /**�񋓌^�𒼐ړY���Ɏg����z��.*/
    template <class TData, class TType>
    class DataPack
    {
    private:
        TData dataS[(int)TType::MAX];
    public:
        TData& operator[](TType index)
        {
            return dataS[(int)index];
        }

        TData& operator[](int index)
        {
            return dataS[index];
        }
    };
}