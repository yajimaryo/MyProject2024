#include "main.h"
#include "manager.h"
#include "scene.h"
#include "effect.h"
#include "sword.h"
#include "collision.h"
#include "audio.h"

void Sword::WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Effect* effect = scene->AddGameObject<Effect>(1);
	effect->Init(
		Position + Direction * 2.0f + D3DXVECTOR3(0.0f, 0.8f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR2(5.0f, 1.0f), "asset/texture/slash001.png", true, 5);
	effect->SetSpeed(0.8f);

	scene->AddGameObject<Collision>(1)->Init(
		Position + Direction * 5.0f + D3DXVECTOR3(0.0f, 0.8f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f), 5, m_Damage,m_Player);

	m_AttackSound->Play();
}
