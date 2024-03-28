#pragma once

#include "gameObject.h"
#include <list>
#include <typeinfo>
#include <vector>

class Fade;
class EnemyManager;

class Scene
{
private:
	
protected:

	std::list<GameObject*> m_GameObject[4];
	
	Fade* m_Fade = nullptr;

	EnemyManager* m_EnemyManager = nullptr;
	int m_SpawnNumber = 0;
public:
	virtual void Init(void){}

	virtual void Uninit(void)
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				(object)->Uninit();
				delete (object);
			}
			m_GameObject[i].clear();
		}
	}

	virtual void Update(void)
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				(object)->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object) {
				return object->Destroy();
			});
		}
	}

	virtual void Draw(void);

	template <typename T>
	T* AddGameObject(int Layer)
	{
		GameObject* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();
		return (T*)gameObject;
	}

	template <typename T>
	T* GetGameObject()
	{
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//Œ^‚ð’²‚×‚éiRTTI“®“IŒ^î•ñj
				{
					return (T*)object;
				}
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetGameObjects()
	{
		std::vector<T*> objects;
		for (int i = 0; i < 4; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				if (typeid(*object) == typeid(T))//Œ^‚ð’²‚×‚éiRTTI“®“IŒ^î•ñj
				{
					objects.push_back((T*)object);
				}
			}
		}
		return objects;
	}

	virtual void SpawnEnemy(void) {};
};