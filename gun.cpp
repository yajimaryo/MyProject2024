
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "bullet.h"
#include "gun.h"
#include "effect.h"
#include "audio.h"

void Gun::WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	Scene* scene = Manager::GetInstance()->GetScene();

	scene->AddGameObject<Effect>(1)->Init(
		Position + D3DXVECTOR3(0.0f, 0.8f, 0.0f), D3DXVECTOR3(0.1f, 0.1f, 0.1f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/hiteffect01.png", true, 1);

	Bullet* bullet = scene->AddGameObject<Bullet>(1);
	bullet->Init(Position + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	//bullet->SetPosition(Position + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	bullet->SetVelocity(Direction);
	bullet->SetSpeed(m_BulletSpd);
	bullet->SetNumber(m_Player);
	bullet->SetDamage(m_Damage);

	m_AttackSound->Play(false,0.1f);
}
