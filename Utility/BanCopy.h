#pragma once//☀Unicode

namespace SDX
{
    /**private継承でコピーを不可にする.*/
    /*boost::noncopyableと同等だが、命名規則を合わせるため実装*/
    class BanCopy
    {
    protected:
        BanCopy() = default;
        ~BanCopy() = default;

        BanCopy(const BanCopy&) = delete;
        BanCopy& operator=(const BanCopy&) = delete;
    };

}