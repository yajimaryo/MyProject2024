#pragma once

#include "gameObject.h"

class Plate;

class Bullet : public GameObject
{
private:
	Plate* m_Plate = nullptr;
	D3DXVECTOR3 m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float m_Speed = 0.0f;
	int m_EffectCount = 0;

	int m_Number = 0;//発射したゲームオブジェクト:0.プレイヤー 1.敵 2,その他

	int m_Damage = 0;

	bool m_IsExplosion = false;

public:
	void Init(D3DXVECTOR3 Position);
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetVelocity(D3DXVECTOR3 Velocity){	m_Velocity = Velocity; }
	void SetSpeed(float Speed){ m_Speed = Speed; }
	void SetNumber(int Number = 0) { m_Number = Number; }
	void SetDamage(float Damage) { m_Damage = Damage; }
	void SetExplosion(bool IsExplosion = true) { m_IsExplosion = IsExplosion; }

private:
	void SummonExplosion();
};