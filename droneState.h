#pragma once

class EnemyDrone;

class DroneState
{
public:
	virtual ~DroneState() {}
	virtual void Update(EnemyDrone* pDrone) = 0;
};