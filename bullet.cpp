
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "enemyManager.h"
#include "model.h"
#include "cylinder.h"
#include "box.h"
#include "player.h"
#include <vector>
#include <list>
#include "resource.h"
#include "plate.h"
#include "meshField.h"
#include "collision.h"
#include "effect.h"
#include "camera.h"


void Bullet::Init(D3DXVECTOR3 Position)
{
	m_Scale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.2f);
	m_Position = Position;
	
	m_Plate = AddComponent<Plate>();
	m_Plate->Init(m_Position, m_Scale, m_Rotation, (char*)"asset/texture/bullet001.png", true);

	m_Damage = 10.0f;
}

void Bullet::Uninit()
{
	GameObject::Uninit();
}

void Bullet::Update()
{
	m_Position += m_Velocity * m_Speed;

	//’e‚ðÁ‚·—\–ñ‚ð‚·‚é
	if (m_Position.z > 110.0f || m_Position.z < -110.0f ||
		m_Position.x > 110.0f || m_Position.x < -110.0f)
	{
		SetDestroy();
		return;
	}

	//“G‚Æ‚ÌÕ“Ë”»’è
	Scene* scene = Manager::GetInstance()->GetScene();

	if (m_Number == 0 || m_Number == 2)
	{
		std::list<Enemy*> enemies = scene->GetGameObject<EnemyManager>()->GetEnemies();
		for (Enemy* enemy : enemies)
		{
			D3DXVECTOR3 enemyPos = enemy->GetPosition() + enemy->GetCollisionOffset();
			D3DXVECTOR3 direction = enemyPos - m_Position;

			float length = D3DXVec3LengthSq(&direction);

			if (length < enemy->GetCollisionSize())
			{
				if (m_IsExplosion)
				{
					SummonExplosion();
				}
				else 
				{
					enemy->TakeDamage(m_Damage, m_Position);
				}
				
				SetDestroy();

				return;
			}
		}
	}
	else if (m_Number == 1 || m_Number == 2)
	{
		Player* player = scene->GetGameObject<Player>();
		
		D3DXVECTOR3 playerPos = player->GetPosition();
		D3DXVECTOR3 direction = playerPos - m_Position;

		float length = D3DXVec3LengthSq(&direction);

		if (length < 2.0f)
		{
			player->TakeDamage(m_Damage);
			SetDestroy();

			if (m_IsExplosion)
				SummonExplosion();

			return;
		}
		
	}

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 pos = cylinder->GetPosition();
		D3DXVECTOR3 scl = cylinder->GetScale();

		D3DXVECTOR3 dir = m_Position - pos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < scl.x + m_Scale.x)
		{
			if (m_Position.y < pos.y + scl.y - 0.5f)
			{
				SetDestroy();

				if (m_IsExplosion)
					SummonExplosion();

				return;
			}
			break;
		}
	}

	//box‚Æ‚Ì“–‚½‚è”»’è
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();
	for (Box* box : boxes)
	{
		D3DXVECTOR3 pos = box->GetPosition();
		D3DXVECTOR3 scl = box->GetScale();

		if (m_Position.x + m_Scale.x > pos.x - scl.x/* - 0.5f*/ && m_Position.x - m_Scale.x < pos.x + scl.x/* + 0.5f*/ &&
			m_Position.z + m_Scale.z > pos.z - scl.z/* - 0.5f*/ && m_Position.z - m_Scale.z < pos.z + scl.z/* + 0.5f*/)
		{
			if (m_Position.y < pos.y + (scl.y * 2 - 0.2f))
			{
				SetDestroy();

				if (m_IsExplosion)
					SummonExplosion();

				return;
			}
			break;
		}
	}

	if (m_Position.y < scene->GetGameObject<MeshField>()->GetHeight(m_Position))
	{
		SetDestroy();

		if(m_IsExplosion)
			SummonExplosion();

		return;
	}

	if (m_IsExplosion)
	{
		if (m_EffectCount == 5)
		{
			Effect* effect = scene->AddGameObject<Effect>(1);
			effect->Init(m_Position + D3DXVECTOR3(0.0f, -0.5f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 15);

			effect->SetMove(0.1f, D3DXVECTOR3(0.0f, 1.0f, 0.0f));

			m_EffectCount = 0;
		}

		m_EffectCount++;
	}

	m_Plate->SetPosition(m_Position);
	GameObject::Update();
}


void Bullet::Draw()
{
	GameObject::Draw();
}

void Bullet::SummonExplosion()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	scene->AddGameObject<Collision>(1)->Init(
		m_Position, D3DXVECTOR3(7.0f, 7.0f, 7.0f), 1, m_Damage, 3);


	{
		Effect* effect = scene->AddGameObject<Effect>(1);
		effect->Init(m_Position + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(6.0f, 6.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 20);

		effect->SetMove(0.4f, D3DXVECTOR3(-0.3f, 0.2f, -0.4f));
	}
	{
		Effect* effect = scene->AddGameObject<Effect>(1);
		effect->Init(m_Position + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(4.0f, 4.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 20);

		effect->SetMove(0.4f, D3DXVECTOR3(0.4f, 0.3f, -0.6f));
	}
	{
		Effect* effect = scene->AddGameObject<Effect>(1);
		effect->Init(m_Position + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(8.0f, 8.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 20);

		effect->SetMove(0.1f, D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	}
	{
		Effect* effect = scene->AddGameObject<Effect>(1);
		effect->Init(m_Position + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(6.0f, 6.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 20);

		effect->SetMove(0.4f, D3DXVECTOR3(0.3f, 0.2f, 0.4f));
	}
	{
		Effect* effect = scene->AddGameObject<Effect>(1);
		effect->Init(m_Position + D3DXVECTOR3(0.0f, -5.0f, 0.0f), D3DXVECTOR3(4.0f, 4.0f, 4.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR2(7.0f, 1.0f), (char*)"asset/texture/explosion002.png", true, 20);

		effect->SetMove(0.4f, D3DXVECTOR3(-0.4f, 0.3f, 0.6f));
	}

	camera->Shake(0.5f);
}
