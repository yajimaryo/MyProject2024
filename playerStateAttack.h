#pragma once

#include "playerState.h"

class Weapon;

class PlayerStateAttack : public PlayerState
{
private:
	Weapon* m_Weapon = nullptr;
	int m_AttackTime = 0;
	float m_Speed = 0.0f;
	float m_SpeedMax = 0.1f;

public:
	explicit PlayerStateAttack(Player* pPlayer, float Speed = 0.01f);
	virtual ~PlayerStateAttack() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateAttack() {}
};