#pragma once

#include "main.h"
#include "gameObject.h"
#include <string>

class Audio;
class Weapon;
class Guage;
class Shadow;
class AnimationModel;
class PlayerState;

class Player : public GameObject
{
private:
	static int m_MainWeaponNum;
	static int m_SubWeaponNum;

	static AnimationModel* m_Model;

	ID3D11VertexShader* m_VertexShader = nullptr;
	ID3D11PixelShader* m_PixelShader = nullptr;
	ID3D11InputLayout* m_VertexLayout = nullptr;

	ID3D11VertexShader* m_VertexShaderGuard = nullptr;
	ID3D11PixelShader* m_PixelShaderGuard = nullptr;
	ID3D11InputLayout* m_VertexLayoutGuard = nullptr;

	PlayerState* m_PlayerPattern = nullptr;

	
	int m_AnimTime = 0;
	int m_NextAnimTime = 0;
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	float m_AnimBlendRate = 0.0f;
	bool m_IsAnimation = true;

	Audio* m_JumpSE = nullptr;
	Audio* m_SecondJumpSE = nullptr;
	Audio* m_HealSE = nullptr;
	Audio* m_HitSE = nullptr;
	Audio* m_GuardSE = nullptr;

	Weapon* m_Weapon = nullptr;
	Weapon* m_SubWeapon = nullptr;

	Guage* m_Guage = nullptr;

	Shadow* m_Shadow = nullptr;

	float m_Hp = 0.0f;
	float m_HpMax = 0.0f;
	float m_HpOld = 0.0f;
	bool m_Move = true;
	bool m_Hit = false;
	int m_DrawCount = 0;

	D3DXVECTOR3 m_Velocity{};

	float m_GroungHeight = 0.0f;
	bool m_IsGround = false;

	float m_Speed;
	float m_SpeedMax;
	float m_DashSpeedMax;
	float m_Accel;

	bool m_Attack = false;
	int m_AttackTime = 0;

	bool m_Guard = false;
	int m_GuardTime = 0;

	bool m_Peek = false;
	bool m_WeaponDraw = true;

	void Collision(void);
public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void SetMainWeapon(int Num) { m_MainWeaponNum = Num; }
	static void SetSubWeapon(int Num) { m_SubWeaponNum = Num; }
	static int GetMainWeapon() { return m_MainWeaponNum; }
	static int GetSubWeapon() { return m_SubWeaponNum; }

	void TakeDamage(float Damage);
	void Heal(float heal);

	Weapon* GetWeapon() { return m_Weapon; }

	int GetHp() { return (int)((m_Hp / m_HpMax) * 100.0f); }//hpÇÃäÑçáÇï‘Ç∑

	void SetGuard(bool Guard) { m_Guard = Guard; }

	float GetGroungHeight() { return m_GroungHeight; }
	bool IsGround() { return m_IsGround; }

	void ChangePlayerState(PlayerState* PlayerPattern);
	void ChangeAnimation(std::string AnimName);
	std::string GetAnimationName(void) { return m_AnimationName; }
	void SetIsAnimation(bool IsAnimation) { m_IsAnimation = IsAnimation; }

	void SetVelocity(D3DXVECTOR3 Velocity) { m_Velocity = Velocity; }
	D3DXVECTOR3 GetVelocity() { return m_Velocity; }
	void AddVelocity(D3DXVECTOR3 Velocity) { m_Velocity += Velocity; }

	bool CanAttack();
	void SetWeaponDraw(bool IsDraw) { m_WeaponDraw = IsDraw; }

	void PlayJumpSound();
};