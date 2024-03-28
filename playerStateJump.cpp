#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "playerStateJump.h"
#include "playerStateIdle.h"
#include "playerStateWalk.h"
#include "input.h"
#include "camera.h"

PlayerStateJump::PlayerStateJump(Player * pPlayer, float Speed)
{
	pPlayer->ChangeAnimation("Jump");
	m_Speed = Speed;

	D3DXVECTOR3 pVelocity = pPlayer->GetVelocity();

	if (pVelocity.y == 0.0f)
		pPlayer->AddVelocity(D3DXVECTOR3(0.0f, m_JumpVelocity, 0.0f));

	pPlayer->PlayJumpSound();
}

void PlayerStateJump::Update(Player * pPlayer)
{
	D3DXVECTOR3 pPosition = pPlayer->GetPosition();
	D3DXVECTOR3 pRotation = pPlayer->GetRotation();
	D3DXVECTOR3 pVelocity = pPlayer->GetVelocity();
	D3DXVECTOR3 pForward = pPlayer->GetForward();
	
	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	
	m_Speed *= 0.98f;
	
	if (m_Speed <= 0.01f)
		m_Speed = 0.0f;

	pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));

	if (pPlayer->IsGround() && m_Speed == 0.0f)
	{
		pPlayer->ChangePlayerState(new PlayerStateIdle(pPlayer));
	}
	else if(pPlayer->IsGround() && m_Speed > 0.0f)
	{
		pPlayer->ChangePlayerState(new PlayerStateWalk(pPlayer, m_Speed));
	}
}
