#pragma once

#include "gameObject.h"
class Plate;

class Explosion : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	float m_Count = 0.0f;
	Plate* m_Plate = nullptr;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};