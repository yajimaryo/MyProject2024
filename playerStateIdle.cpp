#include "main.h"
#include "manager.h"
#include "player.h"
#include "playerStateIdle.h"
#include "playerStateWalk.h"
#include "playerStateRun.h"
#include "playerStateJump.h"
#include "playerStateAttack.h"
#include "playerStateGuard.h"
#include "playerStateDying.h"
#include "input.h"

PlayerStateIdle::PlayerStateIdle(Player * pPlayer)
{
	pPlayer->ChangeAnimation("Idle");

	pPlayer->SetWeaponDraw(false);
}

void PlayerStateIdle::Update(Player * pPlayer)
{
	

	if (Input::GetKeyPress('W') || Input::GetKeyPress('A') ||
		Input::GetKeyPress('S') || Input::GetKeyPress('D'))
	{
		if (Input::GetKeyPress(VK_LSHIFT))
		{
			pPlayer->ChangePlayerState(new PlayerStateRun(pPlayer));
		}
		else
		{
			pPlayer->ChangePlayerState(new PlayerStateWalk(pPlayer));
		}
	}

	if (Input::GetKeyTrigger(VK_SPACE))
		pPlayer->ChangePlayerState(new PlayerStateJump(pPlayer));
	
	if (Input::GetMouseLPress() && pPlayer->CanAttack())
		pPlayer->ChangePlayerState(new PlayerStateAttack(pPlayer));

	if (pPlayer->GetHp() <= 0)
		pPlayer->ChangePlayerState(new PlayerStateDying(pPlayer));
	
}
