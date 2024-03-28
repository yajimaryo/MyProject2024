#pragma once

#include "enemy.h"

class DroneState;

class EnemyDrone : public Enemy
{
private:
	DroneState* m_DronePattern = nullptr;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ChangeDronePattern(DroneState* DronePattern);
	
	void Attack(D3DXVECTOR3 Direction);
};