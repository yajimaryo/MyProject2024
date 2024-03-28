#include "main.h"
#include "manager.h"
#include "player.h"
#include "playerStateGuard.h"
#include "playerStateIdle.h"
#include "input.h"

PlayerStateGuard::PlayerStateGuard(Player * pPlayer)
{
	pPlayer->ChangeAnimation("Guard");

	pPlayer->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	pPlayer->SetGuard(true);
}

void PlayerStateGuard::Update(Player * pPlayer)
{
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_GuardTime = 10;
	}
	else
	{
		m_GuardTime--;

		if (m_GuardTime <= 0)
		{
			pPlayer->SetGuard(false);
			pPlayer->ChangePlayerState(new PlayerStateIdle(pPlayer));
		}
	}
}
