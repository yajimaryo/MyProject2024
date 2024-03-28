
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "bullet.h"
#include "launcher.h"
#include "audio.h"

void Launcher::WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Bullet* bullet = scene->AddGameObject<Bullet>(1);

	bullet->Init(Position + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
	bullet->SetVelocity(Direction);
	bullet->SetSpeed(m_BulletSpd);
	bullet->SetNumber(m_Player);
	bullet->SetDamage(m_Damage);
	bullet->SetExplosion();

	m_AttackSound->Play(false, 0.1f);
}
