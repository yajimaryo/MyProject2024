
#include "main.h"
#include "manager.h"
#include "effect.h"
#include "animPlate.h"
#include "plate.h"

void Effect::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Num,
	const char * TextureName, bool Billboard, int DeleteNumber)
{
	/*m_AP = AddComponent<AnimPlate>();
	m_AP->Init(Position, Scale, Rotation, Num, (char*)TextureName, Billboard);*/

	m_Plate = AddComponent<Plate>();
	m_Plate->Init(Position, Scale, Rotation, (char*)TextureName, Billboard);

	m_Position = Position;

	m_DeleteNumber = DeleteNumber;
}

void Effect::Uninit()
{
	/*m_AP->Uninit();
	delete m_AP;*/

	GameObject::Uninit();
}

void Effect::Update()
{
	m_Count += m_Speed;

	if ((int)m_Count >= m_DeleteNumber)
	{
		SetDestroy();
		return;
	}
	
	m_Alpha -= 0.01f;
	if (m_Alpha <= 0.0f)
		m_Alpha = 0.0f;

	m_Plate->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
	//m_AP->SetCount((int)m_Count);

	if (m_IsMove)
	{
		m_Position += m_Direction * m_MoveSpeed;
		//m_AP->SetPosition(m_Position);
		m_Plate->SetPosition(m_Position);
	}

	GameObject::Update();
}

void Effect::Draw()
{
	GameObject::Draw();
}
