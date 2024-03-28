#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "playerStateRun.h"
#include "playerStateWalk.h"
#include "playerStateJump.h"
#include "playerStateAttack.h"
#include "playerStateGuard.h"
#include "playerStateDying.h"
#include "input.h"
#include "camera.h"

PlayerStateRun::PlayerStateRun(Player * pPlayer, float Speed)
{
	pPlayer->ChangeAnimation("Run");
	m_Speed = Speed;

	pPlayer->SetWeaponDraw(false);
}

void PlayerStateRun::Update(Player * pPlayer)
{
	bool move = false;
	float rotation;

	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (Input::GetKeyPress('A'))
	{
		rotation = camera->GetRotation().y - D3DX_PI * 0.5f;
		move = true;
	}

	if (Input::GetKeyPress('D'))
	{
		rotation = camera->GetRotation().y + D3DX_PI * 0.5f;
		move = true;
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
			m_Speed *= 1.05f;

		if (m_Speed >= m_SpeedMax)
			m_Speed = m_SpeedMax;

		pPlayer->SetRotation(D3DXVECTOR3(pRotation.x, rotation, pRotation.z));
		pPlayer->SetVelocity(D3DXVECTOR3(pForward.x * m_Speed, pVelocity.y, pForward.z * m_Speed));

	}

	if (!Input::GetKeyPress(VK_LSHIFT) || !move)
	{
		pPlayer->ChangePlayerState(new PlayerStateWalk(pPlayer, m_Speed));
	}

	if (Input::GetKeyTrigger(VK_SPACE))
		pPlayer->ChangePlayerState(new PlayerStateJump(pPlayer, m_Speed));

	if (pPlayer->GetHp() <= 0)
		pPlayer->ChangePlayerState(new PlayerStateDying(pPlayer));
}
