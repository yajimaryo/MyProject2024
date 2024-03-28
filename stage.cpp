
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "stage.h"
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
#include "message.h"
#include "box.h"
#include "audio.h"
#include "rock.h"
#include "animPlate.h"
#include "plate.h"
#include "enemyMutant.h"
#include "enemyDrone.h"
#include "radar.h"
#include "normalPlate.h"
#include "preparation.h"
#include "gameClear.h"

bool Stage::m_LoadFinish = false;

void Stage::Load()
{
	EnemyMutant::Load();
	Player::Load();
	m_LoadFinish = true;
}

void Stage::Unload()
{
	EnemyMutant::Unload();
	Player::Unload();
	m_LoadFinish = false;
}

void Stage::Init()
{
	srand(2);

	AddGameObject<Camera>(0);

	AddGameObject<Sky>(1);

	MeshField* meshField = AddGameObject<MeshField>(1);
	meshField->Init(1,
		(char*)"asset/texture/ground006.png",
		(char*)"asset/texture/field012.jpg",
		(char*)"asset/texture/field008.jpg",
		(char*)"asset/texture/field010.jpg");

	m_Player = AddGameObject<Player>(2);
	m_Player->SetPosition(D3DXVECTOR3(0.0f, meshField->GetHeight(D3DXVECTOR3(0.0f, 0.0f, -50.0f)), -50.0f));

	//â∆
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\house01.obj");
		box->SetPosition(D3DXVECTOR3(-30.0f, 0.0f, -30.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\house01.obj");
		box->SetPosition(D3DXVECTOR3(-20.0f, 0.0f, -30.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\house01.obj");
		box->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\house01.obj");
		box->SetPosition(D3DXVECTOR3(80.0f, 0.0f, 20.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\house01.obj");
		box->SetPosition(D3DXVECTOR3(80.0f, 0.0f, -50.0f));
		box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	}
	{
		for (int i = 0; i < 8; i++)
		{
			{
				Box* box = AddGameObject<Box>(1);
				box->Init((char*)"asset\\model\\house01.obj");
				box->SetPosition(D3DXVECTOR3(-125.0f + 15.0f * i, 0.0f, 100.0f));
				box->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
			}
		}
	}


	//ÉKÅ[ÉhÉåÅ[Éã
	{
		for (int i = 0; i < 8; i++)
		{
			if (i != 2)
			{
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(12.0f, 0.0f, -115.0f + 25.0f * i));
					box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
				}
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(-87.0f, 0.0f, -115.0f + 25.0f * i));
					box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
				}
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(-67.0f, 0.0f, -115.0f + 25.0f * i));
					box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
				}
			}
			{
				Box* box = AddGameObject<Box>(1);
				box->Init((char*)"asset\\model\\block.obj");
				box->SetPosition(D3DXVECTOR3(65.0f, 0.0f, -115.0f + 25.0f * i));
				box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
			}
		}
	}
	
	{
		for (int i = 0; i < 6; i++)
		{
			if (i != 2)
			{
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(-125.0f + 25.0f * i, 0.0f, 73.0f));
					box->SetScale(D3DXVECTOR3(10.0f, 0.7f, 0.2f));
				}
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(-125.0f + 25.0f * i, 0.0f, -54.0f));
					box->SetScale(D3DXVECTOR3(10.0f, 0.7f, 0.2f));
				}
				{
					Box* box = AddGameObject<Box>(1);
					box->Init((char*)"asset\\model\\block.obj");
					box->SetPosition(D3DXVECTOR3(-125.0f + 25.0f * i, 0.0f, -74.0f));
					box->SetScale(D3DXVECTOR3(10.0f, 0.7f, 0.2f));
				}
			}
			{
				Box* box = AddGameObject<Box>(1);
				box->Init((char*)"asset\\model\\block.obj");
				box->SetPosition(D3DXVECTOR3(-125.0f + 25.0f * i, 0.0f, 93.0f));
				box->SetScale(D3DXVECTOR3(10.0f, 0.7f, 0.2f));
			}
		}
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\block.obj");
		box->SetPosition(D3DXVECTOR3(12.0f, 0.0f, -115.0f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\block.obj");
		box->SetPosition(D3DXVECTOR3(12.0f, 0.0f, -90.0f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
	}

	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\block.obj");
		box->SetPosition(D3DXVECTOR3(65.0f, 0.0f, 85.0f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\block.obj");
		box->SetPosition(D3DXVECTOR3(65.0f, 0.0f, 110.0f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->Init((char*)"asset\\model\\block.obj");
		box->SetPosition(D3DXVECTOR3(12.0f, 0.0f, 110.0f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 10.0f));
	}

	m_EnemyManager = AddGameObject<EnemyManager>(1);

	{
		m_GameClear = AddGameObject<GameClear>(2);
	}

	AddGameObject<Radar>(2);

	m_Fade = AddGameObject<Fade>(2);

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/tutorial.wav");
	bgm->Play(true, 0.1f);
}

void Stage::Uninit()
{

	Scene::Uninit();

	Unload();
}

void Stage::Update()
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


void Stage::SpawnEnemy()
{
	switch (m_SpawnNumber)
	{
	case 0:
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = ((float)rand() / RAND_MAX * 150 - 75);
			pos.z = ((float)rand() / RAND_MAX * 150 - 75);
			pos.y = 20.0f;

			m_EnemyManager->AddEnemy<EnemyDrone>()->SetPosition(pos);
		}
		break;
	case 1:
		for (int i = 0; i < 10; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = ((float)rand() / RAND_MAX * 150 - 75);
			pos.z = ((float)rand() / RAND_MAX * 150 - 75);
			pos.y = 20.0f;

			m_EnemyManager->AddEnemy<EnemyDrone>()->SetPosition(pos);
		}

		for (int i = 0; i < 15; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = (((float)rand() / RAND_MAX * 50) - 25.0f) + 60.0f;
			pos.y = 4.0f;
			pos.z = (((float)rand() / RAND_MAX * 20) - 10.0f) - 70.0f;

			m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(pos);
		}

		for (int i = 0; i < 5; i++)
		{
			D3DXVECTOR3 pos;
			pos.x = (((float)rand() / RAND_MAX * 50) - 25.0f) + 60.0f;
			pos.y = 4.0f;
			pos.z = (((float)rand() / RAND_MAX * 20) - 10.0f) - 80.0f;

			m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(pos);
		}
		break;
	case 2:
		
		m_EnemyManager->AddEnemy<EnemyMutant>()->SetPosition(D3DXVECTOR3(-5.0f, 4.0f, 5.0f));
		break;
	}

	m_SpawnNumber++;
}