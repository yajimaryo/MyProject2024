
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "enemyMove.h"
#include "player.h"
#include "gun.h"
#include "resource.h"
#include "model.h"

void EnemyMove::Init()
{
	Enemy::Init();
	m_Velocity = m_MovePosition - m_Position;
	D3DXVec3Normalize(&m_Velocity,&m_Velocity);

	m_Hp = 20.0f;
	m_Score = 80;

	m_Attack = false;
	m_AttackFrame = 30;
	m_AttackTime = 0;

	m_ModelName = (char*)"asset\\model\\player01.obj";
}

void EnemyMove::Uninit()
{

	Enemy::Uninit();
}

void EnemyMove::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (!m_Weapon)
	{
		m_Weapon = scene->AddGameObject<Gun>(3);
		m_Weapon->Init(1);
	}

	m_OldPosition = m_Position;

	if ((m_AttackTime <= 0 && PlayerDist() <= 50.0f) || m_Attack)
	{
		if (PlayerDist() >= 10.0f && !m_Attack)
		{
			m_Attack = true;
			m_AttackFrame = 40;
		}

		if (m_AttackFrame <= 0)
		{
			if (m_AttackCountFrame <= 0)
			{
				D3DXVECTOR3 dir = player->GetPosition() - m_Position + D3DXVECTOR3(0.0f,-3.5f,0.0f);
				D3DXVec3Normalize(&dir, &dir);
				m_Weapon->Attack(m_Position + D3DXVECTOR3(0.0f, 3.5f, 0.0f), dir);
				m_AttackCount++;
				m_AttackCountFrame = 10;

				if (m_AttackCount >= 3)
				{
					m_AttackFrame = 30;
					m_Attack = false;
					m_AttackTime = 60;
					m_AttackCount = 0;
					m_AttackCountFrame = 0;

					m_MoveFrame = 0;
				}
			}
			m_AttackCountFrame--;
		}

		if (m_MoveFrame <= 0)
		{
			int x = rand() % 4 - 2;
			int z = rand() % 4 - 2;

			SetMovePosition(D3DXVECTOR3(player->GetPosition().x + x, 0.0f, player->GetPosition().z + z));
			m_Velocity.x *= -1;
			m_Velocity.z *= -1;

			m_MoveFrame = 60;
		}

		D3DXVECTOR3 dir = player->GetPosition() - m_Position;
		m_Rotation.y = atan2f(dir.x, dir.z);

		m_Position.y += m_Velocity.y;

		if (!m_Attack)
		{
			m_Position.x += m_Velocity.x * 0.2f;
			m_Position.z += m_Velocity.z * 0.2f;
		}

		if (m_Attack)
		{
			m_AttackFrame--;
		}
		else if (!m_Attack)
		{
			m_MoveFrame--;
		}
	}
	else if (PlayerDist() > 50.0f)
	{
		float vely = m_Velocity.y;
		SetMovePosition(D3DXVECTOR3(player->GetPosition().x, 0.0f, player->GetPosition().z));
		m_Velocity *= 0.1f;
		m_Velocity.y = vely;

		m_Position += m_Velocity;


		D3DXVECTOR3 dir = player->GetPosition() - m_Position;
		m_Rotation.y = atan2f(dir.x, dir.z);
	}
	else
	{
		m_AttackTime--;
	}

	Enemy::Update();
}

void EnemyMove::Draw()
{
	Enemy::Draw();

	ResourceManager::GetInstance()->GetResouseModel(m_ModelName)->Draw();
}