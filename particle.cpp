#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "particle.h"
#include "resource.h"
#include "model.h"

void Particle::Init(D3DXVECTOR3 Position, char* ModelName)
{
	m_Position = Position;
	m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);

	m_ModelName = ModelName;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\particleVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\particlePS.cso");
	Renderer::CreateGeometryShader(&m_GeometryShader, "shader\\particleGS.cso");
}

void Particle::Uninit()
{
	m_GeometryShader->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Particle::Update()
{
	
	m_Rotation += D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_Anim += m_AnimForce;
	if (m_Anim >= 300.0f)
	{
		m_Anim = 0.0f;
		m_Time = 0;
		m_MoveForce = 0.0f;
		m_AnimForce = 0.0f;
		SetDestroy();
	}

	m_AnimForce += 0.2f;

	m_MoveForce += 0.000007f * 9.8f * m_Time * m_Time;

	m_Time++;
}

void Particle::Draw()
{
	PARAMETER param;
	param.baseColor.r = m_Anim;
	param.baseColor.g = m_MoveForce;
	param.diffColor = D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.3f);
	Renderer::SetParameter(param);

	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	Renderer::GetDeviceContext()->GSSetShader(m_GeometryShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	if (m_ModelName == nullptr)
		m_ModelName = (char*)"asset\\model\\sphere.obj";

	ResourceManager::GetInstance()->GetResouseModel(m_ModelName)->Draw();

	Renderer::GetDeviceContext()->GSSetShader(NULL, NULL, 0);
}
