#include "main.h"
#include "manager.h"
#include "loadingLogo.h"
#include "sprite.h"

void LoadingLogo::Init()
{
	m_Logo = AddComponent<Sprite>();
	m_Logo->Init(-50.0f, -50.0f, 100.0f, 100.0f, (char*)"asset/texture/loadingLogo.jpg");
	
	m_Logo->SetPosition(D3DXVECTOR2(SCREEN_WIDTH - 100.0f, SCREEN_HEIGHT - 100.0f));
}

void LoadingLogo::Uninit()
{
}

void LoadingLogo::Update()
{
	m_Rotation.z += 0.1f;
	m_Logo->SetRotation(m_Rotation);
}

void LoadingLogo::Draw()
{
	m_Logo->Draw();
}
