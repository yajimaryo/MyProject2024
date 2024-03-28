#pragma once

#include "component.h"

class Sprite : public Component
{
private:
	D3DXVECTOR2 m_Position;
	D3DXVECTOR3 m_Scale;
	D3DXVECTOR3 m_Rotation;

	ID3D11Buffer* m_VertexBuffer = nullptr;
	char* m_TextureName = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	bool m_IsDraw = true;

public:
	void Init(float x, float y, float Width, float Height, char* TextureName);
	void Uninit();
	void Update();
	void Draw();

	void SetPosition(D3DXVECTOR2 Position) { m_Position = Position; }
	void SetScale(D3DXVECTOR3 Scale) { m_Scale = Scale; }
	void SetRotation(D3DXVECTOR3 Rotation) { m_Rotation = Rotation; }

	ID3D11Buffer* GetVertexBuffer() { return m_VertexBuffer; }
	
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }

	D3DXVECTOR2 GetPosition() { return m_Position; }

	void SetDraw(bool IsDraw) { m_IsDraw = IsDraw; }
};