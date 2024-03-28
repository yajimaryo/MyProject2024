#pragma once

#include "droneState.h"

class DroneStateMove : public DroneState
{
private:
	D3DXVECTOR3 m_Direction;
	int m_Frame;

	int m_Index;
public:
	explicit DroneStateMove(EnemyDrone* pDrone, int Index);
	virtual ~DroneStateMove() {}
	virtual void Update(EnemyDrone* pDrone) override;

private:
	DroneStateMove() {}
};