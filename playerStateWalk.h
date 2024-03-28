#pragma once

#include "playerState.h"

class PlayerStateWalk : public PlayerState
{
private:
	float m_Speed = 0.01f;
	float m_SpeedMax = 0.1f;

public:
	explicit PlayerStateWalk(Player* pPlayer, float Speed = 0.01f, bool ChangeAnimation = true);
	virtual ~PlayerStateWalk() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateWalk() {}
};