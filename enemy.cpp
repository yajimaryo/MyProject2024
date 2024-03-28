
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "score.h"
#include "effect.h"
#include "model.h"
#include "resource.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"
#include "meshField.h"
#include "item.h"
#include "particle.h"

void Enemy::Init()
{
	m_Hp = 50.0f;

	m_HitSE = AddComponent<Audio>();
	m_HitSE->Load("asset/audio/hit.wav");

	m_Shadow = AddComponent<Shadow>();

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderAttack, &m_VertexLayoutAttack,
		"shader\\pixelLightingAttackVS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderAttack,
		"shader\\pixelLightingAttackPS.cso");

	m_Scale = D3DXVECTOR3(3.0f, 3.0f, 3.0f);
	SetCollisionSize(10.0f);
	SetCollisionOffset(D3DXVECTOR3(0.0f, 3.5f, 0.0f));
}

void Enemy::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_VertexLayoutAttack->Release();
	m_VertexShaderAttack->Release();
	m_PixelShaderAttack->Release();
}

void Enemy::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	if (m_Hp <= 0.0f)
	{
		Particle* pa = scene->AddGameObject<Particle>(1);
		pa->Init(m_Position + D3DXVECTOR3(0.0f, 1.5f, 0.0f), m_ModelName);
		pa->SetScale(D3DXVECTOR3(2.5f, 2.5f, 2.5f));

		int num = rand() % 10;

		if (num < 1)
			scene->AddGameObject<Item>(1)->Init(m_Position);
		
		SetDestroy();
	}

	//重力
	if (!m_Flight)
		m_Velocity.y -= 0.015f;

	if (m_Position.y < m_GroungHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = m_GroungHeight;
		m_Velocity.y = 0.0f;
	}



	//地形との当たり判定
	m_GroungHeight = 0.0f;

	MeshField* mf = scene->GetGameObject<MeshField>();

	m_GroungHeight = mf->GetHeight(m_Position);

	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 pos = cylinder->GetPosition();
		D3DXVECTOR3 scl = cylinder->GetScale();

		D3DXVECTOR3 dir = m_Position - pos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < scl.x + m_Scale.x)
		{
			if (m_Position.y < pos.y + scl.y - 0.5f)
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;

				if (m_Velocity.y == 0.0f)
				{
					if (cylinder->GetScale().y > 3.0f)
					{
						m_Velocity.y = 0.5f;
					}
					else
					{
						m_Velocity.y = 0.2f;
					}
				}
			}
			else
			{
				m_GroungHeight = pos.y + scl.y;
			}
			break;
		}
	}

	//boxとの当たり判定
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();
	for (Box* box : boxes)
	{
		D3DXVECTOR3 pos = box->GetPosition();
		D3DXVECTOR3 scl = box->GetScale();
		D3DXVECTOR3 right = box->GetRight();
		D3DXVECTOR3 forward = box->GetForward();
		D3DXVECTOR3 direction = m_Position - pos;

		float obbx = D3DXVec3Dot(&direction, &right);
		float obbz = D3DXVec3Dot(&direction, &forward);

		//OBB
		if (fabs(obbx) < scl.x && fabs(obbz) < scl.z)
		{
			if (m_Position.y < pos.y + (scl.y * 2 - 0.5f))
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;

				if (m_Velocity.y == 0.0f)
				{
					if (box->GetScale().y > 3.0f)
					{
						m_Velocity.y = 0.5f;
					}
					else
					{
						m_Velocity.y = 0.2f;
					}
				}
			}
			else
			{
				if (m_GroungHeight < pos.y + scl.y * 2)
					m_GroungHeight = pos.y + scl.y * 2;
			}
			break;
		}

	}


	if (m_Position.z > 98.0f || m_Position.z < -98.0f)
	{
		m_Position.z = m_OldPosition.z;
	}

	if (m_Position.x > 98.0f || m_Position.x < -98.0f)
	{
		m_Position.x = m_OldPosition.x;
	}

	if (m_Hit > 0)
		m_Hit--;

	m_Shadow->SetPosition(D3DXVECTOR3(m_Position.x, m_GroungHeight + 0.1f, m_Position.z));

	GameObject::Update();
}


void Enemy::Draw()
{
	GameObject::Draw();

	if (m_AttackFrame <= 20)
	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayoutAttack);

		//シェーダー設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShaderAttack, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderAttack, NULL, 0);
	}
	else
	{
		//入力レイアウト設定
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//シェーダー設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	}

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

}

void Enemy::TakeDamage(float damage, D3DXVECTOR3 Position)
{
	if (!m_IsFight)
		m_IsFight = true;

	m_Hp -= damage;
	m_Hit = 4;

	Scene* scene = Manager::GetInstance()->GetScene();

	scene->AddGameObject<Particle>(1)->Init(Position);

	m_HitSE->Play(false, 0.3f);
}

void Enemy::SetMovePosition(D3DXVECTOR3 Position)
{
	m_MovePosition = Position;

	m_Velocity = m_MovePosition - m_Position;
	D3DXVec3Normalize(&m_Velocity, &m_Velocity);
}

float Enemy::PlayerDist()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 pos = player->GetPosition();

	D3DXVECTOR3 dir = m_Position - pos;
	dir.y = 0.0f;
	float length = D3DXVec3Length(&dir);

	return length;
}
