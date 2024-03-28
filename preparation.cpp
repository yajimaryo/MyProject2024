#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "loading.h"
#include "tutorial.h"
#include "polygon2D.h"
#include "animSprite.h"
#include "fade.h"
#include "audio.h"
#include "backGround.h"
#include "loading.h"
#include "camera.h"
#include "sky.h"
#include "meshField.h"
#include "normalPlate.h"
#include "preparation.h"
#include "player.h"
#include "weaponSet.h"
#include "sprite.h"
#include "stageSelect.h"

void Preparation::Init()
{
	{
		Camera* camera = AddGameObject<Camera>(0);
		camera->SetPosition(D3DXVECTOR3(-45.0f, 1.0f, -42.5f));
	}

	AddGameObject<Sky>(1);

	MeshField* meshField = AddGameObject<MeshField>(1);
	meshField->Init(0,
		(char*)"asset/texture/ground004.png",
		(char*)"asset/texture/field007.jpg",
		(char*)"asset/texture/field006.jpg",
		(char*)"asset/texture/field003.jpg");

	{
		NormalPlate* lake = AddGameObject<NormalPlate>(1);
		lake->Init(D3DXVECTOR3(-100.0f, -0.7f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 1.0f), D3DXVECTOR3(D3DX_PI / 2, 0.0f, 0.0f),
			(char*)"asset/texture/blue.png", (char*)"asset/texture/waveNormal02.jpg", false);
	}

	m_CursorPosition[0] = D3DXVECTOR2(0.0f, 100.0f);
	m_CursorPosition[1] = D3DXVECTOR2(0.0f, 200.0f);
	m_CursorPosition[2] = D3DXVECTOR2(0.0f, 300.0f);

	{
		m_Polygon = AddGameObject<Polygon2D>(2);
		m_Polygon->AddComponent<AnimSprite>()->Init(m_CursorPosition[0].x, m_CursorPosition[0].y, 50.0f, 50.0f, (char*)"asset/texture/bullet001.png", 1, 1);
	}

	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(1000.0f, 650.0f, 250.0f, 70.0f, (char*)"asset/texture/decision.png");

	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(50.0f, 200.0f, 150.0f, 50.0f, (char*)"asset/texture/weaponSelect.png");
	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(50.0f, 100.0f, 150.0f, 50.0f, (char*)"asset/texture/missionSelect.png");
	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(50.0f, 300.0f, 100.0f, 50.0f, (char*)"asset/texture/back.png");

	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(300.0f, 200.0f, 200.0f, 70.0f, (char*)"asset/texture/main.png");
	AddGameObject<GameObject>(2)->AddComponent<Sprite>()->Init(700.0f, 200.0f, 200.0f, 70.0f, (char*)"asset/texture/sub.png");

	m_Fade = AddGameObject<Fade>(2);

	m_WS = AddGameObject<WeaponSet>(2);
	m_WS->SetActive(false);

	m_StageSelect = AddGameObject<StageSelect>(2);
	m_StageSelect->SetActive(false);

	m_SelectSE = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_SelectSE->Load("asset/audio/select.wav");

	m_OkSE = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_OkSE->Load("asset/audio/ok.wav");

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/title.wav");
	bgm->Play(true, 0.2f);
}

void Preparation::Update()
{
	Scene::Update();

	if (m_Select == false)
	{

		if (Input::GetKeyTrigger('S'))
		{
			m_Cursor++;

			if (m_Cursor == 3)
			{
				m_Cursor = 0;
			}

			m_Polygon->GetComponent<AnimSprite>()->SetPosition(m_CursorPosition[m_Cursor]);
			m_SelectSE->Play(false, 0.3f);
		}

		if (Input::GetKeyTrigger('W'))
		{
			m_Cursor--;

			if (m_Cursor == -1)
			{
				m_Cursor = 2;
			}

			m_Polygon->GetComponent<AnimSprite>()->SetPosition(m_CursorPosition[m_Cursor]);
			m_SelectSE->Play(false, 0.3f);
		}

		if (Input::GetKeyTrigger(VK_SPACE))
		{
			if (m_Cursor == 0)
			{ 
				m_Select = true;
				m_StageSelect->SetActive(true);
			}

			if (m_Cursor == 1)
			{
				m_Select = true;
				m_WS->SetActive(true);
			}

			if (m_Cursor == 2)
			{
				Manager::GetInstance()->SetScene<Title>();
			}

			m_OkSE->Play();
		}
	}
	else
	{
		m_Select = m_WS->GetActive();

		if (!m_Select)
			m_Select = m_StageSelect->GetActive();
	}

	m_Start = m_StageSelect->Start();

	if (m_Start)
	{
		m_Fade->FadeOut();
	}

	if (m_Fade->GetFadeFinish())
	{
		Manager::GetInstance()->SetScene<Loading>();
	}
}

