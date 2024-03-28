#pragma once

#include "gameObject.h"


class Sprite;

class BackGround : public GameObject
{
private:

	D3DXVECTOR2 m_LogoMove[5];
	int m_LogoMoveNum;
	float m_LogoU;//èâë¨ìx
	float m_LogoMoveForce;
	float m_Time;

	ID3D11Buffer* m_VertexBuffer = nullptr;
	char* m_TextureName = nullptr;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	Sprite* m_Logo = nullptr;
	D3DXVECTOR2 m_LogoPos;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};