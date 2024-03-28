#pragma once

#include "gameObject.h"

class Box : public GameObject
{
private:
	char* m_ModelName;
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

public:

	void Init(char* ModelName);
	void Uninit() override;
	void Update() override;
	void Draw() override;
};