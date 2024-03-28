#include "main.h"
#include "manager.h"
#include "scene.h"
#include "weapon.h"
#include "sprite.h"
#include "score.h"
#include "audio.h"
#include "guage.h"

void Weapon::Init(int Player)
{
	m_Player = Player;

	if (m_Player == 0)
	{
		Scene* scene = Manager::GetInstance()->GetScene();

		if (m_TextureName)
		{
			AddComponent<Sprite>()->Init(SCREEN_WIDTH - 200.0f, SCREEN_HEIGHT - 150.0f, 200.0f, 70.0f, m_TextureName);
		}
		for (int i = 0; i < 2; i++)
		{
			m_BulletCount[i] = scene->AddGameObject<Score>(3);

			m_BulletCount[i]->Init(SCREEN_WIDTH - 30.0f - (i * 80.0f), SCREEN_HEIGHT - 80.0f, 20, 20, 20, 100);

			m_BulletCount[i]->SetScore(m_BulletMax);
		}

		if (!m_Guage)
		{
			m_Guage = scene->AddGameObject<Guage>(3);
			m_Guage->Init(SCREEN_WIDTH - 205.0f, SCREEN_HEIGHT -55.0f, 200.0f, 30.0f);
			m_Guage->SetBaseColor(D3DXCOLOR(0.2f, 0.7f, 0.2f, 0.6f));
			m_Guage->SetDraw(false);
		}
	}


	if (m_SoundName)
	{
		m_AttackSound = AddComponent<Audio>();
		m_AttackSound->Load(m_SoundName);
	}

	m_ReloadSound = AddComponent<Audio>();
	m_ReloadSound->Load((char*)"asset\\audio\\reload.wav");

	GameObject::Init();
}

void Weapon::Update()
{
	if (m_Player == 0 && m_Main)
	{
		m_Guage->SetGuage(D3DXVECTOR3(m_NowReloadTime, m_ReloadTime, m_NowReloadTime));
		m_BulletCount[1]->SetScore(m_BulletNum);
		if (m_IsReload)
		{
			m_Guage->SetDraw(true);
			m_NowReloadTime++;

			if (m_NowReloadTime >= m_ReloadTime)
			{
				m_NowReloadTime = 0;
				m_BulletNum = m_BulletMax;
				m_IsReload = false;
				m_Guage->SetDraw(false);
				m_BulletCount[1]->SetScore(m_BulletNum);
			}
		}
	}
	
}

void Weapon::Draw()
{
	if (m_Player == 0 && m_Main)
	{
		GameObject::Draw();
	}
}

void Weapon::Attack(D3DXVECTOR3 Position, D3DXVECTOR3 Direction)
{
	if (m_IsReload == true)
	{
		return;
	}


	WeaponAttack(Position, Direction);

	if (m_Player == 0)
	{

		if (m_BulletMax != -1)
		{
			m_BulletNum--;
		}

		if (m_BulletNum <= 0)
		{
			Reload();
		}
	}
}

void Weapon::Reload()
{
	if (m_BulletNum == m_BulletMax)
		return;

	if (m_BulletMax != -1 && m_IsReload == false)
	{
		m_ReloadSound->Play();
		m_BulletNum = 0;
		m_IsReload = true;
	}
}

void Weapon::SetMain(bool IsMain)
{
	
	m_Main = IsMain;

	for (int i = 0; i < 2; i++)
	{
		m_BulletCount[i]->SetDraw(IsMain);

		if (m_IsReload && IsMain)
		{
			m_Guage->SetDraw(true);
		}
		else
		{
			m_Guage->SetDraw(false);
		}
	}
	
}

