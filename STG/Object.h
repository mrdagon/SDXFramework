#pragma once
#include <SDXFrameWork.h>
#include <Framework/ModelMove.h>

namespace SDX
{
/// <summary>所属するレイヤーの識別子</summary>
enum class Belong
{
	Ally,
	EnemyF,
	EnemyG,
	Item,
	Block,
	Etc
};

template <class T> class Layer;

/// <summary>ModelにSTG用の機能を追加したクラス</summary>
///	\include
class Object : public Model , public ModelMove
{
template<class T>
friend class Layer;
    
protected:
	int  timer = 0;///発生してから経過したフレーム数
	bool isOutCheck = true;///範囲外処理を行うかフラグ
	double  power;///攻撃力
	int  attribute;///攻撃属性
	int  lifeTime = -1;///生存期間
	Belong belong;///所属するレイヤー

	/// <summary>消滅判定を行う</summary>
	virtual bool RemoveCheck(Rect* 存在可能範囲)
	{
		if(
			timer == this->lifeTime ||
			(isOutCheck && 存在可能範囲 && !shape->Hit( 存在可能範囲 ) )
           )
		{
			this->isRemove = true;
		}

		if (isRemove) Remove();

		return this->isRemove;
	}

	void SetTimer(int フレーム数)
	{
		timer = フレーム数;
	}

public:
	//説明
	Object( Shape *当たり判定 , Sprite *デフォルトスプライト , double 攻撃力 = 0 , Belong 所属 = Belong::Etc):
		Model( 当たり判定 , デフォルトスプライト ),
		ModelMove(this),
		power(攻撃力),
		belong(所属)
	{}

	int GetTimer()
	{
		return timer;
	}

	virtual ~Object(){}

	/// <summary>状態の更新</summary>
	virtual void Update()
	{
		this->timer++;
		AnimeUpdate();
		this->Act();
	}


	Belong GetBelong()
	{
		return belong;
	}
    
    /// <summary>衝突した相手に攻撃する</summary>
	virtual void Attack(Object *攻撃対象 )
	{
		攻撃対象->Damaged( power );
	}

	/// <summary>Update時の行動処理</summary>
	virtual void Act(){}

	/// <summary>消滅時の処理</summary>
	virtual void Remove(){}

	///ダメージを受けた時の処理
	virtual void React(double ダメージ量){}

	/// <summary>攻撃された時の処理</summary>
	virtual void Damaged(double ダメージ量){}
    
    bool isSelect = false;
};
}