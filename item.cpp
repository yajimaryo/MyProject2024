#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "plate.h"
#include "item.h"
#include "player.h"
#include "meshField.h"

void Item::Init(D3DXVECTOR3 Position)
{
	m_Position = Position;
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Plate = AddComponent<Plate>();
	m_Plate->Init(m_Position, m_Scale, D3DXVECTOR3(0.0f, 0.0f, 0.0f), (char*)"asset/texture/heal.png", true);

	m_Heal = 10.0f;
}

void Item::Uninit()
{
	GameObject::Uninit();
}

void Item::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();
	MeshField* mf = scene->GetGameObject<MeshField>();

	if (m_Position.y > mf->GetHeight(m_Position))
	{
		m_Position.y -= 0.1f;
		m_Plate->SetPosition(m_Position);
	}

	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 direction = playerPos - m_Position;

	float length = D3DXVec3LengthSq(&direction);

	if (length < 2.0f)
	{
		player->Heal(m_Heal);
		SetDestroy();

		return;
	}

	GameObject::Update();
}

void Item::Draw()
{
	GameObject::Draw();
}
