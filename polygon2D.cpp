
#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"

void Polygon2D::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	//AddComponent<Sprite>()->Init(100.0f, 100.0f, 600.0f, 400.0f, (char*)"asset/texture/poppo.jpg");
	//AddComponent<Sprite>()->Init(100.0f, 0.0f, 150.0f, 100.0f, (char*)"asset/texture/field004.jpg");
	//AddComponent<Sprite>()->Init(550.0f, 0.0f, 150.0f, 100.0f, (char*)"asset/texture/field004.jpg");
}

void Polygon2D::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	GameObject::Uninit();
}

void Polygon2D::Update()
{
	GameObject::Update();
}


void Polygon2D::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリクス設定
	Renderer::SetWorldViewProjection2D();

	GameObject::Draw();
}