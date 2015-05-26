//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

namespace SDX
{
	template< class TSuper, int MaxSize >
	/*静的にメモリを確保する動的型.*/
	/*共通スーパークラスと最大型サイズをテンプレートに入れる*/
	/*Holderとか実装してない分、メモリ効率は良い*/
	/*Any同士の代入とかが無理*/
	class Any
	{
	private:
		char buff[MaxSize];
		TSuper* pSuper;

	public:
		template < typename T >
		Any(const T& src) :
			pSuper(new(buff) T(src))
		{
		}

		~Any()
		{
			pSuper->~TSuper();
		}

		Any& operator = (Any const & src)
		{
			if (this != & src)
			{
				//これで行ける？
				for (int a = 0;a < MaxSize;++a)
				{
					buff[a] = src.buff[a];
				}
			}
			return *this;
		}

		template < typename T >
		Any& operator = (const T& src)
		{
			pSuper = new(buff) T(rhs);
			return *this;
		}

		TSuper* Get(void)
		{
			return pSuper;
		}
	};

	template< class TSuper , int MaxSize >
	/*静的にメモリを確保する動的型.*/
	/*共通スーパークラスと最大型サイズをテンプレートに入れる*/
	/*Holderとかの分も考えて、MaxSizeを指定する必要がありメモリ効率が下がる*/
	/*コピー等が可能*/
	class ClonableAny
	{
	private:
		char buff[MaxSize];

		class IHolder
		{
		public:
			virtual ~IHolder() {}
			virtual IHolder * clone(char* buff) = 0;
			virtual TSuper* Get(void) = 0;
		};

		IHolder* content;

		template < typename T >
		class Holder : public IHolder
		{
		public:

			explicit Holder(T const & src) : 
				held(src)
			{}


			explicit Holder(T const && src) :
				held(src)
			{}

			virtual IHolder *clone( char* buff )
			{
				return new(buff) Holder(held);
			}

			TSuper* Get()
			{
				return &held;
			}

		private:
			T held;
		};
		
	public:
		template < typename T >
		ClonableAny(T const & src) :
			content(new(buff) Holder<T>(src))
		{ }

		ClonableAny(ClonableAny const & other) :
			content(other.content ? other.content->clone(buff) : 0)
		{ }

		~ClonableAny()
		{
			content->~IHolder();
		}

		ClonableAny& operator = (ClonableAny const & src)
		{
			if (this != &src)
			{
				content = src.content->clone(buff);
			}
			return *this;
		}

		template < typename T >
		ClonableAny& operator = ( T const & src)
		{
			content = new(buff) Holder<T>(src);
			return *this;
		}

		TSuper* Get(void)
		{
			content->Get();
		}

	};
}