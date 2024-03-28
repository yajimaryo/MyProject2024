#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyMutant.h"
#include "mutantStateAttack.h"
#include "mutantStateWalk.h"
#include "mutantStateIdle.h"
#include "collision.h"
#include "effect.h"

MutantStateAttack::MutantStateAttack(EnemyMutant * pMutant)
{
	pMutant->ChangeAnimation("Attack");

	pMutant->SetVelocity(D3DXVECTOR3(0.0f, pMutant->GetVelocity().y, 0.0f));

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 pVec = player->GetPosition() - pMutant->GetPosition();
	float rot = atan2f(pVec.x, pVec.z);

	pMutant->SetRotation(D3DXVECTOR3(pMutant->GetRotation().x, rot, pMutant->GetRotation().z));

	m_Frame = 0;
}

void MutantStateAttack::Update(EnemyMutant * pMutant)
{
	m_Frame++;

	if (m_Frame == m_AttackFrame)
	{
		Scene* scene = Manager::GetInstance()->GetScene();
		scene->AddGameObject<Collision>(1)->Init(
			pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(4.0f, 5.0f, 4.0f), 5, 10, 1);

		scene->AddGameObject<Effect>(1)->Init(pMutant->GetPosition() + pMutant->GetForward() * 10.0f + D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR3(1.0f, 5.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(5.0f, 1.0f), "asset/texture/slash001.png", true, 5);
	}


	if (m_Frame >= m_AttackTime)
		pMutant->ChangeMutantPattern(new MutantStateIdle(pMutant,60));

}
