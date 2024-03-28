#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "player.h"
#include "enemyDrone.h"
#include "droneStateMove.h"
#include "resource.h"
#include "model.h"
#include "shotGun.h"

void EnemyDrone::Init()
{
	Enemy::Init();
	Enemy::SetFlight();

	m_DronePattern = new DroneStateMove(this, 0);

	m_Hp = 10.0f;

	SetCollisionSize(10.0f);
	SetCollisionOffset(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_ModelName = (char*)"asset\\model\\Drone.obj";
}

void EnemyDrone::Uninit()
{
	Enemy::Uninit();
}

void EnemyDrone::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();

	if (!m_Weapon)
	{
		m_Weapon = scene->AddGameObject<ShotGun>(3);
		m_Weapon->Init(1);
	}

	m_OldPosition = m_Position;

	m_DronePattern->Update(this);

	if (m_Velocity.x > 0.5f)
		m_Velocity.x = 0.5f;

	if (m_Velocity.x < -0.5f)
		m_Velocity.x = -0.5f;

	if (m_Velocity.y > 0.5f)
		m_Velocity.y = 0.5f;

	if (m_Velocity.y < -0.5f)
		m_Velocity.y = -0.5f;

	if (m_Velocity.z > 0.5f)
		m_Velocity.z = 0.5f;

	if (m_Velocity.z < -0.5f)
		m_Velocity.z = -0.5f;

	m_Position += m_Velocity;

	if (m_Position.y > 30.0f)
		m_Position.y = 30.0f;

	Enemy::Update();
}

void EnemyDrone::Draw()
{
	Enemy::Draw();

	ResourceManager::GetInstance()->GetResouseModel(m_ModelName)->Draw();
}

void EnemyDrone::ChangeDronePattern(DroneState * DronePattern)
{
	if (m_DronePattern)
		delete m_DronePattern;

	m_DronePattern = DronePattern;
}

void EnemyDrone::Attack(D3DXVECTOR3 Direction)
{
	m_Weapon->Attack(m_Position + D3DXVECTOR3(0.0f, 0.3f, 0.0f), Direction);
}
