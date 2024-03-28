#include "main.h"
#include "manager.h"
#include "player.h"
#include "playerStateDying.h"

PlayerStateDying::PlayerStateDying(Player * pPlayer)
{
	pPlayer->ChangeAnimation("Dying");

	pPlayer->SetWeaponDraw(false);

	pPlayer->SetVelocity(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_AnimFrame = 0;
}

void PlayerStateDying::Update(Player * pPlayer)
{
	if (m_AnimFrame >= 98)
	{
		pPlayer->SetIsAnimation(false);
	}

	m_AnimFrame++;
}
