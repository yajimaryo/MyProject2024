
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "enemyAttack.h"
#include "bullet.h"
#include "player.h"
#include "sword.h"
#include "resource.h"
#include "model.h"

void EnemyAttack::Init()
{
	Enemy::Init();
	m_Hp = 30.0f;
	m_Score = 100;
	m_AttackFrame = 60;

	m_ModelName = (char*)"asset\\model\\enemy01.obj";
}

void EnemyAttack::Uninit()
{
	Enemy::Uninit();
}

void EnemyAttack::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (!m_Weapon)
	{
		m_Weapon = scene->AddGameObject<Sword>(3);
		m_Weapon->Init(1);
	}

	m_OldPosition = m_Position;

	if (m_Hit <= 0)
	{
		if (m_AttackTime <= 0 && PlayerDist() <= 100.0f)
		{
			if (PlayerDist() <= 3.5f && !m_Attack && m_MoveFrame <= 10)
			{
				m_Attack = true;
				m_AttackFrame = 45;

				D3DXVECTOR3 dir = player->GetPosition() - m_Position;
				m_Rotation.y = atan2f(dir.x, dir.z);
			}

			if (m_AttackFrame <= 0)
			{
				m_Weapon->Attack(m_Position + D3DXVECTOR3(0.0f, -2.0f, 0.0f), GetForward() * 1.0f);
				m_AttackFrame = 60;
				m_Attack = false;
				m_AttackTime = 100;

				m_MoveFrame = 0;
			}

			if (m_MoveFrame <= 0)
			{
				D3DXVECTOR3 dir = player->GetPosition() - m_Position;

				float rotrand = ((float)rand() / RAND_MAX * 20.0f - 10.0f);

				m_Rotation.y = atan2f(dir.x + rotrand, dir.z + rotrand);
				float vely = GetVelocity().y;
				m_Velocity = GetForward();
				m_Velocity.y = vely;

				m_MoveFrame = 120 + (int)(rand() / RAND_MAX) * 300;
			}



			m_Position.y += m_Velocity.y;

			if (!m_Attack)
			{
				m_Position.x += m_Velocity.x * 0.25f;
				m_Position.z += m_Velocity.z * 0.25f;
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
		else if (PlayerDist() > 100.0f)
		{
			float vely = m_Velocity.y;
			SetMovePosition(D3DXVECTOR3(player->GetPosition().x, 0.0f, player->GetPosition().z));
			m_Velocity *= 0.3f;
			m_Velocity.y = vely;

			m_Position += m_Velocity;


			D3DXVECTOR3 dir = player->GetPosition() - m_Position;
			m_Rotation.y = atan2f(dir.x, dir.z);
		}
		else
		{
			m_AttackTime--;
		}
	}

	Enemy::Update();
}

void EnemyAttack::Draw()
{
	Enemy::Draw();

	ResourceManager::GetInstance()->GetResouseModel(m_ModelName)->Draw();
}
