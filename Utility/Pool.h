#pragma once
#include <vector>

namespace SDX
{
/** メモリプールを表すクラス[未実装].*/
/**    \include PoolSample.h*/
class Pool
{
private:
    std::vector<char> byte1;
    std::vector<char> byte2;
    std::vector<char> byte4;
    std::vector<char> byte8;
    std::vector<char> byte16;
    std::vector<char> byte32;
    std::vector<char> byte64;
    std::vector<char> byte128;

    Pool& Single()
    {
        static Pool pool;
        return pool;
    }

public:
    static void* Allocate( size_t size)
    {

    }
            
    static void* DeAllocate( void* p)
    {

    }
};

/** 自作メモリアロケータ.*/
/**    \include PoolSample.h*/
class Allocater
{
public:
    void* operator new( size_t size )
    {
        Pool::Allocate( size );
    }

    void operator delete( void* p )
    {
        Pool::DeAllocate( p );
    }
    void* operator new(size_t, void* p)
    {
        return p;
    }
    void operator delete(void*, void*)
    {
    }
};
}