#pragma once

#include <list>
#include "gameObject.h"
#include "enemy.h"

class EnemyManager : public GameObject
{
private:
	std::list<Enemy*> m_Enemies;
	int m_SpawnNumber = 0;
public:

	void Uninit() 
	{
		for (Enemy* pe : m_Enemies) {
			pe->Uninit();
			delete pe;
		}
		m_Enemies.clear();
	}

	void Update() 
	{
		for (Enemy* pe : m_Enemies) {
			pe->Update();
		}

		m_Enemies.remove_if([](Enemy* enemy) {
			return enemy->Destroy();
		});
	}

	void Draw()
	{
		for (Enemy* pe : m_Enemies) {
			pe->Draw();
		}
	}

	template <typename T>
	T* AddEnemy() {
		Enemy* enemy = new T();
		enemy->Init();
		m_Enemies.push_back(enemy);
		return (T*)enemy;
	}

	std::list<Enemy*> GetEnemies(){return m_Enemies;}

};
