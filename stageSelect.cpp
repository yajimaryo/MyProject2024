#include "main.h"
#include "manager.h"
#include "scene.h"
#include "preparation.h"
#include "input.h"
#include "stageSelect.h"
#include "sprite.h"
#include "player.h"
#include "audio.h"
#include "loading.h"

void StageSelect::Init()
{
	m_CursorPos[0] = 470.0f;
	m_CursorPos[1] = 570.0f;
	m_CursorPos[2] = 670.0f;

	m_Cursor = AddComponent<Sprite>();
	m_Cursor->Init(-50.0f, -50.0f, 50.0f, 50.0f, (char*)"asset/texture/bullet001.png");
	m_Cursor->SetScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	m_Cursor->SetPosition(D3DXVECTOR2(250.0f, m_CursorPos[0]));

	AddComponent<Sprite>()->Init(300.0f, 400.0f, 150.0f, 70.0f, (char*)"asset/texture/back.png");
	AddComponent<Sprite>()->Init(300.0f, 500.0f, 200.0f, 70.0f, (char*)"asset/texture/mission01.png");
	AddComponent<Sprite>()->Init(300.0f, 600.0f, 200.0f, 70.0f, (char*)"asset/texture/mission02.png");

	m_SelectSE = AddComponent<Audio>();
	m_SelectSE->Load("asset/audio/select.wav");

	m_OkSE = AddComponent<Audio>();
	m_OkSE->Load("asset/audio/ok.wav");
}

void StageSelect::Update()
{
	if (m_Active)
	{
		if (Input::GetKeyTrigger('W'))
		{
			m_Select--;
			if (m_Select < 0)
				m_Select = 2;

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger('S'))
		{
			m_Select++;
			if (m_Select > 2)
				m_Select = 0;

			m_SelectSE->Play();
		}

		if (Input::GetKeyTrigger(VK_SPACE))
		{
			m_OkSE->Play();
			if (m_Select == 0)
			{
				m_Active = false;
			}
			else if (m_Select == 1)
			{
				Loading::SetLoadStage(0);
				m_Start = true;
			}
			else
			{
				Loading::SetLoadStage(1);
				m_Start = true;
			}
		}

		m_Cursor->SetPosition(
			D3DXVECTOR2(250.0f, m_CursorPos[m_Select]));

		GameObject::Update();
	}

	
}

void StageSelect::Draw()
{
	if (m_Active)
		GameObject::Draw();
}
