
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "bullet.h"
#include "shotGun.h"
#include "effect.h"
#include "audio.h"

void ShotGun::WeaponAttack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	Scene* scene = Manager::GetInstance()->GetScene();

	scene->AddGameObject<Effect>(1)->Init(
		Position + D3DXVECTOR3(0.0f, 0.8f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/hiteffect01.png", true, 1);

	float angleStep = 0.05f;
	//angleStep = ((float)rand() / RAND_MAX) * 0.1f;

	for (int i = -1; i <= 1; i++)
	{
		for (int n = -1; n <= 1; n++)
		{
			// …•½•ûŒü‚ÉŠp“x‚ð’²®
			float horizontalAngle = atan2f(Direction.z, Direction.x) + i * (D3DX_PI / 2.0f) * angleStep;
			// ‚’¼•ûŒü‚ÉŠp“x‚ð’²®
			float verticalAngle = asinf(Direction.y) + n * (D3DX_PI / 2.0f) * angleStep;


			// ’²®‚µ‚½Šp“x‚©‚ç•ûŒüƒxƒNƒgƒ‹‚ðÄŒvŽZ
			D3DXVECTOR3 newDirection(
				cosf(verticalAngle) * cosf(horizontalAngle),
				sinf(verticalAngle),
				cosf(verticalAngle) * sinf(horizontalAngle)
			);


			Bullet* bullet = scene->AddGameObject<Bullet>(1);

			bullet->Init(Position + D3DXVECTOR3(0.0f, 0.5f, 0.0f));
			bullet->SetVelocity(newDirection);
			bullet->SetSpeed(m_BulletSpd);
			bullet->SetNumber(m_Player);
			bullet->SetDamage(m_Damage);
		}
	}
	m_AttackSound->Play(false, 0.1f);
}
