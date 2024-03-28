#pragma once

#include "playerState.h"

class Weapon;

class PlayerStateGuard : public PlayerState
{
private:
	int m_GuardTime = 10;

public:
	explicit PlayerStateGuard(Player* pPlayer);
	virtual ~PlayerStateGuard() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateGuard() {}
};