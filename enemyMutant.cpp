#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemyMutant.h"
#include "mutantState.h"
#include "mutantStateIdle.h"
#include "animationModel.h"

AnimationModel* EnemyMutant::m_Model{};

void EnemyMutant::Load()
{
	m_Model = new AnimationModel;
	m_Model->Load((char*)"asset\\model\\Mutant.fbx");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Swiping01.fbx", "Attack");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Idle.fbx", "Idle");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Walking.fbx", "Walk");
	m_Model->LoadAnimation((char*)"asset\\model\\Mutant Skill.fbx", "Skill");
}

void EnemyMutant::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void EnemyMutant::Init()
{

	Enemy::Init();

	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";

	m_MutantPattern = new MutantStateIdle(this);

	m_Scale = D3DXVECTOR3(0.05f, 0.05f, 0.05f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout,
		"shader\\pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\pixelLightingPS.cso");

	m_Hp = 500.0f;

	SetCollisionSize(10.0f);
	SetCollisionOffset(D3DXVECTOR3(0.0f, 3.5f, 0.0f));

	m_SkillCT = 600;
}

void EnemyMutant::Uninit()
{
	Enemy::Uninit();
}

void EnemyMutant::Update()
{
	m_OldPosition = m_Position;

	m_MutantPattern->Update(this);

	m_Position += m_Velocity;

	m_AnimBlendRate += 0.05f;

	if (m_AnimBlendRate > 1.0f)
		m_AnimBlendRate = 1.0f;

	m_AnimTime++;
	m_NextAnimTime++;

	m_SkillCT--;

	Enemy::Update();
}

void EnemyMutant::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Update(m_AnimationName.c_str(), m_AnimTime, m_NextAnimationName.c_str(), m_NextAnimTime, m_AnimBlendRate);
	
	m_Model->Draw();
}

void EnemyMutant::ChangeMutantPattern(MutantState * MutantPattern)
{
	if (m_MutantPattern)
		delete m_MutantPattern;

	m_MutantPattern = MutantPattern;
}

void EnemyMutant::ChangeAnimation(std::string AnimName)
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
