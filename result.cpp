#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "result.h"
#include "polygon2D.h"
#include "title.h"
#include "sprite.h"
#include "fade.h"
#include "score.h"
#include "audio.h"

int Result::m_Score = 0;
int Result::m_Hp = 0;

void Result::Init()
{
	Polygon2D* resultlogo = AddGameObject<Polygon2D>(2);
	resultlogo->AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, (char*)"asset/texture/result2.png");
	
	float bonus = 0;
	if (m_Hp >= 100)
	{
		bonus = 1000;
	}

	{
		m_Scores[0] = AddGameObject<Score>(2);
		m_Scores[0]->Init((SCREEN_WIDTH / 2) + 380.0f, 180.0f, 90.0f, 90.0f,80.0f,10);
		m_Scores[0]->SetScore(m_Score);
	}

	{
		m_Scores[1] = AddGameObject<Score>(2);
		m_Scores[1]->Init((SCREEN_WIDTH / 2) + 380.0f, 300.0f, 90.0f, 90.0f,80.0f,10);
		m_Scores[1]->SetScore(m_Hp);
	}

	{
		m_Scores[2] = AddGameObject<Score>(2);
		m_Scores[2]->Init((SCREEN_WIDTH / 2) + 380.0f, 420.0f, 90.0f, 90.0f, 80.0f,10);
		m_Scores[2]->SetScore(bonus);
	}
	

	{
		m_Scores[3] = AddGameObject<Score>(2);
		m_Scores[3]->Init((SCREEN_WIDTH / 2) + 380.0f, 570, 120.0f, 120.0f,100.0f,10);
		m_Scores[3]->SetScore(bonus + m_Score + m_Score * ((float)m_Hp / 100.0f));
	}

	m_Fade = AddGameObject<Fade>(2);

	Audio* bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset/audio/result.wav");
	bgm->Play(true, 0.2f);
}

void Result::Update()
{
	
	m_Scores[0]->Update();

	for (int i = 0; i < 3; i++)
	{
		if (m_Scores[i]->AddEnd())
		{
			m_Scores[i + 1]->Update();
		}
	}

	m_Fade->Update();

	if (Input::GetKeyTrigger(VK_SPACE))
		m_Fade->FadeOut();
		
	if(m_Fade->GetFadeFinish())
		Manager::GetInstance()->SetScene<Title>();
}
