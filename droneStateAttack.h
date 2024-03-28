#pragma once

#include "droneState.h"

class DroneStateAttack : public DroneState
{
private:
	D3DXVECTOR3 m_AttackDir;
	int m_Frame;
public:
	explicit DroneStateAttack(EnemyDrone* pDrone);
	virtual ~DroneStateAttack() {}
	virtual void Update(EnemyDrone* pDrone) override;

private:
	DroneStateAttack() {}
};