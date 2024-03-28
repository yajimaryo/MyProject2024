#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyDrone.h"
#include "droneStateAttack.h"
#include "droneStateMove.h"

DroneStateAttack::DroneStateAttack(EnemyDrone * pDrone)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 pVec = player->GetPosition() - pDrone->GetPosition();

	m_AttackDir = pVec;
	D3DXVec3Normalize(&m_AttackDir, &m_AttackDir);

	float rot = atan2f(pVec.x, pVec.z);

	pDrone->SetRotation(D3DXVECTOR3(pDrone->GetRotation().x, rot, pDrone->GetRotation().z));

	m_Frame = 0;
}

void DroneStateAttack::Update(EnemyDrone * pDrone)
{
	pDrone->SetVelocity(pDrone->GetVelocity() * 0.9f);

	if (m_Frame == 10)
		pDrone->Attack(m_AttackDir);

	if (m_Frame > 30)
		pDrone->ChangeDronePattern(new DroneStateMove(pDrone, 0));

	m_Frame++;
}
