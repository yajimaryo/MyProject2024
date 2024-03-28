#pragma once

#include "playerState.h"

class PlayerStateIdle : public PlayerState
{
public:
	explicit PlayerStateIdle(Player* pPlayer);
	virtual ~PlayerStateIdle(){}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateIdle(){}
};