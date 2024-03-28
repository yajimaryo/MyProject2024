#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "playerStateWalk.h"
#include "playerStateIdle.h"
#include "playerStateRun.h"
#include "playerStateJump.h"
#include "playerStateAttack.h"
#include "playerStateRoll.h"
#include "input.h"
#include "camera.h"

PlayerStateRoll::PlayerStateRoll(Player * pPlayer,float RollRot)
{
	pPlayer->ChangeAnimation("Roll");

	m_Speed = 0.6f;

	D3DXVECTOR3 pRotation = pPlayer->GetRotation();
	pPlayer->SetRotation(D3DXVECTOR3(pRotation.x, RollRot, pRotation.z));

	pPlayer->SetWeaponDraw(false);

	pPlayer->PlayJumpSound();
}

void PlayerStateRoll::Update(Player * pPlayer)
{
	D3DXVECTOR3 pVelocity = pPlayer->GetVelocity();
	D3DXVECTOR3 pForward = pPlayer->GetForward();

	m_Speed *= 0.96f;
		
	pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));

	if (m_Speed <= 0.05f)
	{
		m_Speed = 0.0f;
		pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));
		pPlayer->ChangePlayerState(new PlayerStateIdle(pPlayer));
	}

}
