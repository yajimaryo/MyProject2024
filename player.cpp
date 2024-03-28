
#include "main.h"
#include <vector>
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "resource.h"
#include "player.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "bullet.h"
#include "enemyManager.h"
#include "enemyAttack.h"
#include "cylinder.h"
#include "box.h"
#include "audio.h"
#include "effect.h"
#include "sword.h"
#include "guage.h"
#include "shadow.h"
#include "gun.h"
#include "shotGun.h"
#include "launcher.h"
#include "animSprite.h"
#include "sprite.h"
#include "animationModel.h"
#include "playerState.h"
#include "playerStateIdle.h"
#include "playerStateDying.h"
#include "meshField.h"

int Player::m_MainWeaponNum = 0;
int Player::m_SubWeaponNum = 1;
AnimationModel* Player::m_Model{};

void Player::Load()
{
	m_Model = new AnimationModel;
	m_Model->Load((char*)"asset\\model\\Swat.fbx");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Swiping01.fbx", "Attack");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Idle.fbx", "Idle");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Walk.fbx", "Walk");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Run.fbx", "Run");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Guard.fbx", "Guard");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Jump.fbx", "Jump");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Roll.fbx", "Roll");
	m_Model->LoadAnimation((char*)"asset\\model\\Player_Dying.fbx", "Dying");
}

void Player::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Player::Init()
{
	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_PlayerPattern = new PlayerStateIdle(this);

	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.01f, 0.01f, 0.01f);

	m_Speed = 0.0f;
	m_SpeedMax = 0.1f;
	m_DashSpeedMax = 0.2f;
	m_Accel = 1.3f;

	m_JumpSE = AddComponent<Audio>();
	m_JumpSE->Load("asset/audio/player_jump01.wav");

	m_SecondJumpSE = AddComponent<Audio>();
	m_SecondJumpSE->Load("asset/audio/player_jump02.wav");

	m_HealSE = AddComponent<Audio>();
	m_HealSE->Load("asset/audio/heal.wav");

	m_HitSE = AddComponent<Audio>();
	m_HitSE->Load("asset/audio/hit.wav");

	m_GuardSE = AddComponent<Audio>();
	m_GuardSE->Load("asset/audio/guard.wav");

	m_Shadow = AddComponent<Shadow>();

	
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingPS.cso");

	Renderer::CreateVertexShader(&m_VertexShaderGuard, &m_VertexLayoutGuard,
		"shader\\pixelLightingGuardVS.cso");

	Renderer::CreatePixelShader(&m_PixelShaderGuard,
		"shader\\pixelLightingGuardPS.cso");


	m_HpMax = 50.0f;
	m_Hp = m_HpOld = m_HpMax;
	
	AddComponent<AnimSprite>()->Init(0.0f,25.0f, 50.0f, 30.0f, (char*)"asset/texture/hp.png", 1, 1);
	AddComponent<Sprite>()->Init(SCREEN_WIDTH / 2 - 25.0f, SCREEN_HEIGHT / 2, 50.0f, 50.0f, (char*)"asset/texture/aim.png");
}

void Player::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	m_VertexLayoutGuard->Release();
	m_VertexShaderGuard->Release();
	m_PixelShaderGuard->Release();

	GameObject::Uninit();

}

