#pragma once

#include "playerState.h"

class PlayerStateJump : public PlayerState
{
private:
	float m_Speed = 0.0f;
	float m_JumpVelocity = 0.35f;

public:
	explicit PlayerStateJump(Player* pPlayer, float Speed = 0.0f);
	virtual ~PlayerStateJump() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateJump() {}
};