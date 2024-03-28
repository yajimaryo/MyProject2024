#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyMutant.h"
#include "mutantStateAttack.h"
#include "mutantStateWalk.h"
#include "mutantStateIdle.h"
#include "mutantStateSkill.h"
#include "collision.h"
#include "effect.h"
#include "camera.h"

MutantStateSkill::MutantStateSkill(EnemyMutant * pMutant)
{
	pMutant->ChangeAnimation("Skill");

	pMutant->SetVelocity(D3DXVECTOR3(0.0f, pMutant->GetVelocity().y, 0.0f));

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 pVec = player->GetPosition() - pMutant->GetPosition();
	float rot = atan2f(pVec.x, pVec.z);

	pMutant->SetRotation(D3DXVECTOR3(pMutant->GetRotation().x, rot, pMutant->GetRotation().z));
	pMutant->SetSkillCT();

	m_Frame = 0;
}

void MutantStateSkill::Update(EnemyMutant * pMutant)
{
	m_Frame++;

	if (m_Frame == m_AttackFrame)
	{
		Scene* scene = Manager::GetInstance()->GetScene();
		Camera* camera = scene->GetGameObject<Camera>();

		scene->AddGameObject<Collision>(1)->Init(
			pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR3(12.0f, 12.0f, 12.0f), 5, 10, 1);


		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(6.0f, 6.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 7);

			effect->SetMove(0.4f, D3DXVECTOR3(-0.3f, 0.2f, -0.4f));
		}
		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(4.0f, 4.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 7);

			effect->SetMove(0.4f, D3DXVECTOR3(0.4f, 0.3f, -0.6f));
		}
		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(8.0f, 8.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 7);

			effect->SetMove(0.1f, D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		}
		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(6.0f, 6.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 7);

			effect->SetMove(0.4f, D3DXVECTOR3(0.3f, 0.2f, 0.4f));
		}
		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(pMutant->GetPosition() + pMutant->GetForward() * 8.0f + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(4.0f, 4.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 7);

			effect->SetMove(0.4f, D3DXVECTOR3(-0.4f, 0.3f, 0.6f));
		}

		camera->Shake(0.5f);
	}


	if (m_Frame >= m_AttackTime)
		pMutant->ChangeMutantPattern(new MutantStateIdle(pMutant,60));

}
