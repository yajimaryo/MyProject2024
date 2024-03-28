#include "main.h"
#include "manager.h"
#include "score.h"
#include "animSprite.h"
#include "audio.h"


void Score::Init(float x, float y, float Width, float Height, float Space, int AddNumber)
{
	for (int i = 0; i < DIGITS; i++)
	{
		m_AS[i] = AddComponent<AnimSprite>();

		//m_AS[i]->Init(SCREEN_WIDTH - 100 - (60 * i), 10.0f, 100.0f, 100.0f, (char*)"asset/texture/score.png", 5, 5);
		m_AS[i]->Init(x - (Space * i), y, Width, Height, (char*)"asset/texture/number.png", 10, 1);
	}
	m_AddNumber = AddNumber;

	m_AddSE = AddComponent<Audio>();
	m_AddSE->Load("asset/audio/score.wav");
}

void Score::Update()
{
	if (m_DrawScore < m_Score)
	{
		m_AddEnd = false;

		m_AddSE->Play(false,0.2f);
		m_DrawScore += m_AddNumber;

	}

	if (m_DrawScore > m_Score)
	{
		m_DrawScore = m_Score;
	}

	if (m_DrawScore == m_Score)
		m_AddEnd = true;
}

void Score::Uninit()
{
	GameObject::Uninit();
}

void Score::Draw()
{
	if (m_IsDraw)
	{
		int score = m_DrawScore;

		for (int i = 0; i < DIGITS; i++)
		{
			int num = score % 10;

			m_AS[i]->SetCount(num);
			m_AS[i]->Draw();

			score /= 10;
			if (score == 0)
			{
				break;
			}
		}
	}
}


