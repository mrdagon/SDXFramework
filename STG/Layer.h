#pragma once

#include <STG/Object.h>

namespace SDX
{
///	<summary>Objectのコンテナクラス</summary>
///	\include
template <class TObject>
class Layer
{
public:
	std::vector<std::shared_ptr<TObject>> objects;
	std::vector<std::shared_ptr<TObject>> suspend;

	void Add(TObject *object , int suspend = 0)
	{
		object->SetTimer(-suspend);

		if( object->GetTimer() >= 0 )
		{
			this->objects.push_back( std::shared_ptr<TObject>(object) );
		}else{
			this->suspend.push_back( std::shared_ptr<TObject>(object) );
		}
	}

	void Update( )
	{
		auto it = suspend.begin();

		while( it != suspend.end() )
		{
			(*it)->SetTimer( (*it)->GetTimer() + 1 );
			if( (*it)->GetTimer() >= 0 )
			{
				objects.push_back( (*it) );
				it = suspend.erase( it );
				continue;
			}
			++it;
		}

		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i]->Update();
		}
	}

	void Draw()
	{
		for( auto it : objects )
		{
			it->Draw();
		}
	}

	void DrawShadow(double X座標ずれ , double Y座標ずれ )
	{
		for( auto it : objects )
		{
			it->DrawShadow( X座標ずれ , Y座標ずれ);
		}
	}

	void ExeRemove(Rect* area)
	{
		for (unsigned int i = 0; i < objects.size(); i++)
		{
			objects[i]->RemoveCheck(area);
		}

		auto it = objects.begin();
		while( it != objects.end() )
		{
			if( (*it)->GetRemoveFlag() )
			{
				it = objects.erase( it );					
			}else{
				++it;
			}
		}
	}

	void Clear()
	{
		objects.clear();
		suspend.clear();
	}

	int GetCount()
	{
		return (int)objects.size();
	}

	Object* GetNearest(Object* object)
	{
		double nearest = -1;
		Object* nearObject = nullptr;

		for( auto it : objects )
		{
			double dist = object->GetDistance( it.get() );
			if( dist < nearest || nearest == -1)
			{
				nearest = dist;
				nearObject = it.get();
			}
		}

		return nearObject;
	}

	void Hit( Layer<TObject> &layer )
	{
		for (unsigned int i = 0; i < objects.size(); ++i)
		{
			for (unsigned int j = 0; j < layer.objects.size(); ++j)
			{
				if (layer.objects[j]->GetRemoveFlag()) continue;

				if (objects[i]->Hit( layer.objects[j].get() ))
				{
					objects[i]->Attack(layer.objects[j].get());
					layer.objects[j]->Attack(objects[i].get());
				}
			}

		}
	}
			
	void Hit( Object* objcet )
	{
		for (unsigned int i = 0; i < objects.size(); ++i)
		{
			if( objects[i]->GetRemoveFlag() ) continue;

			if (objects[i]->Hit(objcet))
			{
				objects[i]->Attack(objcet);
				objcet->Attack(objects[i].get());
			}
		}
	}

	TObject* operator[](int index)
	{
		return objects[index].get();
	}

};
}