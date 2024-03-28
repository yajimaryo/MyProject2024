
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "scene.h"
#include "input.h"

void Camera::Init()
{
	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Update()
{
	Scene* scene = Manager::GetInstance()->GetScene();
	Player* player = scene->GetGameObject<Player>();

	if (player)
	{
		D3DXVECTOR3 pos = player->GetPosition();


		// 前回のマウス座標
		static POINT prevMousePos;

		// 現在のマウス座標を取得
		POINT currentMousePos;
		GetCursorPos(&currentMousePos);

		// マウスの移動量を計算
		int deltaX = 300 - prevMousePos.x;
		int deltaY = 300 - prevMousePos.y;

		// マウス座標を保存
		prevMousePos = currentMousePos;

		// マウス移動に応じてカメラの回転量を更新
		float rotationSpeed = -0.002f; // 回転速度調整
		m_Rotation.y += deltaX * rotationSpeed; // 横方向の回転
		m_Rotation.x += deltaY * rotationSpeed; // 縦方向の回転
		m_Up += deltaY * rotationSpeed;

		if (m_Up >= 10.0f)
			m_Up = 10.0f;

		if (m_Up <= -3.0f)
			m_Up = -3.0f;

		if (m_Peek)
		{
			// FPS
			m_Position = pos + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
			D3DXVECTOR3 forward = D3DXVECTOR3(sinf(m_Rotation.y + D3DX_PI), m_Up - 1.5f, cosf(m_Rotation.y + D3DX_PI));
			m_Target = m_Position - forward; // カメラの注視点を更新
		}
		else
		{
			//TPS
			m_Target = pos + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
			m_Position = pos + D3DXVECTOR3(0.0f, m_Up, 0.0f);
			m_Position += D3DXVECTOR3(sinf(m_Rotation.y + D3DX_PI), 0.0f, cosf(m_Rotation.y + D3DX_PI)) * 4.0f;
		}

		SetCursorPos(300, 300);
	}

	


	//カメラシェイク
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.8f;
}


void Camera::Draw()
{

	//ビューマトリクス設定
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_Position + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);

	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);

	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);
}


bool Camera::CheckView(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	D3DXMATRIX vp, invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_Position;

	//左面判定
	{
		v1 = wpos[0] - m_Position;
		v2 = wpos[2] - m_Position;

		D3DXVec3Normalize(&v1,&v1);
		D3DXVec3Normalize(&v2, &v2);


		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < -Size.x)
		{
			return false;
		}
	}

	//右面判定
	{
		v1 = wpos[3] - m_Position;
		v2 = wpos[1] - m_Position;

		D3DXVec3Normalize(&v1, &v1);
		D3DXVec3Normalize(&v2, &v2);

		D3DXVec3Cross(&n, &v1, &v2);

		if (D3DXVec3Dot(&n, &v) < -Size.x)
		{
			return false;
		}
	}

	return true;
}
