//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

namespace SDX
{
	class IUnion
	{
	public:
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
		float num;
	};


#define U_TYPE(name) mutable name uni_##name; Union(const name &shot , Type& type ) : uni_##name(shot) { type = Type::name; }
#define U_DEST(name) case Type::name : uni.uni_##name.~name();break;
#define U_CONST(name) case Type::name : new(&uni.uni_##name) name(src.uni.uni_##name);break;
#define U_GET(name) case Type::name: return &uni.uni_##name;

	/**共用体サンプル.*/
	/**メモリプール使う方が基本的に楽*/
	class SampleUnion
	{
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
	};

	/**共用体サンプルその2.*/
	/**メモリプール使う方が基本的に楽*/
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
			mutable T0 uni_T0; Union(const T0 &t0, Type& type) : uni_T0(t0){ type = Type::T0; }
			mutable T1 uni_T1; Union(const T1 &t1, Type& type) : uni_T1(t1){ type = Type::T1; }
			Union() {}
			~Union() {};
		}uni;

		void Destoract()
		{
			switch (typeNo)
			{
			case Type::T0: uni.uni_T0.~T0(); break;
			case Type::T1: uni.uni_T1.~T1(); break;
			default:break;
			}
		}

		void Constract(const TempUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
			case Type::T0: new(&uni.uni_T0) T0(src.uni.uni_T0); break;
			case Type::T1: new(&uni.uni_T1) T1(src.uni.uni_T1); break;
			default:break;
			}
		}

		TInterface* Get() const
		{
			switch (typeNo)
			{
				case Type::T0: return &uni.uni_T0;
				case Type::T1: return &uni.uni_T1;
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
		//同じ型になる場合も再構成する
		TempUnion& operator=(const TempUnion& src)
		{
			Destoract();
			Constract(src);
			return *this;
		}
		~TempUnion() { Destoract(); }
	};

}