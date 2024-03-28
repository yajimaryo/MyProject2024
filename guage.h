#pragma once

#include "gameObject.h"

class Guage : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	float m_GuageNow;
	float m_GuageMax;
	float m_GuageOld;

	D3DXCOLOR m_BaseColor{};

	bool m_IsDraw = true;

public:
	void Init(float x, float y, float Width, float Height);
	void Uninit();
	void Update();
	void Draw();

	void SetGuage(D3DXVECTOR3 Guages)
	{
		m_GuageNow = Guages.x;
		m_GuageMax = Guages.y;
		m_GuageOld = Guages.z;
	}

	void SetBaseColor(D3DXCOLOR Color) { m_BaseColor = Color; }
	void SetDraw(bool IsDraw) { m_IsDraw = IsDraw; }
};