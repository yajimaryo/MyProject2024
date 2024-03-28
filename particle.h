#pragma once

#include "gameObject.h"
#include <list>

class Particle : public GameObject
{
private:
	
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11GeometryShader* m_GeometryShader = nullptr;;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	char* m_ModelName;

	float m_Anim = 0.0f;
	float m_AnimForce = 0.0f; //äOÇ…çLÇ™ÇÈë¨ìx
	float m_MoveForce = 0.0f; //óéâ∫ë¨ìx

	int m_Time = 0;
public:
	void Init(D3DXVECTOR3 Position,char* ModelName = (char*)"asset\\model\\sphere.obj");
	void Uninit()override;
	void Update()override;
	void Draw()override;
};
