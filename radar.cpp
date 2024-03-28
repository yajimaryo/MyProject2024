#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "player.h"
#include "camera.h"
#include "enemyManager.h"
#include "item.h"
#include "radar.h"
#include "sprite.h"


void Radar::Init()
{
	float size;
	VERTEX_3D vertex[4];

	{
		size = 100.0f;

		vertex[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - size, SCREEN_HEIGHT / 2 - size, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 + size, SCREEN_HEIGHT / 2 - size, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - size, SCREEN_HEIGHT / 2 + size, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 + size, SCREEN_HEIGHT / 2 + size, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}
	{
		size = 5.0f;

		vertex[0].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - size, SCREEN_HEIGHT / 2 - size, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

		vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 + size, SCREEN_HEIGHT / 2 - size, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

		vertex[2].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 - size, SCREEN_HEIGHT / 2 + size, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

		vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH / 2 + size, SCREEN_HEIGHT / 2 + size, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		//頂点バッファ生成
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertex;

		Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBufferEnemy);
	}


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\circleVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\circlePS.cso");
	
	AddComponent<Sprite>()->Init(995.0f, -36.5f, 290.0f, 290.0f, (char*)"asset/texture/aim.png");
}

void Radar::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_VertexBuffer->Release();
}

void Radar::Update()
{
	m_Ring += 0.01f;

	if (m_Ring >= 1.0f)
		m_Ring = 0.0f;
}

void Radar::Draw()
{
	GameObject::Draw();

	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	D3DXVECTOR2 position = D3DXVECTOR2(500.0f, -250.0f);
	D3DXMATRIX worldMatrix;
	D3DXMatrixTranslation(&worldMatrix, position.x, position.y, 0.0f);
	D3DXMATRIX wvpMatrix = worldMatrix;

	Renderer::SetWorldMatrix(&wvpMatrix);

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	float percentage = (float)player->GetHp() / 100.0f;

	float r = (1.0f - percentage) * 2.0f;
	float g = percentage * 2.0f;

	PARAMETER param;
	param.hitpoint.x = m_Ring;
	param.baseColor = D3DXCOLOR(r, g, 0.0f, 0.6f);
	param.diffColor = D3DXCOLOR(r, g, 0.0f, 1.0f);
	Renderer::SetParameter(param);

	// 頂点バッファ設定やマテリアル設定など
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ワールドビュープロジェクション行列を渡して描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	EnemyDraw();

	ItemDraw();
}

void Radar::EnemyDraw()
{
	PARAMETER param;
	param.baseColor = D3DXCOLOR(1.0f, 0.2f, 0.2f, 0.6f);
	Renderer::SetParameter(param);

	// 頂点バッファ設定やマテリアル設定など
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBufferEnemy, &stride, &offset);

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();
	Camera* camera = scene->GetGameObject<Camera>();
	EnemyManager* em = scene->GetGameObject<EnemyManager>();

	D3DXVECTOR3 pPos = player->GetPosition();

	for(auto enemy : em->GetEnemies())
	{
		D3DXVECTOR3 peVec = enemy->GetPosition() - pPos;
		D3DXVECTOR3 epVec = pPos - enemy->GetPosition();

		float distance = D3DXVec3Length(&peVec);

		distance /= 100.0f;

		if (distance > 1.0f)
			distance = 1.0f;

		distance *= 100.0f;

		float angleRadians = atan2f(epVec.x, epVec.z);
		angleRadians -= camera->GetRotation().y - D3DX_PI / 2;

		D3DXVECTOR2 position;
		position.x = distance * cosf(angleRadians);
		position.x += 500.0f;

		position.y = distance * sinf(angleRadians);
		position.y += -250.0f;


		D3DXMATRIX worldMatrix;
		D3DXMatrixTranslation(&worldMatrix, position.x, position.y, 0.0f);
		D3DXMATRIX wvpMatrix = worldMatrix;

		Renderer::SetWorldMatrix(&wvpMatrix);

		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}

void Radar::ItemDraw()
{
	PARAMETER param;
	param.baseColor = D3DXCOLOR(0.2f, 1.0f, 0.2f, 0.6f);
	Renderer::SetParameter(param);

	// 頂点バッファ設定やマテリアル設定など
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBufferEnemy, &stride, &offset);

	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();
	Camera* camera = scene->GetGameObject<Camera>();

	std::vector<Item*> items = scene->GetGameObjects<Item>();

	D3DXVECTOR3 pPos = player->GetPosition();

	for (auto item : items)
	{
		D3DXVECTOR3 peVec = item->GetPosition() - pPos;
		D3DXVECTOR3 epVec = pPos - item->GetPosition();

		float distance = D3DXVec3Length(&peVec);

		distance /= 100.0f;

		if (distance > 1.0f)
			distance = 1.0f;

		distance *= 100.0f;

		float angleRadians = atan2f(epVec.x, epVec.z);
		angleRadians -= camera->GetRotation().y - D3DX_PI / 2;

		D3DXVECTOR2 position;
		position.x = distance * cosf(angleRadians);
		position.x += 500.0f;

		position.y = distance * sinf(angleRadians);
		position.y += -250.0f;


		D3DXMATRIX worldMatrix;
		D3DXMatrixTranslation(&worldMatrix, position.x, position.y, 0.0f);
		D3DXMATRIX wvpMatrix = worldMatrix;

		Renderer::SetWorldMatrix(&wvpMatrix);

		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}
