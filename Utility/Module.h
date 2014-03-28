#pragma once
#include <memory>
#include <functional>

namespace SDX
{
/** Exeモジュールのインターフェース.*/
/**    \include*/
class IModule
{
    public:
        virtual void Update() = 0;
};

/** ラムダ式で実行条件を追加可能なモジュール.*/
/**    \include*/
class PartTimeModule : public IModule
{
    private:
        std::list< std::shared_ptr<IModule> > modules;
        std::function<bool()> judge;
    public:
        PartTimeModule(IModule *実行するModule , std::function<bool()> 実行する条件式) :
            judge(実行する条件式)
        {
            this->Add( 実行するModule);
        }

        void Update()
        {
            if( !judge() ) return;
                
            for( auto &it : modules )
            {
                it->Update();
            }
        };

        void Add( IModule *追加するModule )
        {
            this->modules.push_back(std::shared_ptr<IModule>(追加するModule));
        }
};

/** 関数オブジェクトをモジュール化するクラス.*/
/**    \include*/
class FuncModule : public IModule
{
    private:
        std::function<void()> func;
    public:
        FuncModule( std::function<void()> 関数オブジェクト):
            func(関数オブジェクト)
        {}

        void Update()
        {
            func();
        }
};

}