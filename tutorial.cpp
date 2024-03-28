
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "tutorial.h"
#include "game.h"
#include "polygon2D.h"
#include "sprite.h"
#include "fade.h"
#include "camera.h"
#include "sky.h"
#include "field.h"
#include "meshField.h"
#include "player.h"
#include "enemyManager.h"
#include "enemyTuto.h"
#include "enemyMove.h"
#include "enemyAttack.h"
#include "enemyDrone.h"
#include "message.h"
#include "box.h"
#include "audio.h"
#include "rock.h"
#include "animPlate.h"
#include "plate.h"
#include "enemyMutant.h"
#include "radar.h"
#include "normalPlate.h"
#include "preparation.h"
#include "gameClear.h"
#include "particle.h"

bool Tutorial::m_LoadFinish = false;

void Tutorial::Load()
{
	EnemyMutant::Load();
	Player::Load();
	m_LoadFinish = true;
}

void Tutorial::Unload()
{
	EnemyMutant::Unload();
	Player::Unload();
	m_LoadFinish = false;
}

void Tutorial::Init()
{
	srand(2);

	

	AddGameObject<Camera>(0);

	AddGameObject<Sky>(1);

	MeshField* meshField = AddGameObject<MeshField>(1);
	meshField->Init(0,
		(char*)"asset/texture/ground004.png",
		(char*)"asset/texture/field007.jpg",
		(char*)"asset/texture/field006.jpg",
		(char*)"asset/texture/field003.jpg");

	m_Player = AddGameObject<Player>(2);
	m_Player->SetPosition(D3DXVECTOR3(-45.0f, meshField->GetHeight(D3DXVECTOR3(-45.0f, 0.0f, -32.5f)), -32.5f));

	m_EnemyManager = AddGameObject<EnemyManager>(1);

	
	{
		for (int i = 0; i < 20; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = ((float)rand() / RAND_MAX * 200 - 100);
			pos.z = ((float)rand() / RAND_MAX * 200 - 100);
			pos.y = meshField->GetHeight(pos);
			
			if (pos.y < 0.0f)
				continue;

			GameObject* tree = AddGameObject<GameObject>(1);
			tree->AddComponent<Plate>()->Init(
				pos, D3DXVECTOR3(3.0f, 3.0f, 3.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				(char*)"asset/texture/tree001.png", true);
		}
	}

	{
		for (int i = 0; i < 300; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = ((float)rand() / RAND_MAX * 200 - 100);
			pos.z = ((float)rand() / RAND_MAX * 200 - 100);
			pos.y = meshField->GetHeight(pos) - 0.3f;

			if (pos.y < -0.3f)
				continue;

			for (int n = 0; n < 6; n++)
			{
				GameObject* grass = AddGameObject<GameObject>(1);
				grass->AddComponent<Plate>()->Init(
					pos, D3DXVECTOR3(2.0f, 1.0f, 2.0f), D3DXVECTOR3(0.0f, (D3DX_PI / 3) * n, 0.0f),
					(char*)"asset/texture/grass.png", false);
			}
		}
	}

	{
		NormalPlate* lake = AddGameObject<NormalPlate>(1);
		lake->Init(D3DXVECTOR3(-100.0f, -0.7f, -100.0f), D3DXVECTOR3(100.0f, 100.0f, 1.0f), D3DXVECTOR3(D3DX_PI/2, 0.0f, 0.0f),
			(char*)"asset/texture/blue.png", (char*)"asset/texture/waveNormal02.jpg", false);
	}

	{
		m_GameClear = AddGameObject<GameClear>(2);
	}

	AddGameObject<Radar>(2);

	m_Fade = AddGameObject<Fade>(2);

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/tutorial.wav");
	bgm->Play(true,0.1f);
}

void Tutorial::Uninit()
{
	
	Scene::Uninit();

	Unload();
}

void Tutorial::Update()
{
	Scene::Update();

	std::list<Enemy*> enemies = m_EnemyManager->GetEnemies();

	bool spawn = true;

	for (Enemy* enemy : enemies)
	{
		spawn = false;
		break;
	}

	if (spawn)
		SpawnEnemy();

	if (m_SpawnNumber > 3)
	{
		m_GameClear->Start();
		m_GameClear->SetClear(true);
	}

	if (m_Player->GetHp() <= 0)
	{
		m_GameClear->Start();
		m_GameClear->SetClear(false);
	}

	if (m_GameClear->GetFadeFinish())
		m_Fade->FadeOut();

	
	if (m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Preparation>();

}


void Tutorial::SpawnEnemy()
{
	switch (m_SpawnNumber)
	{
	case 0:
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = (((float)rand() / RAND_MAX * 10) - 5.0f) + 40.0f;
			pos.y = 4.0f;
			pos.z = (((float)rand() / RAND_MAX * 50) - 25.0f) + 50.0f;

			m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(pos);
		}

		break;
	case 1:
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = (((float)rand() / RAND_MAX * 20) - 10.0f) - 40.0f;
			pos.y = 4.0f;
			pos.z = (((float)rand() / RAND_MAX * 50) - 25.0f) + 50.0f;

			m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(pos);
		}

		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(43.0f, 4.0f, 22.5f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(43.0f, 4.0f, 17.5f));
		break;
	case 2:
		m_EnemyManager->AddEnemy<EnemyMutant>()->SetPosition(D3DXVECTOR3(-5.0f, 4.0f, 5.0f));
	}

	m_SpawnNumber++;
}