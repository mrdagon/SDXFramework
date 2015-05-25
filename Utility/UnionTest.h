//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

//コンテナ比較用のコードあれこれ
namespace SDX
{
	class IUnion
	{
	public:
		virtual ~IUnion(){}
	};

	class Int :public IUnion
	{
		int num;
	};

	class Double :public IUnion
	{
		double num;
	};

	class Float :public IUnion
	{
	public:
		float num;

		~Float()
		{
			static int b = 0;
			if (b == 1000)
			{
				SDX::Window::SetTitle("OK");
			}
			++b;
		}
	};

	/**共用体サンプル.*/
	/**メモリプール使う方が基本的に楽*/
	class SampleUnion
	{
#define U_TYPE(name) mutable name uni_##name; Union(const name &shot , Type& type ) : uni_##name(shot) { type = Type::name; }
#define U_DEST(name) case Type::name : uni.uni_##name.~name();break;
#define U_CONST(name) case Type::name : new(&uni.uni_##name) name(src.uni.uni_##name);break;
#define U_GET(name) case Type::name: return &uni.uni_##name;
	public:
		//列挙子名 = 型名にする
		enum class Type
		{
			Int,Double,Float
		} typeNo;

		union Union
		{
		public:
			U_TYPE(Int)
			U_TYPE(Double)
			U_TYPE(Float)

			Union() {}
			~Union() {};
		}uni;

		void Destoract()
		{
			switch (typeNo)
			{
				U_DEST(Int)
				U_DEST(Double)
				U_DEST(Float)
			default:break;
			}
		}

		void Constract(const SampleUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
				U_CONST(Int)
				U_CONST(Double)
			default:break;
			}
		}

		IUnion* Get() const
		{
			switch (typeNo)
			{
				U_GET(Int)
				U_GET(Double)
			}
			return nullptr;
		}

		//以下はunionの型数によらない
		template< class T>
		SampleUnion(const T &src) : uni(src, typeNo) {}

		SampleUnion(const SampleUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合も再構成する
		SampleUnion& operator=(const SampleUnion& src)
		{
			Destoract();
			Constract(src);
			return *this;
		}
		~SampleUnion() { Destoract(); }
#undef U_TYPE
#undef U_DEST
#undef U_CONST
#undef U_GET
	};

	/**共用体サンプルその2.*/
	/**メモリプール使う方が効率は良い*/
	template<class TInterface,class T0, class T1>
	class TempUnion
	{
	public:
		enum class Type
		{
			T0,
			T1
		} typeNo;

		union Union
		{
		public:
			mutable T0 value_0; Union(const T0 &t0, Type& type) : value_0(t0){ type = Type::T0; }
			mutable T1 value_1; Union(const T1 &t1, Type& type) : value_1(t1){ type = Type::T1; }
			Union() {}
			~Union() {};
		}uni;


		void Constract(const TempUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
			case Type::T0: new(&uni.value_0) T0(src.uni.value_0); break;
			case Type::T1: new(&uni.value_1) T1(src.uni.value_1); break;
			default:break;
			}
		}

		void Destoract()
		{
			switch (typeNo)
			{
			case Type::T0: uni.value_0.~T0(); break;
			case Type::T1: uni.value_1.~T1(); break;
			default:break;
			}
		}


		TInterface* Get() const
		{
			switch (typeNo)
			{
				case Type::T0: return &uni.value_0;
				case Type::T1: return &uni.value_1;
			}
			return nullptr;
		}

		//以下はunionの型数によらない
		template< class T>
		TempUnion(const T &src) : uni(src, typeNo) {}

		TempUnion(const TempUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合はコピー、それ以外は再確保
		TempUnion& operator=(const TempUnion& src)
		{
			if (typeNo == src.typeNo )
			{
				switch (typeNo) {
				case Type::T0:
					uni.value_0 = src.uni.value_0;
					break;
				case Type::T1:
					uni.value_1 = src.uni.value_1;
					break;
				default:
					break;
				}
				return *this;
			}

			Destoract();
			Constract(src);
			return *this;
		}
		~TempUnion() { Destoract(); }
	};


	/**共用体サンプルその3.*/
	/**なんか中途半端*/
	template<class TInterface, class T0, class T1>
	class AnyUnion
	{
	public:
		enum class Type
		{
			T0,
			T1
		} typeNo;

		TInterface* ptr;

		char buff[100];//placement new用の領域

		void Constract(const AnyUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
			case Type::T0: ptr = new(buff) T0(src.uni.value_0); break;
			case Type::T1: ptr = new(buff) T1(src.uni.value_1); break;
			default:break;
			}
		}

		void Destoract()
		{
			switch (typeNo)
			{
			case Type::T0: (T0)buff->~T0(); break;
			case Type::T1: (T1)buff->~T1(); break;
			default:break;
			}
		}

		TInterface* Get() const
		{
			return ptr;
		}

		//以下はunionの型数によらない
		template< class T>
		AnyUnion(const T &src , Type type)
		{
			typeNo = type;
			ptr = new(buff) T(src); break;
		}

		AnyUnion(const TempUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合も再確保
		AnyUnion& operator=(const AnyUnion& src)
		{
			Destoract();
			Constract(src);
			return *this;
		}
		~AnyUnion() { Destoract(); }
	};

	template< class TSuper , int MaxSize >
	/*静的な何でも入る型.*/
	/*共通スーパークラスと最大型サイズをテンプレートに入れる*/
	/*Holderとかの分、メモリ効率は下がる*/
	class Any
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

		template < typename T >
		class Holder : public IHolder
		{
		public:
			explicit Holder(T const & src)
				: held(src)
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
		Any(T const & src)
			: content(new(buff) Holder<T>(src))
		{
		}

		Any(Any const & other)
			: content(other.content ? other.content->clone(buff) : 0)
		{ }

		Any& operator = (Any const & rhs)
		{
			if (this != &rhs)
			{
				content = rhs.content->clone(buff);
			}
			return *this;
		}

		template < typename T >
		Any& operator = ( T const & rhs)
		{
			content = new(buff) holder<T>(rhs);
			return *this;
		}


		template < typename T >
		Any& operator = (T const && rhs)
		{
			content = new(buff) Holder<T>(rhs);
			return *this;
		}

		TSuper* Get(void)
		{
			content->Get();
		}

	private:
		IHolder* content;
	};
}