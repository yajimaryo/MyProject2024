
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "game.h"

#include "polygon2D.h"
#include "sprite.h"
#include "field.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "enemyMove.h"
#include "enemyAttack.h"
#include "bullet.h"
#include "explosion.h"
#include "enemyManager.h"
#include "cylinder.h"
#include "box.h"
#include "result.h"
#include "score.h"
#include "audio.h"
#include "animPlate.h"
#include "sky.h"
#include "fade.h"
#include "guage.h"
#include "timer.h"

void Game::Init()
{
	AddGameObject<Camera>(0);

	AddGameObject<Sky>(1);

	AddGameObject<Field>(1);

	AddGameObject<Timer>(3);

	//ç∂çÚ
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, 12.5f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 8.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, -12.5f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 8.0f));
	}
	//âEçÚ
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(25.0f, 0.0f, 12.5f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 8.0f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(25.0f, 0.0f, -12.5f));
		box->SetScale(D3DXVECTOR3(0.2f, 0.7f, 8.0f));
	}
	//âúçÚ
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(12.5f, 0.0f, 25.0f));
		box->SetScale(D3DXVECTOR3(8.0f, 0.7f, 0.2f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-12.5f, 0.0f, 25.0f));
		box->SetScale(D3DXVECTOR3(8.0f, 0.7f, 0.2f));
	}
	//éËëOçÚ
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(12.5f, 0.0f, -25.0f));
		box->SetScale(D3DXVECTOR3(8.0f, 0.7f, 0.2f));
	}
	{
		Box* box = AddGameObject<Box>(1);
		box->SetPosition(D3DXVECTOR3(-12.5f, 0.0f, -25.0f));
		box->SetScale(D3DXVECTOR3(8.0f, 0.7f, 0.2f));
	}

	{
		Cylinder* cyilinder = AddGameObject<Cylinder>(1);
		cyilinder->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		cyilinder->SetScale(D3DXVECTOR3(8.0f, 3.0f, 8.0f));
	}

	m_EnemyManager = AddGameObject<EnemyManager>(1);
	AddGameObject<Player>(2)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	AddGameObject<Score>(3)->Init(SCREEN_WIDTH - 80, SCREEN_HEIGHT - 80.0f, 60.0f, 60.0f, 60.0f);

	m_Fade = AddGameObject<Fade>(3);

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/game01.wav");
	bgm->Play(true,0.2f);
}

void Game::Uninit()
{
	Scene::Uninit();
}

void Game::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();

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
	

	Timer* timer = scene->GetGameObject<Timer>();
	Player* player = scene->GetGameObject<Player>();

	if (timer->Finish() || player->GetHp() <= 0.0f)
	{
		Score* score = scene->GetGameObject<Score>();
		

		Result::SetScore(score->GetScore());
		Result::SetHp(player->GetHp());
		m_Fade->FadeOut();
	}

	if(m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Result>();
}

void Game::SpawnEnemy()
{
	switch (m_SpawnNumber)
	{
	case 0:
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(0.0f, 4.0f, 0.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(5.0f, 4.0f, 5.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(-5.0f, 4.0f, 5.0f));
		break;
	case 1:
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(35.0f, 4.0f, 25.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(40.0f, 4.0f, 20.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(40.0f, 4.0f, 15.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(43.0f, 4.0f, 22.5f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(43.0f, 4.0f, 17.5f));
		break;
	case 3:
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(15.0f, 4.0f, 30.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(25.0f, 4.0f, 30.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(-15.0f, 4.0f, 30.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(-25.0f, 4.0f, 30.0f));
		break;
	case 4:
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(0.0f, 4.0f, 30.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(25.0f, 4.0f, 10.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(-25.0f, 4.0f, 10.0f));
		break;
	case 5:
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(20.0f, 4.0f, 20.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(20.0f, 4.0f, -20.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(-20.0f, 4.0f, 20.0f));
		m_EnemyManager->AddEnemy<EnemyAttack>()->SetPosition(D3DXVECTOR3(-20.0f, 4.0f, -20.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(5.0f, 4.0f, 0.0f));
		m_EnemyManager->AddEnemy<EnemyMove>()->SetPosition(D3DXVECTOR3(-5.0f, 4.0f, 0.0f));
		break;
	}

	m_SpawnNumber++;

	if (m_SpawnNumber >= 6)
		m_SpawnNumber = 0;
}
