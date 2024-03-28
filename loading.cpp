#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "loading.h"
#include "backGround.h"
#include "input.h"
#include "tutorial.h"
#include "stage.h"
#include "loadingLogo.h"
#include "sprite.h"
#include <thread>

int Loading::m_StageNum = 0;

void Loading::Init()
{
	//LoadingLogo���V�[���ɒǉ�
	AddGameObject<LoadingLogo>(2);

	//m_StageNum�̒l�ɉ����ăV�[���̃��[�h���}���`�X���b�h�ōs��
	if (m_StageNum == 0)
	{
		std::thread th(&Tutorial::Load);
		th.detach();
	}
	else if (m_StageNum == 1)
	{
		std::thread th(&Stage::Load);
		th.detach();
	}
}

void Loading::Update()
{
	Scene::Update();
	
	if (m_StageNum == 0)
	{
		if (Tutorial::GetLoadFinish())
		{
			Manager::GetInstance()->SetScene<Tutorial>();
		}
	}
	else if (m_StageNum == 1)
	{
		if (Stage::GetLoadFinish())
		{
			Manager::GetInstance()->SetScene<Stage>();
		}
	}
}
