#pragma once

#include "component.h"

class AnimPlate : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	char* m_TextureName = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXVECTOR3 m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	D3DXVECTOR2 m_Num = D3DXVECTOR2(0.0f, 0.0f);

	bool m_Billboard = true;

	int m_Count = 0;
	int m_Check = false;

public:
	void Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Num,
		char* TextureName, bool Billboard);

	void Uninit();
	void Update();
	void Draw();

	void SetCount(int Count) { m_Count = Count; }
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	
};