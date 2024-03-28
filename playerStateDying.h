#pragma once

#include "playerState.h"

class PlayerStateDying : public PlayerState
{
private:
	int m_AnimFrame = 0;
public:
	explicit PlayerStateDying(Player* pPlayer);
	virtual ~PlayerStateDying() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateDying() {}
};