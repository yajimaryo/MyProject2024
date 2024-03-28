#pragma once

#include "gameObject.h"
#include "model.h"

class Sky : public GameObject
{
private:

	Model* m_Model = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

public:

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};