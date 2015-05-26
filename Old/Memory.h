//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#define ONLY_MSPACES (1)
#define MALLOC_ALIGNMENT (8) // 最低８

// ソース自体をインクルード  
#include "malloc.c"
#include <cstdio>
#undef max
#undef min
#undef DrawText

namespace SDX
{
	/** メモリアロケータ.*/
	/** [参考にしました]http://pokotsun.mydns.jp/?p=1220.*/
	/** @todo サンプル作成*/
	class Memory
	{
	private:
		mspace  m_mspace;
		size_t m_heapSize;
	public:

		Memory()
		{
			const int HEAP_SIZE = 64*1024*1024;

			m_mspace = create_mspace(HEAP_SIZE, 0);
			m_heapSize = HEAP_SIZE;
		}

		Memory(size_t 確保領域)
		{
			m_mspace = create_mspace(確保領域, 0);
			m_heapSize = 確保領域;
		}

		~Memory()
		{
			destroy_mspace(m_mspace);
		}

		void* Allocate(size_t size)
		{
			return mspace_malloc(m_mspace, size);
		}

		void* Allocate(size_t size, int alignment)
		{
			return mspace_memalign(m_mspace, alignment, size);
		}

		void Deallocate(void* p) {
			mspace_free(m_mspace, p);
		}

	};

	namespace MEMORY
	{
		Memory memory;
	}
}

static void* operator new(size_t size)
{
	return SDX::MEMORY::memory.Allocate(size);
}

static void* operator new[](size_t size)
{
	return SDX::MEMORY::memory.Allocate(size);
}

static void* operator new(size_t size, int alignment)
{
	return SDX::MEMORY::memory.Allocate(size, alignment);
}

static void operator delete(void* p)
{
	SDX::MEMORY::memory.Deallocate(p);
}

static void operator delete[](void* p)
{
	SDX::MEMORY::memory.Deallocate(p);
}
