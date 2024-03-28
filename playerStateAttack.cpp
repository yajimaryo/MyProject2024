#include "main.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "playerStateAttack.h"
#include "playerStateIdle.h"
#include "playerStateWalk.h"
#include "playerStateRoll.h"
#include "playerStateJump.h"
#include "playerStateDying.h"
#include "weapon.h"
#include "input.h"

PlayerStateAttack::PlayerStateAttack(Player * pPlayer, float Speed)
{
	m_Weapon = pPlayer->GetWeapon();
	m_AttackTime = 0;

	m_Speed = Speed;

	pPlayer->SetWeaponDraw(true);
}

void PlayerStateAttack::Update(Player * pPlayer)
{
	m_Weapon = pPlayer->GetWeapon();
	bool move = false;
	D3DXVECTOR3 moveVec;
	float rollRot;

	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (Input::GetKeyPress('A'))
	{
		moveVec = -pPlayer->GetRight();
		rollRot = camera->GetRotation().y - D3DX_PI * 0.5f;
		move = true;
	}

	if (Input::GetKeyPress('D'))
	{
		moveVec = pPlayer->GetRight();
		rollRot = camera->GetRotation().y + D3DX_PI * 0.5f;
		move = true;
	}

	if (Input::GetKeyPress('W'))
	{
		moveVec = pPlayer->GetForward();
		rollRot = camera->GetRotation().y;

		if (Input::GetKeyPress('D'))
		{
			moveVec += pPlayer->GetRight();
			rollRot += D3DX_PI * 0.25f;
		}

		if (Input::GetKeyPress('A'))
		{
			moveVec -= pPlayer->GetRight();
			rollRot -= D3DX_PI * 0.25f;
		}
		move = true;
	}

	if (Input::GetKeyPress('S'))
	{
		moveVec = -pPlayer->GetForward();
		rollRot = camera->GetRotation().y + D3DX_PI;

		if (Input::GetKeyPress('D'))
		{
			moveVec += pPlayer->GetRight();
			rollRot -= D3DX_PI * 0.25f;
		}

		if (Input::GetKeyPress('A'))
		{
			moveVec -= pPlayer->GetRight();
			rollRot += D3DX_PI * 0.25f;
		}

		move = true;
	}

	if (move)
	{
		pPlayer->ChangeAnimation("Walk");

		if (m_Speed <= 0.0f)
			m_Speed = 0.01f;

		if (m_Speed < m_SpeedMax)
			m_Speed *= 1.3f;

		if (m_Speed >= m_SpeedMax)
			m_Speed *= 0.9f;

		D3DXVec3Normalize(&moveVec, &moveVec);
		pPlayer->SetVelocity(D3DXVECTOR3(moveVec.x * m_Speed, pPlayer->GetVelocity().y, moveVec.z * m_Speed));
	}
	else if (!move)
	{
		if (m_Speed > 0.0f)
			m_Speed *= 0.9f;

		if (m_Speed < 0.01f)
			m_Speed = 0.0f;

		pPlayer->SetVelocity(pPlayer->GetVelocity() * m_Speed);

		
		pPlayer->ChangeAnimation("Idle");

	}

	D3DXVECTOR3 rotation = pPlayer->GetRotation();
	pPlayer->SetRotation(D3DXVECTOR3(rotation.x, camera->GetRotation().y, rotation.z));



	m_AttackTime++;

	if (m_AttackTime == m_Weapon->GetAttackFrame())
		m_Weapon->Attack(pPlayer->GetPosition() + D3DXVECTOR3(0.0f,0.5f,0.0f), camera->GetForward());

	if (m_AttackTime >= m_Weapon->GetAttackTime() && !Input::GetMouseLPress())
	{
		if (m_Speed == 0.0f)
		{
			pPlayer->ChangePlayerState(new PlayerStateIdle(pPlayer));
		}
		else
		{
			pPlayer->ChangePlayerState(new PlayerStateWalk(pPlayer, m_Speed, true));
		}
	}
	else if (m_AttackTime >= m_Weapon->GetAttackTime())
		m_AttackTime = 0;

	if (Input::GetKeyTrigger(VK_SPACE))
		pPlayer->ChangePlayerState(new PlayerStateRoll(pPlayer, rollRot));

	if (pPlayer->GetHp() <= 0)
		pPlayer->ChangePlayerState(new PlayerStateDying(pPlayer));
}
