//©SDXFramework http://sourceforge.jp/projects/dxframework/
//[License] Affero General Public License ver 3
#pragma once
#include <Framework/IScene.h>
#include <Utility/Timer.h>
#include <Multimedia/Input.h>
#include <Framework/Camera.h>

namespace SDX
{
/** シーンを管理するクラス.*/
/**    \include DirectorSample.h*/
class Director
{
private:
    std::vector< std::shared_ptr<IScene> > scenes;

    Director(){};

    static Director& Single()
    {
        static Director instance; 
        return instance;
    }
public:
    /** 実行開始.*/
    static void Run()
    {
        Time::ResetFPS();

        while( System::Update() )
        {
            if( Single().scenes.size() == 0 ) break;
            Single().scenes.back()->Update();
            Single().scenes.back()->Draw();
            //更新処理
            if( Camera::Now() ) Camera::Now()->Update();
            Time::CheckFPS();

            Remove();
        }
    }

    /** 消滅したSceneを片付ける.*/
    static void Remove()
    {
        auto it = Single().scenes.begin();

        while( it != Single().scenes.end() )
        {
            if( (*it)->IsEnd() )
            {
                it = Single().scenes.erase(it);
                if(Single().scenes.size() == 0 )break;
                continue;
            }
            it++;
        }
    }

    /** Sceneを追加する.*/
    /** 追加したシーンがアクティブになる\n
        既に追加されているシーンの場合アクティブ化する*/
    static void AddScene( IScene* 追加するシーン )
    {
        //既に存在する場合移動のみ
        auto it = Single().scenes.begin();
        while( it != Single().scenes.end() )
        {
            if ((*it).get() == 追加するシーン)
            {
                Single().scenes.push_back( (*it) );
                return;
            }
            ++it;
        }
        //存在していない場合初期化して追加
        追加するシーン->Init();
        Single().scenes.emplace_back(追加するシーン);
    }

    /** 上からインデックス番目のシーンを取得.*/
    /** 0で現在アクティブなシーン*/
    static IScene* GetScene(int インデックス)
    {
        return Single().scenes[Single().scenes.size() - インデックス - 1].get();
    }
};
}









