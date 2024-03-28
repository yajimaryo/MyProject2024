#pragma once

#include "playerState.h"

class PlayerStateRoll : public PlayerState
{
private:
	float m_Speed = 0.01f;
	float m_SpeedMax = 0.1f;
	float m_RollRot = 0.0f;
public:
	explicit PlayerStateRoll(Player* pPlayer,float RollRot);
	virtual ~PlayerStateRoll() {}
	virtual void Update(Player* pPlayer) override;

private:
	PlayerStateRoll() {}
};