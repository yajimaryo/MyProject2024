#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "guage.h"
#include "player.h"

void Guage::Init(float x, float y, float Width, float Height)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(x, y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(x + Width, y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(x, y + Height, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(x + Width, y + Height, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//ここにシェーダーファイルのロードを追加
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "shader\\gaugeVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "shader\\gaugePS.cso");


	m_BaseColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
}

void Guage::Uninit()
{
	m_VertexBuffer->Release();
	
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Guage::Update()
{
	//m_Position.x += 1.0f;
	//VERTEX_3D vertex[4];

	//// 新しい位置に基づいて頂点を更新
	//vertex[0].Position = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	//vertex[1].Position = D3DXVECTOR3(m_Position.x + 100.0f, m_Position.y, 0.0f);
	//vertex[2].Position = D3DXVECTOR3(m_Position.x, m_Position.y + 20.0f, 0.0f);
	//vertex[3].Position = D3DXVECTOR3(m_Position.x + 100.0f, m_Position.y + 20.0f, 0.0f);

	//// 頂点バッファ生成
	//D3D11_BUFFER_DESC bd;
	//ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd;
	//ZeroMemory(&sd, sizeof(sd));
	//sd.pSysMem = vertex;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void Guage::Draw()
{
	if (m_IsDraw)
	{
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		//頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		//マテリアル設定
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		material.TextureEnable = true;
		Renderer::SetMaterial(material);

		PARAMETER param;
		param.hitpoint.x = m_GuageNow;
		param.hitpoint.y = m_GuageMax;
		param.hitpoint.z = m_GuageOld;

		param.baseColor = m_BaseColor;//D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		param.lostColor = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
		param.diffColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		Renderer::SetParameter(param);

		//プリミティブトポロジ設定
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//ポリゴン描画
		Renderer::GetDeviceContext()->Draw(4, 0);
	}
}
