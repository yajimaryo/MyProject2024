
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "explosion.h"

#include "plate.h"

void Explosion::Init()
{
	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Plate = AddComponent<Plate>();

	m_Plate->Init(
		D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f),
		D3DXVECTOR3(1.0f, 2.0f, 0.0f), D3DXVECTOR3(-1.0f, 2.0f, 0.0f),
		D3DXVECTOR2(1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
		(char*)"asset/texture/explosion001.png");
	*/
}

void Explosion::Uninit()
{
	/*m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();*/
}

void Explosion::Update()
{

	/*m_Count += 0.2f;

	if (m_Count >= 7)
	{
		SetDestroy();
		return;
	}

	GameObject::Update();*/
}


void Explosion::Draw()
{
	////テクスチャ座標の変更

	//float x = (int)m_Count * (1.0f / 7.0f);
	//float y = 1.0f;
	//
	////頂点データ書き換え
	//D3D11_MAPPED_SUBRESOURCE msr;
	//Renderer::GetDeviceContext()->Map(m_Plate->GetVertexBuffer(), 0,
	//	D3D11_MAP_WRITE_DISCARD, 0, &msr);

	//VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//vertex[0].Position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	//vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[0].TexCoord = D3DXVECTOR2(x + 1.0f / 7.0f, 1.0f);

	//vertex[1].Position = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	//vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[1].TexCoord = D3DXVECTOR2(x, 1.0f);

	//vertex[2].Position = D3DXVECTOR3(1.0f, 2.0f, 0.0f);
	//vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[2].TexCoord = D3DXVECTOR2(x + 1.0f / 7.0f, 0.0f);

	//vertex[3].Position = D3DXVECTOR3(-1.0f, 2.0f, 0.0f);
	//vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertex[3].TexCoord = D3DXVECTOR2(x, 0.0f);

	//Renderer::GetDeviceContext()->Unmap(m_Plate->GetVertexBuffer(), 0);

	////入力レイアウト設定
	//Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	////シェーダー設定
	//Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	////カメラのビューマトリクス取得
	//Scene* scene = Manager::GetInstance()->GetScene();
	//Camera* camera = scene->GetGameObject<Camera>();
	//D3DXMATRIX view = camera->GetViewMatrix();

	//D3DXMATRIX invView;
	//D3DXMatrixInverse(&invView, NULL, &view);//逆行列
	//invView._41 = 0.0f;
	//invView._42 = 0.0f;
	//invView._43 = 0.0f;

	//// マトリクス設定
	//D3DXMATRIX world, scale, rot, trans;
	//D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	////D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	//world = scale * invView * trans;
	//Renderer::SetWorldMatrix(&world);

	//GameObject::Draw();
}