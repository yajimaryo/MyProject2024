#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "backGround.h"
#include "sprite.h"
#include "input.h"

void BackGround::Init()
{
	m_LogoMoveNum = 0;
	m_LogoMoveForce = 0.0f;

	m_LogoPos = D3DXVECTOR2(SCREEN_WIDTH / 2, -100.0f);
	m_Time = 0.0f;

	m_Logo = AddComponent<Sprite>();
	m_Logo->Init(-400.0f, -150.0f, 800.0f, 300.0f, (char*)"asset/texture/TitleLogo.png");
	m_Logo->SetPosition(m_LogoPos);

	AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT - 200.0f, 280.0f, 80.0f, (char*)"asset/texture/play.png");
	AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2 - 100.0f, SCREEN_HEIGHT - 100.0f, 210.0f, 80.0f, (char*)"asset/texture/end.png");
}

void BackGround::Uninit()
{
	GameObject::Uninit();
}

void BackGround::Update()
{
	if (m_LogoMoveNum < 3)
	{
		m_LogoMoveForce += 0.1f * 9.8f * m_Time * m_Time;
		m_LogoPos.y += m_LogoMoveForce;
		m_Logo->SetPosition(m_LogoPos);

		if (m_LogoPos.y >= SCREEN_HEIGHT / 2 - 100.0f)
		{
			m_LogoMoveForce *= -1.0f;
			m_LogoPos.y -= 5.0f;
			m_LogoMoveNum++;
		}
		m_Time += 1.0f / 60.0f;
	}

	if (Input::GetMouseLTrigger())
	{
		m_LogoMoveNum = 0;
		m_LogoMoveForce = 0.0f;

		m_LogoPos = D3DXVECTOR2(SCREEN_WIDTH / 2, -100.0f);
		m_Time = 0.0f;
	}
}

void BackGround::Draw()
{
	GameObject::Draw();
}