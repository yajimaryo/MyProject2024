
#include "main.h"
#include "renderer.h"
#include "gameClear.h"
#include "sprite.h"

void GameClear::Init()
{
	
	m_ClearSprite = AddComponent<Sprite>();
	m_ClearSprite->Init(0.0f, SCREEN_HEIGHT / 2.0f - 100.0f, SCREEN_WIDTH, 200.0f, (char*)"asset/texture/GameClear.png");

	m_LoseSprite = AddComponent<Sprite>();
	m_LoseSprite->Init(0.0f, SCREEN_HEIGHT / 2.0f - 100.0f, SCREEN_WIDTH, 200.0f, (char*)"asset/texture/GameOver.png");

	m_Alpha = 0.0f;
}

void GameClear::Uninit()
{
	GameObject::Uninit();
}

void GameClear::Update()
{
	GameObject::Update();

	if (m_Start)
	{
		m_Alpha += 0.005f;

		if (m_Alpha >= 1.0f)
		{
			m_Alpha = 1.0f;
			m_FadeFinish = true;
		}
	}

	m_ClearSprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
	m_LoseSprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
}


void GameClear::Draw()
{
	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	if (m_IsClear)
	{
		m_ClearSprite->Draw();
	}
	else
	{
		m_LoseSprite->Draw();
	}
}