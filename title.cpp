
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "preparation.h"
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
#include "particle.h"

void Title::Init()
{
	m_CursorPosition[0] = D3DXVECTOR2(SCREEN_WIDTH / 2 - 200.0f, 520.0f);
	m_CursorPosition[1] = D3DXVECTOR2(SCREEN_WIDTH / 2 - 200.0f, 600.0f);

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

	{
		m_Polygon = AddGameObject<Polygon2D>(2);
		m_Polygon->AddComponent<AnimSprite>()->Init(m_CursorPosition[0].x, m_CursorPosition[0].y, 70.0f, 70.0f, (char*)"asset/texture/bullet001.png", 1, 1);
	}

	{
		AddGameObject<BackGround>(2);
	}

	m_Fade = AddGameObject<Fade>(2);

	m_SelectSE = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_SelectSE->Load("asset/audio/select.wav");

	m_OkSE = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	m_OkSE->Load("asset/audio/ok.wav");

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/title.wav");
	bgm->Play(true,0.2f);
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger('W') || Input::GetKeyTrigger('S'))
	{
		if (m_Cursor == 0)
		{
			m_Cursor = 1;
		}
		else if (m_Cursor == 1)
		{
			m_Cursor = 0;
		}
		m_Polygon->GetComponent<AnimSprite>()->SetPosition(m_CursorPosition[m_Cursor]);
		m_SelectSE->Play(false,0.3f);
	}

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_Fade->FadeOut();
		m_OkSE->Play();
	}

	if (m_Fade->GetFadeFinish())
	{
		if (m_Cursor == 0)
		{
			Manager::GetInstance()->SetScene<Preparation>();
		}
		else if (m_Cursor == 1)
		{
			Manager::GetInstance()->GameEnd();
		}
	}
}
