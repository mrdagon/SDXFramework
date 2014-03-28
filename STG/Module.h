#pragma once
#include <memory>
#include <functional>

namespace DXFW
{
///	<summary>Exeモジュールのインターフェース</summary>
///	\include
class IModule
{
	public:
		virtual void Update() = 0;
};

///	<summary>ラムダ式で実行条件を追加可能なモジュール</summary>
///	\include
class PartTimeModule : public IModule
{
	private:
		std::list< std::shared_ptr<IModule> > modules;
		std::function<bool()> judge;
	public:
		PartTimeModule(IModule *module , std::function<bool()> judge) :
			judge(judge)
		{
			this->Add( module );
		}

		void Update()
		{
			if( !judge() ) return;
				
			for( auto &it : modules )
			{
				it->Update();
			}
		};

		void Add( IModule *module )
		{
			this->modules.push_back( std::shared_ptr<IModule>(module) );
		}
};

///	<summary>関数オブジェクトをモジュール化するクラス</summary>
///	\include
class FuncModule : public IModule
{
	private:
		std::function<void()> func;
	public:
		FuncModule( std::function<void()> func):
			func(func)
		{}

		void Update()
		{
			func();
		}
};

}