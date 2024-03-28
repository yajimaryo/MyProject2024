#pragma once

#include "gameObject.h"

class Radar :public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11Buffer* m_VertexBufferEnemy = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	float m_Ring = 0.0f;

	void EnemyDraw();
	void ItemDraw();

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;


};

class DrawPoint
{
private:
	D3DXVECTOR2 m_Position;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

public:
	/*void Init();
	void Uninit();
	void Update();
	void Draw();*/
};