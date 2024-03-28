#pragma once

#include "playerState.h"

class PlayerStateRun : public PlayerState
{
private:
	float m_Speed = 0.01f;
	float m_SpeedMax = 0.3f;

public:
	explicit PlayerStateRun(Player* pPlayer, float Speed = 0.01f);
	virtual ~PlayerStateRun() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateRun() {}
};