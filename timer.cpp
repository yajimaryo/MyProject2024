#include "main.h"
#include "manager.h"
#include "scene.h"
#include "timer.h"
#include "guage.h"
#include "animSprite.h"

void Timer::Init()
{
	m_TimeLimit = 3600;
	m_TimeNow = m_TimeLimit;

	m_Sprite = AddComponent<AnimSprite>();
	m_Sprite->Init(90.0f, 5.0f, 100.0f, 20.0f, (char*)"asset/texture/time.png", 1, 1);
}

void Timer::Update()
{
	
	if (!m_Guage)
	{
		Scene* scene = Manager::GetInstance()->GetScene();

		m_Guage = scene->AddGameObject<Guage>(3);
		m_Guage->Init(200.0f, 5.0f, SCREEN_WIDTH - 400.0f, 15.0f);
	}

	float percentage = (float)m_TimeNow / (float)m_TimeLimit;
	
	float r = (1.0f - percentage) * 2.0f;
	float g = percentage * 2.0f;


	if (r > 1.0f)
		r = 1.0f;

	if (g > 1.0f)
		g = 1.0f;

	m_Guage->SetGuage(D3DXVECTOR3(m_TimeNow, m_TimeLimit, m_TimeNow));
	m_Guage->SetBaseColor(D3DXCOLOR(r, g, 0.0f, 1.0f));

	m_TimeNow--;

	GameObject::Init();
}

void Timer::Uninit()
{
	GameObject::Uninit();
}

void Timer::Draw()
{
	GameObject::Draw();
}
