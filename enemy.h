#pragma once

#include "gameObject.h"

class Weapon;
class Audio;
class Shadow;

class Enemy : public GameObject
{
private:
	bool m_IsFight = false;
	bool m_Flight = false;
	float m_ColisionSize = 2.0f;
	D3DXVECTOR3 m_CollisionOffset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	ID3D11VertexShader* m_VertexShaderAttack = nullptr;
	ID3D11PixelShader* m_PixelShaderAttack = nullptr;
	ID3D11InputLayout* m_VertexLayoutAttack = nullptr;

	Audio* m_HitSE = nullptr;

	Shadow* m_Shadow = nullptr;

protected:

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	D3DXVECTOR3 m_MovePosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	Weapon* m_Weapon = nullptr;

	char* m_ModelName = nullptr;

	float m_Hp = 0.0f;
	int m_Score = 0;

	int m_AttackFrame = 0;
	int m_AttackTime = 0; //çUåÇÇÃå„åÑ
	bool m_Attack = false; //çUåÇíÜÇ©Ç«Ç§Ç©
	int m_MoveFrame = 0;
	float m_GroungHeight = 0.0f;
	int m_Hit = 0;
public:

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	bool GetIsFight() { return m_IsFight; }
	void TakeDamage(float Damage, D3DXVECTOR3 Position);
	void SetMovePosition(D3DXVECTOR3 Position);
	float PlayerDist();
	void SetCollisionSize(float Size) { m_ColisionSize = Size; }
	float GetCollisionSize() { return m_ColisionSize; }

	void SetFlight() { m_Flight = true; }

	void SetVelocity(D3DXVECTOR3 Velocity) { m_Velocity = Velocity; }
	D3DXVECTOR3 GetVelocity() { return m_Velocity; }

	void AddVelocity(D3DXVECTOR3 Velocity) { m_Velocity += Velocity; }

	void SetCollisionOffset(D3DXVECTOR3 Offset) { m_CollisionOffset = Offset; }
	D3DXVECTOR3 GetCollisionOffset() { return m_CollisionOffset; }
};