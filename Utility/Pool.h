#pragma once
#include <vector>
#include <new>

namespace SDX
{
/** メモリプールを表すクラス[未実装].*/
/**    \include PoolSample.h*/
template <int Size> class Pool
{
private:
    int index = -1;

    char* data;//確保している領域
    const int elemetsNumber = 4096;//要素数

    Pool* itr;//サイズが大きくなったら次プールに繋ぐ
    Pool* next;//サイズが大きくなったら次プールに繋ぐ

    Pool()
    {
        itr = this;
        next = nullptr;
        data = new char[elemetsNumber * Size];
        for (int i = Size-1; i < elemetsNumber; i+=Size)
        {
            data[a] = 0;
        }
    }

public:
    inline static Pool& Single()
    {
        static Pool pool;
        return pool;
    }

    inline void* Allocate()
    {
        while (1)
        {
            index++;
            if (index >= elemetsNumber) index = 0;

            //使用フラグをチェック
            if (data[index*Size + Size - 1] == 0)
            {
                data[index*Size + Size - 1] = 1;
                break;
            }
        }

        return &data[index*Size];
    }

    inline void DeAllocate( void* p)
    {
        char* pt = static_cast<char*>(p);
        pt[Size - 1] = 0;
    }
};

/** 自作メモリアロケータ.*/
/**    \include PoolSample.h*/
template <class T> class Allocater
{
public:
    const int size = sizeof(T);

    inline static void* operator new( size_t size )
    {
        return Pool<sizeof(T)+1>::Single().Allocate();
    }

    inline static void operator delete(void* p)
    {
        Pool<sizeof(T)+1>::Single().DeAllocate(p);
    }
};

}