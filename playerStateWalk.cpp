#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "playerStateWalk.h"
#include "playerStateIdle.h"
#include "playerStateRun.h"
#include "playerStateJump.h"
#include "playerStateAttack.h"
#include "playerStateGuard.h"
#include "playerStateRoll.h"
#include "playerStateDying.h"
#include "input.h"
#include "camera.h"

PlayerStateWalk::PlayerStateWalk(Player * pPlayer, float Speed, bool ChangeAnimation)
{
	if(ChangeAnimation)
		pPlayer->ChangeAnimation("Walk");

	m_Speed = Speed;

	pPlayer->SetWeaponDraw(true);
}

void PlayerStateWalk::Update(Player * pPlayer)
{
	bool move = false;
	bool roll = false;
	float rotation;

	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	
	if (Input::GetKeyPress('A')) 
	{
		rotation = camera->GetRotation().y - D3DX_PI * 0.5f;
		move = true;
		roll = true;
	}

	if (Input::GetKeyPress('D')) 
	{
		rotation = camera->GetRotation().y + D3DX_PI * 0.5f;
		move = true;
		roll = true;
	}

	if (Input::GetKeyPress('W'))
	{
		rotation = camera->GetRotation().y;

		if (Input::GetKeyPress('D'))
			rotation += D3DX_PI * 0.25f;

		if (Input::GetKeyPress('A'))
			rotation -= D3DX_PI * 0.25f;

		move = true;
	}

	if (Input::GetKeyPress('S'))
	{
		rotation = camera->GetRotation().y + D3DX_PI;

		if (Input::GetKeyPress('D'))
			rotation -= D3DX_PI * 0.25f;

		if (Input::GetKeyPress('A'))
			rotation += D3DX_PI * 0.25f;

		move = true;
	}

	D3DXVECTOR3 pRotation = pPlayer->GetRotation();
	D3DXVECTOR3 pVelocity = pPlayer->GetVelocity();
	D3DXVECTOR3 pForward = pPlayer->GetForward();

	if (move)
	{
		if (m_Speed < 0.01f)
			m_Speed = 0.0f;

		if (m_Speed < m_SpeedMax)
			m_Speed *= 1.3f;
					
		if (m_Speed >= m_SpeedMax)
			m_Speed *= 0.9f;

		pPlayer->SetRotation(D3DXVECTOR3(pRotation.x, rotation, pRotation.z));
		pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));

		if (Input::GetKeyPress(VK_LSHIFT))
			pPlayer->ChangePlayerState(new PlayerStateRun(pPlayer, m_Speed));

		if (Input::GetKeyTrigger(VK_SPACE))
		{
			if (roll)
				pPlayer->ChangePlayerState(new PlayerStateRoll(pPlayer, rotation));

			if(!roll)
				pPlayer->ChangePlayerState(new PlayerStateJump(pPlayer, m_Speed));
		}
	}
	else if (!move)
	{
		if (m_Speed > 0.0f)
			m_Speed *= 0.9f;

		if (m_Speed < 0.01f)
			m_Speed = 0.0f;
		
		pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));

		if (m_Speed == 0.0f)
			pPlayer->ChangePlayerState(new PlayerStateIdle(pPlayer));

		if (Input::GetKeyTrigger(VK_SPACE))
			pPlayer->ChangePlayerState(new PlayerStateJump(pPlayer, m_Speed));
	}

	if (Input::GetMouseLPress() && pPlayer->CanAttack())
		pPlayer->ChangePlayerState(new PlayerStateAttack(pPlayer,m_Speed));

	if (pPlayer->GetHp() <= 0)
		pPlayer->ChangePlayerState(new PlayerStateDying(pPlayer));
}
