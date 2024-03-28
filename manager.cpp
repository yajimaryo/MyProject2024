#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "tutorial.h"
#include "title.h"
#include "result.h"
#include "audio.h"
#include <time.h>
#include "loading.h"

Manager* Manager::m_pInstance = nullptr;

Scene* Manager::m_Scene = nullptr;
Scene* Manager::m_NextScene = nullptr;

bool Manager::m_End = false;

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	SetScene<Title>();
}

void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}

		m_Scene = m_NextScene;
		m_Scene->Init();

		m_NextScene = nullptr;
	}

	m_Scene->Update();

}

void Manager::Draw()
{
	Renderer::Begin();
	
	m_Scene->Draw();

	Renderer::End();
}

