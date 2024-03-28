#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyMutant.h"
#include "mutantStateWalk.h"
#include "mutantStateIdle.h"
#include "mutantStateAttack.h"
#include "mutantStateSkill.h"

MutantStateWalk::MutantStateWalk(EnemyMutant * pMutant, float Speed)
{
	pMutant->ChangeAnimation("Walk");
}

void MutantStateWalk::Update(EnemyMutant * pMutant)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 dir = player->GetPosition() - pMutant->GetPosition();
	D3DXVec3Normalize(&dir, &dir);
	pMutant->SetRotation(D3DXVECTOR3(pMutant->GetRotation().x, atan2f(dir.x, dir.z), pMutant->GetRotation().z));
	pMutant->SetVelocity(D3DXVECTOR3(dir.x * 0.25f, pMutant->GetVelocity().y, dir.z * 0.25f));
	
	if (pMutant->PlayerDist() < 10.0f)
	{
		if (pMutant->GetSkillCT() <= 0)
		{
			pMutant->ChangeMutantPattern(new MutantStateSkill(pMutant));
		}
		else
		{
			pMutant->ChangeMutantPattern(new MutantStateAttack(pMutant));
		}
	}
}
