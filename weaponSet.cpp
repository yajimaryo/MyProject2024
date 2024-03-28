#include "main.h"
#include "input.h"
#include "weaponSet.h"
#include "sprite.h"
#include "player.h"
#include "audio.h"

void WeaponSet::Init()
{
	m_CursorPos[0] = 350.0f;
	m_CursorPos[1] = 450.0f;
	m_CursorPos[2] = 550.0f;

	for (int i = 0; i < 6; i++)
	{
		m_WeaponView[i] = AddComponent<Sprite>();
	}
	
	m_WeaponView[0]->Init(300.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/assault.png");
	m_WeaponView[1]->Init(300.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/shotgun.png");
	m_WeaponView[2]->Init(300.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/launcher.png");

	m_WeaponView[3]->Init(700.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/assault.png");
	m_WeaponView[4]->Init(700.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/shotgun.png");
	m_WeaponView[5]->Init(700.0f, 100.0f, 200.0f, 70.0f, (char*)"asset/texture/launcher.png");

	for (int i = 0; i < 6; i++)
	{
		m_WeaponView[i]->SetDraw(false);
	}

	if (Player::GetMainWeapon() == 0)
	{
		m_WeaponView[0]->SetDraw(true);
	}
	else if (Player::GetMainWeapon() == 1)
	{
		m_WeaponView[1]->SetDraw(true);
	}
	else if (Player::GetMainWeapon() == 2)
	{
		m_WeaponView[2]->SetDraw(true);
	}

	if (Player::GetSubWeapon() == 0)
	{
		m_WeaponView[3]->SetDraw(true);
	}
	else if (Player::GetSubWeapon() == 1)
	{
		m_WeaponView[4]->SetDraw(true);
	}
	else if (Player::GetSubWeapon() == 2)
	{
		m_WeaponView[5]->SetDraw(true);
	}
	
	
	AddComponent<Sprite>()->Init(300.0f, 300.0f, 200.0f, 70.0f, (char*)"asset/texture/assault.png");
	AddComponent<Sprite>()->Init(300.0f, 400.0f, 200.0f, 70.0f, (char*)"asset/texture/shotgun.png");
	AddComponent<Sprite>()->Init(300.0f, 500.0f, 200.0f, 70.0f, (char*)"asset/texture/launcher.png");

	
	AddComponent<Sprite>()->Init(700.0f, 300.0f, 200.0f, 70.0f, (char*)"asset/texture/assault.png");
	AddComponent<Sprite>()->Init(700.0f, 400.0f, 200.0f, 70.0f, (char*)"asset/texture/shotgun.png");
	AddComponent<Sprite>()->Init(700.0f, 500.0f, 200.0f, 70.0f, (char*)"asset/texture/launcher.png");


	for (int i = 0; i < 2; i++)
	{
		m_Cursor[i] = AddComponent<Sprite>();
		m_Cursor[i]->Init(-50.0f, -50.0f, 50.0f, 50.0f, (char*)"asset/texture/bullet001.png");
	}
	m_Cursor[0]->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Cursor[0]->SetPosition(D3DXVECTOR2(250.0f, m_CursorPos[0]));
	m_Cursor[1]->SetPosition(D3DXVECTOR2(650.0f, m_CursorPos[0]));

	m_MainSub = 0;

	m_SelectSE = AddComponent<Audio>();
	m_SelectSE->Load("asset/audio/select.wav");

	m_OkSE = AddComponent<Audio>();
	m_OkSE->Load("asset/audio/ok.wav");
}

void WeaponSet::Update()
{
	if (m_Active)
	{
		if (Input::GetKeyTrigger('W'))
		{
			m_Select[m_MainSub]--;
			if (m_Select[m_MainSub] < 0)
				m_Select[m_MainSub] = 2;

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger('S'))
		{
			m_Select[m_MainSub]++;
			if (m_Select[m_MainSub] > 2)
				m_Select[m_MainSub] = 0;

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger('A') || Input::GetKeyTrigger('D'))
		{
			m_Cursor[m_MainSub]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

			if (m_MainSub == 0)
			{
				m_MainSub = 1;
			}
			else if (m_MainSub == 1)
			{
				m_MainSub = 0;
			}

			m_Cursor[m_MainSub]->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger(VK_SPACE))
		{
			Player::SetMainWeapon(m_Select[0]);
			Player::SetSubWeapon(m_Select[1]);
			m_Active = false;

			m_OkSE->Play();
		}

		m_Cursor[m_MainSub]->SetPosition(
			D3DXVECTOR2(m_Cursor[m_MainSub]->GetPosition().x, m_CursorPos[m_Select[m_MainSub]]));

		GameObject::Update();
	}

	for (int i = 0; i < 6; i++)
	{
		m_WeaponView[i]->SetDraw(false);
	}

	if (Player::GetMainWeapon() == 0)
	{
		m_WeaponView[0]->SetDraw(true);
	}
	else if (Player::GetMainWeapon() == 1)
	{
		m_WeaponView[1]->SetDraw(true);
	}
	else if (Player::GetMainWeapon() == 2)
	{
		m_WeaponView[2]->SetDraw(true);
	}

	if (Player::GetSubWeapon() == 0)
	{
		m_WeaponView[3]->SetDraw(true);
	}
	else if (Player::GetSubWeapon() == 1)
	{
		m_WeaponView[4]->SetDraw(true);
	}
	else if (Player::GetSubWeapon() == 2)
	{
		m_WeaponView[5]->SetDraw(true);
	}
}

void WeaponSet::Draw()
{
	if (m_Active)
		GameObject::Draw();

	for (int i = 0; i < 6; i++)
	{
		m_WeaponView[i]->Draw();
	}
}
