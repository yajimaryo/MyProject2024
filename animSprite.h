#pragma once

#include "component.h"

class AnimSprite : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	char* m_TextureName = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	int m_XNum, m_YNum = 0;

	int m_Count = 0;

	float m_x, m_y = 0.0f;
	float m_Width, m_Height = 0.0f;

public:
	void Init(float x, float y, float Width, float Height, char* TextureName, int XNum, int YNum);
	void Uninit();
	void Update();
	void Draw();

	void SetCount(int Count) { m_Count = Count; }

	void SetPosition(D3DXVECTOR2 Position) 
	{
		m_x = Position.x;
		m_y = Position.y;
	}

	void AddCount() { m_Count++; }
};