void Player::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (!m_Weapon)
	{
		if (m_MainWeaponNum == 0)
			m_Weapon = scene->AddGameObject<Gun>(3);

		if (m_MainWeaponNum == 1)
			m_Weapon = scene->AddGameObject<ShotGun>(3);

		if(m_MainWeaponNum == 2)
			m_Weapon = scene->AddGameObject<Launcher>(3);
		
		m_Weapon->Init(0);
	}
	if (!m_SubWeapon)
	{
		if (m_SubWeaponNum == 0)
			m_SubWeapon = scene->AddGameObject<Gun>(3);

		if (m_SubWeaponNum == 1)
			m_SubWeapon = scene->AddGameObject<ShotGun>(3);

		if (m_SubWeaponNum == 2)
			m_SubWeapon = scene->AddGameObject<Launcher>(3);

		m_SubWeapon->Init(0);
		m_SubWeapon->SetMain(false);
	}

	m_OldPosition = m_Position;
	
	m_PlayerPattern->Update(this);

	if (Input::GetKeyTrigger('R'))
	{
		m_Weapon->Reload();
	}
	if (Input::GetKeyTrigger('E'))
	{
		Weapon* we = m_Weapon;
		m_Weapon = m_SubWeapon;
		m_Weapon->SetMain(true);
		m_SubWeapon = we;
		m_SubWeapon->SetMain(false);
	}
	if (Input::GetMouseRTrigger())
	{
		if (m_Peek)
		{
			camera->SetPeek(m_Peek);
			m_Peek = false;
		}
		else
		{
			camera->SetPeek(m_Peek);
			m_Peek = true;
		}
	}

	//重力
	m_Velocity.y -= 0.015f;
	//移動
	m_Position += m_Velocity;

	if (m_Position.y < m_GroungHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = m_GroungHeight;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	if (m_Hit)
	{
		m_DrawCount++;

		if (m_DrawCount > 90)
		{
			m_DrawCount = 0;
			m_Hit = false;
		}
	}

	if (m_Hp < m_HpOld && m_Hp > 0.0f)
	{
		m_Hp += 0.01f;
		
		if (m_Hp > m_HpOld)
			m_Hp = m_HpOld;
	}

	if (!m_Guage)
	{
		m_Guage = scene->AddGameObject<Guage>(3);
		m_Guage->Init(50.0f, 25.0f, 500.0f, 30.0f);
	}

	m_Guage->SetGuage(D3DXVECTOR3(m_Hp, m_HpMax, m_HpOld));


	if (m_Position.z > 98.0f || m_Position.z < -98.0f)
	{
		m_Position.z = m_OldPosition.z;
	}

	if (m_Position.x > 98.0f || m_Position.x < -98.0f)
	{
		m_Position.x = m_OldPosition.x;
	}

	m_AnimBlendRate += 0.05f;

	if (m_AnimBlendRate > 1.0f)
		m_AnimBlendRate = 1.0f;

	if (m_IsAnimation)
	{
		m_AnimTime++;
		m_NextAnimTime++;
	}

	m_Shadow->SetPosition(D3DXVECTOR3(m_Position.x, m_GroungHeight + 0.1f, m_Position.z));


	Collision();

	GameObject::Update();
}


void Player::Draw()
{
	if (m_DrawCount % 15 <= 5 || m_DrawCount >= 60)
	{
		if (!m_Guard)
		{
			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//シェーダー設定
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
		}
		else if (m_Guard)
		{
			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayoutGuard);

			Renderer::GetDeviceContext()->VSSetShader(m_VertexShaderGuard, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShaderGuard, NULL, 0);
		}


		// マトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
		world = scale * rot * trans;

		Renderer::SetWorldMatrix(&world);

		//m_Model->Update(m_AnimationName.c_str(), m_AnimTime);
		m_Model->Update(m_AnimationName.c_str(), m_AnimTime, m_NextAnimationName.c_str(), m_NextAnimTime, m_AnimBlendRate);
		
		m_Model->Draw();

		if (m_WeaponDraw)
		{

			D3DXVECTOR3 weaponPos = m_Model->GetBonePosition((char*)"mixamorig:LeftHand");
			
			D3DXMATRIX weaponWorld, weaponScale, weaponRot, weaponTrans;
			D3DXMatrixScaling(&weaponScale, 0.2f, 0.2f, 0.2f);
			D3DXMatrixRotationYawPitchRoll(&weaponRot, -D3DX_PI / 2, 0.0f, 0.0f);
			D3DXMatrixTranslation(&weaponTrans, 0.0f, -weaponPos.y / 2.0f + 1.3f, weaponPos.z - 0.35f);
			
			weaponWorld = weaponScale * weaponRot * weaponTrans * rot * trans;

			Renderer::SetWorldMatrix(&weaponWorld);

			ResourceManager::GetInstance()->GetResouseModel((char*)"asset\\model\\gun01.obj")->Draw();
		}
	}
	GameObject::Draw();
}

