#pragma once

#include "enemy.h"

class EnemyMove : public Enemy
{
private:
	int m_AttackCount = 0;
	int m_AttackCountFrame = 0;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};