#pragma once


#include "gameObject.h"

class MeshField : public GameObject
{

private:
	ID3D11Buffer*				m_VertexBuffer{};
	ID3D11Buffer*				m_IndexBuffer{};
	ID3D11ShaderResourceView*	m_Texture{};
	ID3D11VertexShader*			m_VertexShader{};
	ID3D11PixelShader*			m_PixelShader{};
	ID3D11InputLayout*			m_VertexLayout{};

	char* m_TerrainTextureName;
	char* m_RTextureName;
	char* m_GTextureName;
	char* m_BTextureName;

	int m_XNum = 0;
	int m_ZNum = 0;

	VERTEX_3D					m_Vertex[31][31]{};
public:
	void Init(int FieldNum, char* TerrainTex, char* RTex, char* GTex, char*BTex);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	float GetHeight(D3DXVECTOR3 Position);
};