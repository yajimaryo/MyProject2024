#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyDrone.h"
#include "droneStateMove.h"
#include "droneStateAttack.h"

DroneStateMove::DroneStateMove(EnemyDrone * pDrone,int Index)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 dir;
	dir = player->GetPosition() - pDrone->GetPosition();
	D3DXVec3Normalize(&dir, &dir);

	dir.x + rand() % 20 - 10;
	dir.y = rand() % 20 - 10;
	dir.z + rand() % 20 - 10;

	D3DXVec3Normalize(&dir, &dir);
	
	m_Direction = dir;

	m_Index = Index;

	m_Frame = rand() % 100 + 100;
}

void DroneStateMove::Update(EnemyDrone * pDrone)
{
	D3DXVECTOR3 vel;
	vel = m_Direction * 0.02f;
	vel.y *= 0.1f;

	pDrone->AddVelocity(vel);

	if (m_Frame >= 250)
	{
		if (m_Index == 0)
			pDrone->ChangeDronePattern(new DroneStateMove(pDrone, 1));

		if (m_Index == 1)
			pDrone->ChangeDronePattern(new DroneStateAttack(pDrone));
	}

	m_Frame++;
}
