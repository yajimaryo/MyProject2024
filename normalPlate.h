#pragma once

#include "gameObject.h"

class NormalPlate : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	char* m_TextureName = nullptr;
	char* m_NormalTextureName = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	bool m_Billboard = true;

	D3DXVECTOR2 m_NormalPos;
	D3DXVECTOR2 m_NormalSpeed;

public:
	void Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation,
		char* TextureName, char* NormalTextureName , bool Billboard);

	void Uninit();
	void Update();
	void Draw();

	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }

};