#include "main.h"
#include "manager.h"
#include "scene.h"
#include "message.h"
#include "animSprite.h"
#include "player.h"

void Message::Init(float x, float y, float Width, float Height, char * TextureName)
{
	m_Sprite = AddComponent<AnimSprite>();
	m_Sprite->Init(x, y, Width, Height, TextureName, 1, 1);

	m_Range = 5.0f;
}

void Message::Uninit()
{
	GameObject::Uninit();
}

void Message::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();
	D3DXVECTOR3 pos = player->GetPosition();

	m_Draw = false;

	if (m_Position.x + m_Range > pos.x && m_Position.x - m_Range < pos.x &&
		m_Position.z + m_Range > pos.z && m_Position.z - m_Range < pos.z)
	{
		m_Draw = true;
	}

}

void Message::Draw()
{
	if (m_Draw)
	{
		GameObject::Draw();
	}
}
