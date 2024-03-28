#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemyTuto.h"
#include "player.h"
#include "bullet.h"
#include "gun.h"

void EnemyTuto::Init()
{
	Enemy::Init();

	m_Rotation.y = D3DX_PI;

	m_Hp = 10.0f;
	m_AttackFrame = 60.0f;
	m_Score = 0;
}

void EnemyTuto::Uninit()
{
	Enemy::Uninit();
}

void EnemyTuto::Update()
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
		if (!m_Attack)
		{
			m_Attack = true;
			m_AttackFrame = 60;
		}

		if (m_AttackFrame <= 0)
		{
			m_Weapon->Attack(m_Position, GetForward());
			m_AttackFrame = 60;
			m_Attack = false;
			m_AttackTime = 100;
		}

		if (m_Attack)
		{
			m_AttackFrame--;
		}
	
	}
	else
	{
		m_AttackTime--;
	}

	Enemy::Update();
}

void EnemyTuto::Draw()
{
	Enemy::Draw();
}