void Player::TakeDamage(float Damage)
{
	if (!m_Guard)
	{
		if (m_Hit)
			return;

		m_HpOld = m_Hp - Damage  * 0.8f;
		m_Hp -= Damage;

		if (m_Hp < 0.0f)
			m_Hp = 0.0f;

		m_HitSE->Play(false, 0.3f);

		m_Hit = true;
	}
	else
	{
		m_GuardSE->Play();
	}
}

void Player::Heal(float heal)
{
	m_HealSE->Play();

	m_Hp += heal;

	if (m_Hp > m_HpOld)
		m_HpOld = m_Hp;

	if (m_Hp >= m_HpMax)
		m_Hp = m_HpMax;
}

void Player::ChangePlayerState(PlayerState * PlayerPattern)
{
	if (m_PlayerPattern)
		delete m_PlayerPattern;

	m_PlayerPattern = PlayerPattern;
}

void Player::ChangeAnimation(std::string AnimName)
{
	if (m_NextAnimationName != AnimName)
	{
		m_AnimationName = m_NextAnimationName;
		m_NextAnimationName = AnimName;
		m_AnimBlendRate = 0.0f;
		m_AnimTime = m_NextAnimTime;
		m_NextAnimTime = 0;
	}
}

bool Player::CanAttack()
{
	return m_Weapon->CanAttack();
}

void Player::PlayJumpSound()
{
	int n = rand() % 2;

	if (n == 0)
	{
		m_JumpSE->Play(false, 2.0f);
	}
	else
	{
		m_SecondJumpSE->Play(false, 2.0f);
	}
}

void Player::Collision(void)
{
	Scene* scene = Manager::GetInstance()->GetScene();
	MeshField* mf = scene->GetGameObject<MeshField>();

	m_GroungHeight = mf->GetHeight(m_Position);

	//Cylinderとの当たり判定
	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 pos = cylinder->GetPosition();
		D3DXVECTOR3 scl = cylinder->GetScale();

		D3DXVECTOR3 dir = m_Position - pos;
		dir.y = 0.0f;
		float length = D3DXVec3Length(&dir);

		if (length < scl.x + 0.5f)
		{
			if (m_Position.y < pos.y + scl.y - 0.5f)
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;
			}
			else
			{
				if (m_GroungHeight < pos.y + scl.y)
					m_GroungHeight = pos.y + scl.y;
			}
			break;
		}
	}

	//boxとの当たり判定
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();
	for (Box* box : boxes)
	{
		D3DXVECTOR3 pos = box->GetPosition();
		D3DXVECTOR3 scl = box->GetScale();
		D3DXVECTOR3 right = box->GetRight();
		D3DXVECTOR3 forward = box->GetForward();
		D3DXVECTOR3 direction = m_Position - pos;
		
		float obbx = D3DXVec3Dot(&direction, &right);
		float obbz = D3DXVec3Dot(&direction, &forward);

		//OBB
		if (fabs(obbx) < scl.x + 0.5f && fabs(obbz) < scl.z + 0.5f)
		{
			if (m_Position.y < pos.y + (scl.y * 2 - 0.5f))
			{
				m_Position.x = m_OldPosition.x;
				m_Position.z = m_OldPosition.z;
			}
			else
			{
				if (m_GroungHeight < pos.y + scl.y * 2)
					m_GroungHeight = pos.y + scl.y * 2;
			}
			break;
		}
	}


}