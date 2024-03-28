#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "resource.h"
#include "enemyManager.h"
#include "player.h"
#include <list>
#include "model.h"
#include "collision.h"

void Collision::Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, int Continuation, int Damage, int Player)
{
	m_Position = Position;
	m_Scale = Scale;
	m_Continuation = Continuation;
	m_Damage = Damage;
	m_Player = Player;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingPS.cso");
}

void Collision::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Collision::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();

	if (m_Player == 0 || m_Player == 3)
	{
		std::list<Enemy*> enemies = scene->GetGameObject<EnemyManager>()->GetEnemies();
		for (Enemy* enemy : enemies)
		{
			D3DXVECTOR3 pos = enemy->GetPosition();
			D3DXVECTOR3 scl = enemy->GetScale();

			D3DXVECTOR3 dir = m_Position - pos;
			dir.y = 0.0f;
			float length = D3DXVec3Length(&dir);

			if (length < scl.x + m_Scale.x)
			{
				if (m_Position.y - m_Scale.y / 1.0f < pos.y && m_Position.y + m_Scale.y / 1.0f > pos.y)
				{
					enemy->TakeDamage(m_Damage, pos);
				}
			}
		}
	}
	if (m_Player == 1 || m_Player == 3)
	{
		Player* player = scene->GetGameObject<Player>();

		D3DXVECTOR3 pos = player->GetPosition();
		D3DXVECTOR3 scl = player->GetScale();

		D3DXVECTOR3 dir = m_Position - pos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < 1.0f + m_Scale.x)
		{
			if (m_Position.y - 2.0f < pos.y && m_Position.y + 2.0f > pos.y)
			{
				player->TakeDamage(m_Damage);
			}
		}
	}

	m_Continuation--;

	if (m_Continuation <= 0)
	{
		SetDestroy();
	}
}

void Collision::Draw()
{
	////入力レイアウト設定
	//Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////シェーダー設定
	//Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	//// マトリクス設定
	//D3DXMATRIX world, scale, rot, trans;
	//D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	//world = scale * rot * trans;

	//Renderer::SetWorldMatrix(&world);

	//ResourceManager::GetInstance()->GetResouseModel((char*)"asset\\model\\torus.obj.")->Draw();
}
