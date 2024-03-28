#pragma once

#include "gameObject.h"

class AnimPlate;
class Plate;

class Effect : public GameObject
{
private:
	AnimPlate* m_AP = nullptr;
	Plate* m_Plate = nullptr;
	float m_MoveSpeed = 0.0f;
	D3DXVECTOR3 m_Direction{};
	bool m_IsMove = false;

	float m_Alpha = 1.0f;

	int m_DeleteNumber = 0;

	float m_Count = 0;

	float m_Speed = 0.2f;

public:
	void Init(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation, D3DXVECTOR2 Num,
		const char* TextureName, bool Billboard, int DeleteNumber);
	
	void Uninit();
	void Update();
	void Draw();

	void SetSpeed(float Speed) { m_Speed = Speed; }

	void SetMove(float MoveSpeed, D3DXVECTOR3 Direction) {
		m_MoveSpeed = MoveSpeed;
		m_Direction = Direction;
		m_IsMove = true;
	}
};