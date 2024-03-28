#pragma once

#include "gameobject.h"

class Collision : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;
	
	int m_Continuation = 0;
	float m_Damage = 0;
	int m_Player = 0; //ゲームオブジェクト:0.プレイヤー 1.敵 2,その他

public:
	void Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, int Continuation, int Damage, int Player);
	void Uninit();
	void Update();
	void Draw();
};